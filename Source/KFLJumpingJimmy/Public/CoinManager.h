// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CoinManager.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KFLJUMPINGJIMMY_API UCoinManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCoinManager();

    UFUNCTION()
        int getNumCoins();
    UFUNCTION()
        void AddCoin();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Custom", meta = (AllowPrivateAccess = "true"))
        class UAudioComponent* AudioComponent;

    UPROPERTY(EditAnywhere, Category = "Custom", meta = (AllowPrivateAccess = "true"))
        class USoundBase* JumpSound;

    int numCoins;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
