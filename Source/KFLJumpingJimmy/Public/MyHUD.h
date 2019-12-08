// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MyHUD.generated.h"

/**
 * 
 */
UCLASS()
class KFLJUMPINGJIMMY_API AMyHUD : public AHUD
{
	GENERATED_BODY()
public:
        AMyHUD();

    //TSubclassOf: This is a reference to a Class which can be set and has to be of type UUserWidget in this case. Remember this is not a Instance of a class
    UPROPERTY(EditAnywhere, Category = "Game Hud")
        TSubclassOf<class UUserWidget> PlayerGuiClass;

    //A UUserWidget pointer to the Instance of the PlayerGuiClass
    UPROPERTY()
        class UUserWidget* PlayerGui;

protected:
    virtual void BeginPlay() override;
	
};
