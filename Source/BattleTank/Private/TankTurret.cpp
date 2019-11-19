// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"
#include "Engine/StaticMesh.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"

// Just switch workaround off by commenting this
//#define WORKAROUND

/*
 * W O R K A R O U N D   F O R   V A N I S H I N G   S T A T I C  M E S H
 * Set static mesh within the constructor manually
 */
UTankTurret::UTankTurret()
{
#ifdef WORKAROUND
    static ConstructorHelpers::FObjectFinder<UStaticMesh>SM(TEXT("BattleTank/Content/Tank/Tank_fbx_Turret"));
    if (SM.Succeeded()) {
        UE_LOG(LogTemp, Warning, TEXT("Set Static Mesh %s"), *SM.Object->GetName());
        this->SetStaticMesh(SM.Object);
    } else {
        UE_LOG(LogTemp, Error, TEXT("Could not set static mesh to component"));
    }
#endif
}

void UTankTurret::Rotate(float TargetHitYawAngle)
{
    float MaxLimitedAngle = MaxRotationSpeed * FMath::Sign(TargetHitYawAngle) * GetWorld()->DeltaTimeSeconds;
    SetRelativeRotation(FRotator(0.0f,
        FMath::Abs(TargetHitYawAngle) > FMath::Abs(MaxLimitedAngle) ?
        RelativeRotation.Yaw + MaxLimitedAngle :
        RelativeRotation.Yaw + TargetHitYawAngle,
        0.0f));
}
