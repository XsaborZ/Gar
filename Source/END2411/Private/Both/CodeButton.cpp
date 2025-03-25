// Fill out your copyright notice in the Description page of Project Settings.


#include "Both/CodeButton.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

void UCodeButton::NativePreConstruct()
{
	Information->SetText(Info);
}

void UCodeButton::NativeConstruct()
{
	Background_Button->OnClicked.AddDynamic(this, &UCodeButton::HandleOnClicked);
}

void UCodeButton::HandleOnClicked()
{
	OnClickedDelegate.Broadcast();
}
