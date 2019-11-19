// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
    void Rotate(float TargetHitYawAngles);
    float previousRotate = 0.0f;

private:
    UTankTurret();
    //UPROPERTY(EditAnywhere, Category = Setup)
    //float MaxDegreesPerSecond = 25;
    // Maximum Turret Rotation Speed in degrees per second. This is used in combination with Relative Speed factor 1.0 .. -1.0 for left/right rotation
    UPROPERTY(EditDefaultsOnly, Category = Movability, meta = (DisplayName = "Rotate Speed", UIMin = "5.0", UIMax = "40.0", ClampMin = "5.0", ClampMax = "40.0"))
    float MaxRotationSpeed = 20.0f;
};
