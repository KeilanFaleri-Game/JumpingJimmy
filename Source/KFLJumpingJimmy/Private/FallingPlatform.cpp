// Fill out your copyright notice in the Description page of Project Settings.


#include "FallingPlatform.h"
#include "Components/BoxComponent.h"
#include "PaperSpriteComponent.h"

// Sets default values
AFallingPlatform::AFallingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    BoxComponent = CreateDefaultSubobject<UBoxComponent>("FallingPlatformBox");
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
    BoxComponent->ComponentTags.Add("Block");

    PlayerSpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>("FallingPlatformSprite");
    PlayerSpriteComponent->SetCollisionProfileName("NoCollision");
    PlayerSpriteComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    PlayerSpriteComponent->SetupAttachment(RootComponent);


}

// Called when the game starts or when spawned
void AFallingPlatform::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFallingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z - 5.0f));

    if (GetActorLocation().Z < -800.0f)
    {
        SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z + 2700.0f), false, nullptr, ETeleportType::TeleportPhysics);
    }
}


// When pressing up arrow
    // Check if we are on elavator (get overlapping actors)
        // If we found overlapping actors (array is larger than 0)
            // Check if the object is the elavator (tags)
                // if object does, move it the same way as player

