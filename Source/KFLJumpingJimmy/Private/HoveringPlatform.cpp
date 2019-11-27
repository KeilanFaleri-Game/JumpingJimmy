// Fill out your copyright notice in the Description page of Project Settings.

#include "HoveringPlatform.h"
#include "Components/BoxComponent.h"
#include "PaperSpriteComponent.h"


// Sets default values
AHoveringPlatform::AHoveringPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    BoxComponent = CreateDefaultSubobject<UBoxComponent>("HoveringBox");
    RootComponent = BoxComponent;
    BoxComponent->SetCollisionProfileName("BlockAll");
    BoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    BoxComponent->SetSimulatePhysics(false);
    BoxComponent->SetEnableGravity(false);
    BoxComponent->GetBodyInstance()->bLockZRotation = true;
    BoxComponent->GetBodyInstance()->bLockYRotation = true;
    BoxComponent->GetBodyInstance()->bLockXRotation = true;
    BoxComponent->GetBodyInstance()->bLockYTranslation = true;
    BoxComponent->GetBodyInstance()->bLockXTranslation = true;

    PlayerSpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>("HoveringSprite");
    PlayerSpriteComponent->SetCollisionProfileName("NoCollision");
    PlayerSpriteComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    PlayerSpriteComponent->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AHoveringPlatform::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHoveringPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

