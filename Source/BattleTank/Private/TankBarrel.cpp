// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "BattleTank.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
    // Moves the barrel to the right amount this time Given a max elevation speed and the frame time
    RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1);
    auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
    auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;
    auto Elevation = FMath::Clamp<float>(RawNewElevation, MinElevationDegrees, MaxElevationDegrees);
    SetRelativeRotation(FRotator(RawNewElevation, 0, 0));
}
