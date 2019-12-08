// Fill out your copyright notice in the Description page of Project Settings.

#include "MyHUD.h"
#include "Blueprint/UserWidget.h"
#include "ConstructorHelpers.h"

AMyHUD::AMyHUD()
{
    //The following lines sets the PlayerUI blueprint to the TSubclassof variable via code
    static ConstructorHelpers::FClassFinder<UUserWidget> playerHud(TEXT("/Game/Blueprints/UI/PlayerUI"));
    if (playerHud.Succeeded())
        PlayerGuiClass = playerHud.Class;
}

int AMyHUD::GetGameTimer()
{
    return GameTimer;
}

void AMyHUD::BeginPlay()
{
    //Instantiate the PlayerGuiClass and assign the instance to PlayerGui
    PlayerGui = CreateWidget<UUserWidget>(GetGameInstance(),
        PlayerGuiClass);
    //Add the PlayerGui to the HUD's viewport
    PlayerGui->AddToViewport();

}

void AMyHUD::Tick(float DeltaTime)
{
    GameTimer += DeltaTime;
}
