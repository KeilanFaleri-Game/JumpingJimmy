// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformSpawner.h"
#include "FallingPlatform.h"
#include "Components/BoxComponent.h"
#include "..\Public\PlatformSpawner.h"

// Sets default values
APlatformSpawner::APlatformSpawner()
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

    BoxComponent->ComponentHasTag()
}

// Called when the game starts or when spawned
void APlatformSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlatformSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlatformSpawner::SpawnActor()
{
    //IF the FallingActorTemplate NOT EQUAL to nullptr
    if (FallingActorTemplate != nullptr)
    {
        //DECLARE a variable called World of type const UWorld* and assign it to the return value of GetWorld()
        UWorld* World = GetWorld();
        //IF World is NOT EQUAL to nullptr
        if (World)
        {
            //DECLARE a variable called SpawnParams of type FActorSpawnParameters
            FActorSpawnParameters SpawnParams;
            //SET SpawnParams Owner to this
            SpawnParams.Owner = this;
            //SET SpawnParams SpawnCollisionHandlingOverride property to ESpawnActorCollisionHandlingMethod::AlwaysSpawn
            SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

            //DECLARE a variable called SpawnTransform of type FTransform and assign it to the return value of SpawnPointComponent->GetComponentTransform()
            FTransform SpawnTransform = SpawnPointComponent->GetComponentTransform();
            //DECLARE a variable called SpawnedActor of type AFallingActor* and assign it to the return value of World->SpawnActor<type>(args..), 
            //passing in AFallingActor as the type argument (inside <>) and in function arguments pass --> FallingActorTemplate, SpawnTransform, SpawnParams
            //SpawnActor() is a very important Function, it Instantiates the TSubclassOf template class that we set in the editor.
            AFallingPlatform* SpawnedActor = World->SpawnActor<AFallingPlatform>(FallingActorTemplate, SpawnTransform, SpawnParams);
            //IF SpawnedActor NOT EQUAL to nullptr
            if (SpawnedActor)
            {
                //DECLARE a variable called direction of type FVector and assign it to the return value of --> FRotationMatrix(SpawnTransform.Rotator()).GetScaledAxis(EAxis::X)
                FVector direction = FRotationMatrix(SpawnTransform.Rotator()).GetScaledAxis(EAxis::X);
                //DECLARE a variable called physicsComponent of type UPrimitiveComponent* and assign it to the return value of --> SpawnedActor->GetPhysicsComponent()
                UPrimitiveComponent* physicsComponent = SpawnedActor->GetPhysicsComponent();
                //CALL AddForce(..) on the physicsComponent and pass in --> direction * 1000000, NAME_None, true
                physicsComponent->AddForce(direction * 1000000, NAME_None, true);
            }
            //ENDIF SpawnedActor NOT EQUAL to nullptr
        }
        //ENDIF World is NOT EQUAL to nullptr

    }//ENDIF the FallingActorTemplate NOT EQUAL to nullptr

}