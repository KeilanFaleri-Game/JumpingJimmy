// Fill out your copyright notice in the Description page of Project Settings.


#include "FallingPawn.h"
#include "PaperSpriteComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "..\Public\FallingPawn.h"

// Sets default values
AFallingPawn::AFallingPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    BoxComponent = CreateDefaultSubobject<UBoxComponent>("playerBox");
    RootComponent = BoxComponent;
    BoxComponent->SetCollisionProfileName("BlockAll");
    BoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    BoxComponent->SetSimulatePhysics(true);
    BoxComponent->SetEnableGravity(true);
    BoxComponent->GetBodyInstance()->bLockXRotation = true;
    BoxComponent->GetBodyInstance()->bLockYRotation = true;
    BoxComponent->GetBodyInstance()->bLockZRotation = true;
    BoxComponent->GetBodyInstance()->bLockYTranslation = true;

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

}

// Called when the game starts or when spawned
void AFallingPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFallingPawn::MoveRight(float value)
{
    MovementRight = value;
}

void AFallingPawn::MoveUp(float value)
{
    MovementUp = value;
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
    if (MovementUp != 0)
    {
        //Calculate a new location to move (ActorsCurrentLocation + (ActorsUpDirection * MovementDelta)
        FVector NewLocation = GetActorLocation() + (GetActorUpVector() * MovementUp);
        //SET's the Actors new Location
        SetActorLocation(NewLocation);
    }
    if (GetActorLocation().Z < -800.0f)
    {
        SetActorLocation(CheckPoint);
    }
}

// Called to bind functionality to input
void AFallingPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    //BINDS this Actors MoveRight function to the MoveRight input binding created in the Editor under EditProjectSettings->Input->AxisMapping
    //MoveRight(float value) will get called when the Axis Button is activated
    PlayerInputComponent->BindAxis("MoveRight",
        this,
        &AFallingPawn::MoveRight);

    //BINDS this Actors MoveRight function to the MoveUp input binding created in the Editor under EditProjectSettings->Input->AxisMapping
    //MoveUp(float value) will get called when the Axis Button is activated
    PlayerInputComponent->BindAxis("MoveUp",
        this,
        &AFallingPawn::MoveUp);
}


