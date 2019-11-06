// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"
#include "BattleTank.h"


void ATankAIController::BeginPlay()
{
    Super::BeginPlay();
    auto PlayerTank = GetPlayerTank();
    if(!PlayerTank)
    {
        UE_LOG(LogTemp, Warning, TEXT("AIController can't find a PlayerTank"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("AIController found player: %s"), *(PlayerTank->GetName()));
    }
}

ATank* ATankAIController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
    auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
    if(!PlayerPawn) { return nullptr; }
    return Cast<ATank>(PlayerPawn);
}

void ATankAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    if(GetPlayerTank())
    {
        // TODO Move towards the player
        
        // Tell the ControlledTank to AimAt the Player's Location
        GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
        
        //  Fire if ready
    }
}
