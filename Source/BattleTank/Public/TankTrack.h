// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 *  TankTrack sets a maximum driving force and applies it to the Tank
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
    UFUNCTION(BlueprintCallable, Category = Input)
    void SetThrottle(float Throttle);
    // Max force per track in Newtons for a 40 Ton Tank and 1g acceleration according to https://www.wolframalpha.com/input/?i=0-60mph+in+10+seconds
    UPROPERTY(EditDefaultsOnly)
    float TrackMaxDrivingForce = 40000000;
};
