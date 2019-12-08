// Fill out your copyright notice in the Description page of Project Settings.

#include "JumpComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Components/BoxComponent.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundBase.h"
#include "FallingPawn.h"


// Sets default values for this component's properties
UJumpComponent::UJumpComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

    AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("SoundEmitter"));
    AudioComponent->bAutoActivate = false;
    AudioComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
}


void UJumpComponent::Jump()
{
    //TODO Week 10:
    if (OnFloor) 
    {
        //TODO Week 10:
        //SET OnFloor to false
        OnFloor = false;
        //TODO Week 10:
        //CALL AddForce() on CapsuleComponent->BodyInstance passing FVector(0.0f, 0.0f, 1.0f) * ForceScalarZ * JumpPowerZ
        
        CharacterOwner->BoxComponent->AddForce(FVector(0.0f, 0.0f, 1.0f) * ForceScalarZ * JumpPowerZ);

        AudioComponent->SetSound(JumpSound);

        AudioComponent->Play();
    }

}

void UJumpComponent::Land()
{
    //TODO Week 10:
    //SET OnFloor to true
    OnFloor = true;
    //TODO Week 10:
    //IF !WasOnFloor
    if (!WasOnFloor) {
        //TODO Week 10:
        //SET WasOnFloor to true
        WasOnFloor = true;
    }
    //ENDIF
}
 
// Called when the game starts
void UJumpComponent::BeginPlay()
{
	Super::BeginPlay();
    CharacterOwner = Cast<AFallingPawn>(GetOwner());

    check(CharacterOwner != nullptr && "UJumpComponent::MoveUp::BeginPlay - CharacterOwner is Null");
}


// Called every frame
void UJumpComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}
