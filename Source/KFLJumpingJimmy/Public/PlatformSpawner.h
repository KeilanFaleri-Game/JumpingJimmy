// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlatformSpawner.generated.h"

UCLASS()
class KFLJUMPINGJIMMY_API APlatformSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlatformSpawner();

    class UBoxComponent* BoxComponent;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Config")
    TSubclassOf<class AFallingActor> FallingActorTemplate;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    void SpawnActor();

private:
    /* arrow component  */
    //This will be the spawn point
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
        class UArrowComponent* SpawnPointComponent;

};
