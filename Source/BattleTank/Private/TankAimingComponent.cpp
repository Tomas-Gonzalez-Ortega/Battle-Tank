// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "BattleTank.h"
#include "Projectile.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Public/DrawDebugHelpers.h"    // e.g. DrawDebugLine


/// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
    if(!BarrelToSet){return;}
    Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurret* TurretToSet)
{
    if(!TurretToSet){return;}
    Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector OutHitLocation, float LaunchSpeed)
{
    if(!ensure(Barrel) || !ensure(Turret)) return;
    FVector startLocation = Barrel->GetSocketLocation(FName("Projectile"));
    if(Barrel->bDrawDebugLines) {
        DrawDebugLine(
            GetWorld(),
            startLocation,        // Projectile Start
            OutHitLocation,        // Hit Location
            FColor::Red,
            false,
            2.0f,
            0,
            2.0f
        );
    }
    FVector OutSuggestedVelocity = FVector(0.0f);            // Aim direction when normalized
    // Launch Speed is very important. From Engine Source:
    // https://github.com/EpicGames/UnrealEngine/blob/release/Engine/Source/Runtime/Engine/Private/GameplayStatics.cpp
    // "this will automatically fall back to line test if radius is small enough"
    // https://en.wikipedia.org/wiki/Projectile_motion - Angle required to hit coordinate (x,y)
    if(UGameplayStatics::SuggestProjectileVelocity(
        this,
        OutSuggestedVelocity,                                // returned velocity length = LaunchSpeed
        startLocation,
        OutHitLocation,
        LaunchSpeed,
        false,                                                // true: returns just a vector pointing UP
        0.0f,
        0.0f,
        ESuggestProjVelocityTraceOption::DoNotTrace            // NEEDED, ELSE GETTING MANY NON RESULTS
    )) {
        AimDirection = OutSuggestedVelocity.GetSafeNormal();
        if(Barrel->bDrawDebugLines)
        {
            DrawDebugLine(
                GetWorld(),
                startLocation,                                    // Projectile Socket
                startLocation + AimDirection * 300.0f,            // 3m into AimDirection
                FColor::Yellow,
                false,
                2.0f,
                0,
                3.0f
            );
        }
        // Barrel Elevation
        FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
        //FRotator BarrelRotator = Barrel->GetComponentRotation(); // Same, just Roll != 0.0
        FRotator AimRotator = AimDirection.Rotation();
        Barrel->Elevate((AimRotator - BarrelRotator).Pitch);

        // Turret Rotation - calculate Yaw ourselves instead of using Yaw from AimRotator
        FVector BarrelLocation = Barrel->GetComponentLocation();
        FRotator YawRotator = (OutHitLocation - BarrelLocation).Rotation();
        FRotator DeltaRotator = YawRotator - BarrelRotator;
        Turret->Rotate(FMath::Abs(DeltaRotator.Yaw) < 180 ? DeltaRotator.Yaw : -DeltaRotator.Yaw);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("%s: No aiming direction could be determined"), *GetOwner()->GetName());
    }
}

/*
void UTankAimingComponent::AimAt(FVector OutHitLocation, float LaunchSpeed)
{
    if(!Barrel){return;}
    FVector OutLaunchVelocity(0);
    FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
    auto Time = GetWorld()->GetTimeSeconds();
    bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
    (
        this,
        OutLaunchVelocity,
        StartLocation,
        OutHitLocation,
        LaunchSpeed,
        false,
        0,
        0,
        ESuggestProjVelocityTraceOption::DoNotTrace
    );
    if(bHaveAimSolution)
    {
        auto AimDirection = OutLaunchVelocity.GetSafeNormal();
        MoveBarrelTowards(AimDirection);
    }
    // No aim solution found - Do Nothing
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
    // Works out difference between current barrel rotation and AimDirection
    auto BarrelRotator = Barrel->GetForwardVector().Rotation();
    auto AimAsRotator = AimDirection.Rotation();
    auto DeltaRotator = AimAsRotator - BarrelRotator;
    Barrel->Elevate(DeltaRotator.Pitch);
    Turret->Rotate(DeltaRotator.Yaw);
}
*/
