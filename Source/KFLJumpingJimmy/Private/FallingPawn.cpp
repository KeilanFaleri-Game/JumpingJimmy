// Fill out your copyright notice in the Description page of Project Settings.


#include "FallingPawn.h"
#include "Checkpoint.h"
#include "EnemyActor.h"
#include "JumpComponent.h"
#include "PaperSpriteComponent.h"
#include "Components/PrimitiveComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundBase.h"
#include "Camera/CameraComponent.h"
#include "EngineUtils.h"
#include "Components/BoxComponent.h"
#include "..\Public\FallingPawn.h"

// Sets default values
AFallingPawn::AFallingPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    BoxComponent = CreateDefaultSubobject<UBoxComponent>("playerBox");
    RootComponent = BoxComponent;
    BoxComponent->SetNotifyRigidBodyCollision(true);
    BoxComponent->SetCollisionProfileName("BlockAll");
    BoxComponent->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
    BoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    BoxComponent->SetSimulatePhysics(true);
    //BoxComponent->SetEnableGravity(true);
    BoxComponent->GetBodyInstance()->bLockXRotation = true;
    BoxComponent->GetBodyInstance()->bLockYRotation = true;
    BoxComponent->GetBodyInstance()->bLockZRotation = true;
    BoxComponent->GetBodyInstance()->bLockYTranslation = true;
    BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AFallingPawn::OnHit);
    BoxComponent->ComponentTags.Add("Player");

    PlayerSpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>("playerSprite");
    PlayerSpriteComponent->SetCollisionProfileName("NoCollision");
    PlayerSpriteComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    PlayerSpriteComponent->SetupAttachment(RootComponent);

    SpringArmComponent =
        CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
    SpringArmComponent->SetupAttachment(RootComponent);
    SpringArmComponent->bDoCollisionTest = false;
    SpringArmComponent->bInheritPitch = false;
    SpringArmComponent->bInheritYaw = false;
    SpringArmComponent->bInheritRoll = false;
    SpringArmComponent->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

    FollowCameraComponent = CreateDefaultSubobject<UCameraComponent>("Player Follow Camera");
    FollowCameraComponent->SetProjectionMode(ECameraProjectionMode::Orthographic);
    FollowCameraComponent->SetOrthoWidth(2500.0f);
    FollowCameraComponent->SetupAttachment(SpringArmComponent);

    AudioComponent2 = CreateDefaultSubobject<UAudioComponent>(TEXT("SoundEmitter2"));
    AudioComponent2->bAutoActivate = false;
    AudioComponent2->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
    AudioComponent2->SetupAttachment(RootComponent);

    pJumpComponent = CreateDefaultSubobject<UJumpComponent>("Jump");
}

// Called when the game starts or when spawned
void AFallingPawn::BeginPlay()
{
	Super::BeginPlay();
    GameTimer = 0;
}

void AFallingPawn::MoveRight(float value)
{
    MovementRight = value;
}

void AFallingPawn::Jump()
{
    pJumpComponent->Jump();
}

// Called every frame

void AFallingPawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (MovementRight != 0)
    {
        //Calculate a new location to move (ActorsCurrentLocation + (ActorsForwardDirection * MovementDelta)
        FVector NewLocation = GetActorLocation() + (GetActorForwardVector() * MovementRight);
        //SET's the Actors new Location
        SetActorLocation(NewLocation);
    }

    if (GetActorLocation().Z < -800.0f || GetActorLocation().Z > 3000.0f)
    {
        SetActorLocation(CheckPoint, false, nullptr, ETeleportType::TeleportPhysics);
    }
    
    GameTimer += DeltaTime;
}

int AFallingPawn::GetGameTimer()
{
    return GameTimer;
}

// Called to bind functionality to input
void AFallingPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    //BINDS this Actors MoveRight function to the MoveRight input binding created in the Editor under EditProjectSettings->Input->AxisMapping
    //MoveRight(float value) will get called when the Axis Button is activated
    PlayerInputComponent->BindAxis("MoveRight", this, &AFallingPawn::MoveRight);

    //BINDS this Actors MoveRight function to the MoveUp input binding created in the Editor under EditProjectSettings->Input->AxisMapping
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AFallingPawn::Jump);
}

void AFallingPawn::OnHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, "POOP " + OtherComp->GetName());

    if (OtherComp->ComponentHasTag("Checkpoint"))
    {
        for (TActorIterator<ACheckpoint> ActorItr(GetWorld()); ActorItr; ++ActorItr)
        {
            ACheckpoint* tempCheckPoint = Cast<ACheckpoint>(*ActorItr);

            CheckPoint = tempCheckPoint->GetActorLocation();
        }
    }

    if (OtherComp->ComponentHasTag("Enemy"))
    {
        for (TActorIterator<AEnemyActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
        {
            SetActorLocation(CheckPoint, false, nullptr, ETeleportType::TeleportPhysics);
        }
    }

    if (OtherComp->ComponentHasTag("Win"))
    {
        for (TActorIterator<AEnemyActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
        {
            AudioComponent2->SetSound(YayyySound);

            AudioComponent2->Play();

            SetActorLocation(FVector(29295.0,0,100), false, nullptr, ETeleportType::TeleportPhysics);
        }
    }

    if (OtherComp->ComponentHasTag("Block"))
    {
        
         pJumpComponent->Land();
        
    }
}

