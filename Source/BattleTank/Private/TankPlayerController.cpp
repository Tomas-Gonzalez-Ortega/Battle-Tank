// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Tank.h"
#include "BattleTank.h"

void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();
    auto ControlledTank = GetControlledTank();
    if(!ControlledTank)
    {
        UE_LOG(LogTemp, Warning, TEXT("PlayerController Not Possessing a Tank"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("PlayerController Possessing: %s"), *(ControlledTank->GetName()));
    }
}

void ATankPlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
    if(!GetControlledTank()) { return; }
    FVector OutHitLocation; // Out Parameter
    if(GetSightRayHitLocation(OutHitLocation))
    {
        GetControlledTank()->AimAt(OutHitLocation);
          // GetWorld Location of the linetrace through the crosshair
          // If it hits the landscape
              // tells ControlledTank to aim at this point
    }
}

// Gets World Location of linetrace through crosshair, if it hits the landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
    // Finds the crosshair position in pixel coordinates
    int32 ViewportSizeX, ViewportSizeY;
    GetViewportSize(ViewportSizeX, ViewportSizeY);
    auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairXLocation);
    
    // De-projects the screen position of the crosshair to a world direction
    FVector LookDirection;
    if(GetLookDirection(ScreenLocation, LookDirection))
    {
        // Line-traces along that LookDirection, and sees what we hit (up to a max range)
        GetLookVectorHitDirection(LookDirection, OutHitLocation);
    }
    return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
    FVector CameraWorldLocation; // to be discarded
    return DeprojectScreenPositionToWorld
    (
        ScreenLocation.X,
        ScreenLocation.Y,
        CameraWorldLocation,
        LookDirection
     );
}

bool ATankPlayerController::GetLookVectorHitDirection(FVector LookDirection, FVector& OutHitLocation) const
{
    FHitResult HitResult;
    auto StartLocation = PlayerCameraManager->GetCameraLocation();
    auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
    if(GetWorld()->LineTraceSingleByChannel
       (
        HitResult,
        StartLocation,
        EndLocation,
        ECollisionChannel::ECC_Visibility)
       )
    {
        OutHitLocation = HitResult.Location;
        return true;
    }
    OutHitLocation = FVector(0); // Preventing nasty values coming out from tracing
    return false; // Line trace did not succed
}
