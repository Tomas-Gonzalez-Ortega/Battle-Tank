// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

//Forward Declaration
class ATank;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

private:
    ATank* GetControlledTank() const;
    void AimTowardsCrosshair(); // barrel starts to move towards the aiming point
    bool GetSightRayHitLocation(FVector& OutHitLocation) const;
    bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;
    bool GetLookVectorHitDirection(FVector LookDirection, FVector& OutHitLocation) const;
    UPROPERTY(EditAnywhere)
    float CrosshairXLocation = 0.5;
    UPROPERTY(EditAnywhere)
    float CrosshairYLocation = 0.3333;
    UPROPERTY(EditAnywhere)
    float LineTraceRange = 1000000; // 10K = a million centimiters
};
