// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
    // -1 is max downwards movement & +1 is upwards movement
    void Elevate(float TargetHitPitchAngle);
    // Draw debug lines Barrel: projectile>hitlocation in red and projectile>aimdirection in yellow
    UPROPERTY(EditAnyWhere, Category = Debugging, meta = (DisplayName = "Debuglines"))
    bool bDrawDebugLines = false;
    
private:
    private:
    // Maximum Barrel Elevation Speed in degrees per second. This is used in combination with Relative Speed factor 1.0 .. -1.0 for up/down movement
    UPROPERTY(EditDefaultsOnly, Category = Movability, meta = (DisplayName = "Barrel Speed", UIMin = "5.0", UIMax = "20.0", ClampMin = "5.0", ClampMax = "20.0"))
    float MaxElevationSpeed = 10.0f;

    // Minimum Barrel Elevation in degrees. Determines lowest position.
    UPROPERTY(EditDefaultsOnly, Category = Movability, meta = (DisplayName = "Min. Elevation", UIMin = "-5.0", UIMax = "5.0", ClampMin = "-5.0", ClampMax = "5.0"))
    float MinimumElevation = 0.0f;

    // Maximum Barrel Elevation in degrees. Determinex highest position.
    UPROPERTY(EditDefaultsOnly, Category = Movability, meta = (DisplayName = "Max. Elevation", UIMin = "50.0", UIMax = "80.0", ClampMin = "50.0", ClampMax = "80.0"))
    float MaximumElevation = 65.0f;
};
