// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingPlatform.generated.h"

UCLASS()
class KFLJUMPINGJIMMY_API AMovingPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovingPlatform();

    UPROPERTY(EditAnywhere, Category = "Collision Box")
        class UBoxComponent* BoxComponent;

    UPROPERTY(EditAnywhere, Category = "Visual")
        class UPaperSpriteComponent* PlayerSpriteComponent;

    /* Let the guard go on patrol */
    UPROPERTY(EditInstanceOnly, Category = "AI")
        bool bPatrol;

    /* First of two patrol points to patrol between */
    UPROPERTY(EditInstanceOnly, Category = "AI", meta = (EditCondition = "bPatrol"))
        AActor* FirstPatrolPoint;

    /* Second of two patrol points to patrol between */
    UPROPERTY(EditInstanceOnly, Category = "AI", meta = (EditCondition = "bPatrol"))
        AActor* SecondPatrolPoint;

    // The current point the actor is either moving to or standing at
    AActor* CurrentPatrolPoint;

    UFUNCTION() //WIthout this, the function will be inlined and optimized out
        void MoveToNextPatrolPoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
