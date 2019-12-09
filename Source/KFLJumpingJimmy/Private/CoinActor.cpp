// Fill out your copyright notice in the Description page of Project Settings.


#include "CoinActor.h"
#include "Components/BoxComponent.h"
#include "PaperSpriteComponent.h"

// Sets default values
ACoinActor::ACoinActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    BoxComponent = CreateDefaultSubobject<UBoxComponent>("playerBox");
    RootComponent = BoxComponent;
    BoxComponent->SetNotifyRigidBodyCollision(true);
    BoxComponent->SetCollisionProfileName("Checkpoint");
    BoxComponent->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
    BoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    BoxComponent->GetBodyInstance()->bLockXRotation = true;
    BoxComponent->GetBodyInstance()->bLockYRotation = true;
    BoxComponent->GetBodyInstance()->bLockZRotation = true;
    BoxComponent->GetBodyInstance()->bLockYTranslation = true;
    BoxComponent->ComponentTags.Add("Coin");

    CoinComponent = CreateDefaultSubobject<UPaperSpriteComponent>("playerSprite");
    CoinComponent->SetCollisionProfileName("NoCollision");
    CoinComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    CoinComponent->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ACoinActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACoinActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

