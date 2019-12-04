// Fill out your copyright notice in the Description page of Project Settings.

#include "MovingPlatform.h"
#include "Components/BoxComponent.h"
#include "PaperSpriteComponent.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
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

void AMovingPlatform::MoveToNextPatrolPoint()
{
    if (CurrentPatrolPoint == nullptr || CurrentPatrolPoint == SecondPatrolPoint)
    {
        CurrentPatrolPoint = FirstPatrolPoint;

    }
    else
    {
        CurrentPatrolPoint = SecondPatrolPoint;
    }

    FVector Direction = GetActorLocation() - CurrentPatrolPoint->GetActorLocation();
    Direction.Normalize();

    FRotator NewLookAt = FRotationMatrix::MakeFromX(Direction).Rotator();
    NewLookAt.Pitch = 0.0f;
    NewLookAt.Roll = 0.0f;
    NewLookAt.Yaw += -180.0f;
    SetActorRotation(NewLookAt);
}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

    if (bPatrol)
    {
        MoveToNextPatrolPoint();
    }
  
	
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    // Patrol Goal Checks
    if (CurrentPatrolPoint && bPatrol)
    {
        FVector Delta = GetActorLocation() - CurrentPatrolPoint->GetActorLocation();
        float DistanceToGoal = Delta.Size();

        // Check if we are within 50 .. 100(Better with 2D) units of our goal, if so - pick a new patrol point
        if (DistanceToGoal < 100)
        {
            MoveToNextPatrolPoint();
        }
        SetActorLocation(FMath::VInterpConstantTo(GetActorLocation(), CurrentPatrolPoint->GetActorLocation(), DeltaTime, 300.f));
    }
}

