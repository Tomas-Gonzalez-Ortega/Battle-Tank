// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// Forward Declaration
class ATank;
class UTankBarrel;
class UTankTurret;

// Holds the Barrel parameters and Elevate method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UTankAimingComponent(); // Constructs default values for this component's properties
    void SetBarrelReference(UTankBarrel* BarrelToSet);
    void SetTurretReference(UTankTurret* TurretToSet);
    void AimAt(FVector OutHitLocation, float LaunchSpeed);
    
private:
    UTankBarrel* Barrel = nullptr;
    UTankTurret* Turret = nullptr;
    //void MoveBarrelTowards(FVector AimDirection);
    FVector AimDirection = FVector(0.0f, 0.0f, 1.0f);
};
