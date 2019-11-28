// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Checkpoint.generated.h"

UCLASS()
class KFLJUMPINGJIMMY_API ACheckpoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACheckpoint();

    UPROPERTY(EditAnywhere, Category = "Collision Box")
        class UBoxComponent* BoxComponent;

    UPROPERTY(EditAnywhere, Category = "Visual")
        class UPaperSpriteComponent* CheckpointSprite;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
