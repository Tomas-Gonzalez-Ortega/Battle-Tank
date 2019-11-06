// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

// Forward declaration to prevent more dependencies
class UTankBarrel;
class UTankAimingComponent;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = Setup)
    void SetBarrelReference(UTankBarrel* BarrelToSet);
    
    UFUNCTION(BlueprintCallable, Category = Setup)
    void SetTurretReference(UTankTurret* TurretToSet);
    
    UFUNCTION(BlueprintCallable, Category = Firing)
    void Fire();
    
    void AimAt(FVector OutHitLocation);
    
protected:
    UTankAimingComponent* TankAimingComponent = nullptr;

private:
    ATank(); // Sets default values for this pawn's properties
	virtual void BeginPlay() override; // Called when the game starts or when spawned
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override; // Called to bind functionality to input
    UPROPERTY(EditAnywhere, Category = Firing)
    float LaunchSpeed = 40000;
};
