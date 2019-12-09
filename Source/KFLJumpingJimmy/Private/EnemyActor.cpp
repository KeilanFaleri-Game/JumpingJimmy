// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyActor.h"
#include "FallingPawn.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
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
    BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AEnemyActor::OnHit2);
    BoxComponent->ComponentTags.Add("Enemy");

    AICollision = CreateDefaultSubobject<USphereComponent>("AIBox");
    AICollision->SetCollisionProfileName("Checkpoint");
    AICollision->OnComponentBeginOverlap.AddDynamic(this, &AEnemyActor::OnHit);
    AICollision->SetupAttachment(RootComponent);

    PlayerSpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>("EnemySprite");
    PlayerSpriteComponent->SetCollisionProfileName("NoCollision");
    PlayerSpriteComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    PlayerSpriteComponent->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AEnemyActor::BeginPlay()
{
	Super::BeginPlay();

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
        SetActorLocation(FMath::VInterpConstantTo(GetActorLocation(), CurrentPatrolPoint->GetActorLocation(), DeltaTime, 200.f));
    }

    //IF Target is NOT EQUAL to nullptr
    if (Target != nullptr && !(bPatrol))
    {
        //DECLARE a variable called targetLocation of type FVector and assign it to the return value of FMath::VInterpConstantTo(..) passing in --> GetActorLocation(), Target->GetActorLocation(), DeltaTime, 600.0f
        FVector targetLocation = FMath::VInterpConstantTo(GetActorLocation(), Target->GetActorLocation(), DeltaTime, 300.0f);
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

void AEnemyActor::OnHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "POOP " + OtherComp->GetName());

    if (OtherComp != nullptr)
    {
        if (OtherComp->ComponentHasTag("Player"))
        {
            bPatrol = false;
        }
    }

}

void AEnemyActor::OnHit2(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, "POOP " + OtherComp->GetName());

    if (OtherComp != nullptr)
    {
        if (OtherComp->ComponentHasTag("Player"))
        {
            SetActorLocation(FirstPatrolPoint->GetActorLocation());
            bPatrol = true;
        }
    }

}

