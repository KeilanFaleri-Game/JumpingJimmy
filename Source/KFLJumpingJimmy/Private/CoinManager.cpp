// Fill out your copyright notice in the Description page of Project Settings.


#include "CoinManager.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundBase.h"

// Sets default values for this component's properties
UCoinManager::UCoinManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

    AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("SoundEmitter"));
    AudioComponent->bAutoActivate = false;
    AudioComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	// ...
}


int UCoinManager::getNumCoins()
{
    return numCoins;
}

void UCoinManager::AddCoin()
{
    numCoins++;

    AudioComponent->SetSound(JumpSound);
    AudioComponent->Play(0.5f);
}

// Called when the game starts
void UCoinManager::BeginPlay()
{
	Super::BeginPlay();

	// ...
    numCoins = 0;
}


// Called every frame
void UCoinManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

