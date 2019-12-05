// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyActor.h"
#include "FallingPawn.h"
#include "Perception/PawnSensingComponent.h"
#include "DrawDebugHelpers.h"
#include "Components/BoxComponent.h"
#include "EngineUtils.h"
#include "PaperSpriteComponent.h"

// Sets default values
AEnemyActor::AEnemyActor()
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
    BoxComponent->ComponentTags.Add("Enemy");

    PlayerSpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>("EnemySprite");
    PlayerSpriteComponent->SetCollisionProfileName("NoCollision");
    PlayerSpriteComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    PlayerSpriteComponent->SetupAttachment(RootComponent);
    
    PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>("AI");


}

// Called when the game starts or when spawned
void AEnemyActor::BeginPlay()
{
	Super::BeginPlay();

    //SUBSCRIBE to the PawnSensingComponent's OnSeePawn event passing in (this, &AAIGuard::OnPawnSeen)
    PawnSensingComponent->OnSeePawn.AddDynamic(this, &AEnemyActor::OnPawnSeen);

    bPatrol = true;

    if (bPatrol)
    {
        MoveToNextPatrolPoint();
    }

    for (TActorIterator<AFallingPawn> ActorItr(GetWorld()); ActorItr; ++ActorItr)
    {
        Target = Cast<AFallingPawn>(*ActorItr);
    }
}

// Called every frame
void AEnemyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (CurrentPatrolPoint)
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

    //IF Target is NOT EQUAL to nullptr
    if (Target != nullptr && !(bPatrol))
    {
        //DECLARE a variable called targetLocation of type FVector and assign it to the return value of FMath::VInterpConstantTo(..) passing in --> GetActorLocation(), Target->GetActorLocation(), DeltaTime, 600.0f
        FVector targetLocation = FMath::VInterpConstantTo(GetActorLocation(), Target->GetActorLocation(), DeltaTime, 600.0f);
        //CALL  SetActorLocation(..) passing in targetLocation
        SetActorLocation(targetLocation);
    }
    //ENDIF Target is NOT EQUAL to nullptr

}

void AEnemyActor::MoveToNextPatrolPoint()
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

void AEnemyActor::PostInitializeComponents()
{
    Super::PostInitializeComponents();
}

void AEnemyActor::OnPawnSeen(APawn* SeenPawn)
{
    //TODO Week 10b:
    if (SeenPawn == nullptr)
    {
        return;
    }


    //TODO Week 10b:
    //SET TargetActor to the SeenPawn (This can now be used to Implement a Chase behavior)
    TargetActor = SeenPawn;
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, "POOP " + TargetActor->GetName());

    bPatrol = false;

}
