// Fill out your copyright notice in the Description page of Project Settings.


#include "Checkpoint.h"
#include "Components/BoxComponent.h"
#include "PaperSpriteComponent.h"

// Sets default values
ACheckpoint::ACheckpoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    BoxComponent = CreateDefaultSubobject<UBoxComponent>("EnemyBox");
    RootComponent = BoxComponent;
    BoxComponent->SetCollisionProfileName("Checkpoint");
    BoxComponent->SetSimulatePhysics(false);
    BoxComponent->SetEnableGravity(false);
    BoxComponent->GetBodyInstance()->bLockZRotation = true;
    BoxComponent->GetBodyInstance()->bLockYRotation = true;
    BoxComponent->GetBodyInstance()->bLockXRotation = true;
    BoxComponent->GetBodyInstance()->bLockYTranslation = true;
    BoxComponent->GetBodyInstance()->bLockXTranslation = true;
    BoxComponent->ComponentTags.Add("Checkpoint");

    CheckpointSprite = CreateDefaultSubobject<UPaperSpriteComponent>("EnemySprite");
    CheckpointSprite->SetCollisionProfileName("NoCollision");
    CheckpointSprite->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    CheckpointSprite->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ACheckpoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACheckpoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

