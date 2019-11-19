// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Projectile.generated.h"

UCLASS()
class BATTLETANK_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:
	AProjectile();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
    void LaunchProjectile(float Speed);
    
private:
    UProjectileMovementComponent* ProjectileMovement = nullptr;
};
