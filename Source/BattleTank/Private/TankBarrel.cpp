// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "BattleTank.h"

void UTankBarrel::Elevate(float TargetHitPitchAngle)
{
    float MaxLimitedAngle = MaxElevationSpeed * FMath::Sign(TargetHitPitchAngle) * GetWorld()->DeltaTimeSeconds;
    float RawNewElevation = FMath::Abs(TargetHitPitchAngle) > FMath::Abs(MaxLimitedAngle) ?
        RelativeRotation.Pitch + MaxLimitedAngle :
        RelativeRotation.Pitch + TargetHitPitchAngle;
    SetRelativeRotation(FRotator(FMath::Clamp(RawNewElevation, MinimumElevation, MaximumElevation), 0.0f, 0.0f));
}
