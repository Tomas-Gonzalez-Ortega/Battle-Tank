// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "BattleTank.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
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
