// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Actors/Code_MenuPlayerController.h"
#include "Blueprint/UserWidget.h"

void ACode_MenuPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (MenuClass) {
		MenuInstance = CreateWidget< UUserWidget>(this, MenuClass);
		if (MenuInstance) {
			MenuInstance->AddToViewport();
			
			SetShowMouseCursor(true);
			FInputModeUIOnly InputMode;
			InputMode.SetWidgetToFocus(MenuInstance->TakeWidget());
			InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
			SetInputMode(InputMode);
			bShowMouseCursor = true; 
		}
	}

}
