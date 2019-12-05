// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyActor.generated.h"

UCLASS()
class KFLJUMPINGJIMMY_API AEnemyActor : public AActor
{

	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	AEnemyActor();

    virtual void PostInitializeComponents() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    UPROPERTY(VisibleAnywhere, Category = "Components")
        class UPawnSensingComponent* PawnSensingComponent;

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

    UFUNCTION()
        void OnPawnSeen(APawn* SeenPawn);

    UPROPERTY(EditInstanceOnly)
        AActor* Target;

    UPROPERTY(EditInstanceOnly)
        AActor* TargetActor;

};
