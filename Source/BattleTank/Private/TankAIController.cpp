// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"
#include "BattleTank.h"


void ATankAIController::BeginPlay()
{
    Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
    auto ControlledTank = Cast<ATank>(GetPawn());
    if(PlayerTank)
    {
        // TODO Move towards the player
        
        // Tell the ControlledTank to AimAt the Player's Location and Fire
        ControlledTank->AimAt(PlayerTank->GetActorLocation());
        ControlledTank->Fire();
    }
}
