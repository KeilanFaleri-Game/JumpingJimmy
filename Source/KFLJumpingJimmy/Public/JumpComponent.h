// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FallingPawn.h"
#include "Components/ActorComponent.h"
#include "JumpComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KFLJUMPINGJIMMY_API UJumpComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UJumpComponent();

    UPROPERTY(EditAnywhere, Category = "Visual")
        class AFallingPawn* CharacterOwner;

    UFUNCTION()
    void Jump();
    UFUNCTION()
    void Land();


    float TravelDirection;
    bool OnFloor = false;
    bool WasOnFloor = false;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

    float JumpScalar = 1.0f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Custom", meta = (AllowPrivateAccess = "true"))
        float MaxVelX = 1000.0f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Custom", meta = (AllowPrivateAccess = "true"))
        float ForceScalarX = 500000.0f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Custom", meta = (AllowPrivateAccess = "true"))
        float AirborneScalarX = 15000.0f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Custom", meta = (AllowPrivateAccess = "true"))
        float ForceScalarZ = 800000.0f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Custom", meta = (AllowPrivateAccess = "true"))
        float JumpPowerZ = 20.0f;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Custom", meta = (AllowPrivateAccess = "true"))
        class UAudioComponent* AudioComponent;

    UPROPERTY(EditAnywhere, Category = "Custom", meta = (AllowPrivateAccess = "true"))
        class USoundBase* JumpSound;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
		
};
