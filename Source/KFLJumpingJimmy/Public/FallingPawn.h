// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "FallingPawn.generated.h"

UCLASS()
class KFLJUMPINGJIMMY_API AFallingPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AFallingPawn();

    UPROPERTY(EditAnywhere, Category = "Collision Box")
        class UBoxComponent* BoxComponent;

    UPROPERTY(EditAnywhere, Category = "Visual")
        class UPaperSpriteComponent* PlayerSpriteComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera Spring", meta = (AllowPrivateAccess = "true"))
        class USpringArmComponent* SpringArmComponent;

    UPROPERTY(EditAnywhere, Category = "Player Camera")
        class UCameraComponent* FollowCameraComponent;

    UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
        class UJumpComponent* pJumpComponent;

    UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
        class UCoinManager* CoinManager;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Custom", meta = (AllowPrivateAccess = "true"))
        class UAudioComponent* AudioComponent2;

    UPROPERTY(EditAnywhere, Category = "Custom", meta = (AllowPrivateAccess = "true"))
        class USoundBase* YayyySound;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

    void MoveRight(float value);

    void Jump();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
       
    UFUNCTION(BlueprintCallable)
       int GetGameTimer();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    UFUNCTION()
        void OnHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION(BlueprintCallable)
        int getNumCoins();

    void PlayEndSound();

private:
    float MovementRight;
    FVector CheckPoint = FVector(50,0,500);
    float GameTimer;

};
