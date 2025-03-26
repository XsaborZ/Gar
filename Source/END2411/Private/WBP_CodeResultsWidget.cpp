// Fill out your copyright notice in the Description page of Project Settings.


#include "WBP_CodeResultsWidget.h"
#include "Utility/CodeGameInstance.h"
#include "Components/WidgetSwitcher.h" 
#include "Components/VerticalBox.h"
#include "Both/CodeButton.h"

void UWBP_CodeResultsWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	// Get Game instance then cast it into CodegameIntance
	UCodeGameInstance* CurrentGameInstance = Cast<UCodeGameInstance>(GetGameInstance()); 

    if (CurrentGameInstance)
    {
        GameInstance = CurrentGameInstance;
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to cast to UCodeGameInstance!"));
    }

}

void UWBP_CodeResultsWidget::NativeConstruct()
{
    RestartButton->OnClickedDelegate.AddDynamic(GameInstance, &UCodeGameInstance::LoadCurrentLevel);
    MenuButton->OnClickedDelegate.AddDynamic(GameInstance, &UCodeGameInstance::LoadMainMenu);
}

void UWBP_CodeResultsWidget::LoadMainMenu()
{
    MenuButton->OnClickedDelegate.Broadcast();
}
void UWBP_CodeResultsWidget::Setlose() {
    ResultsSwitch->SetActiveWidgetIndex(0);
}

void UWBP_CodeResultsWidget::SetWin()
{
    ButtonArea->SetVisibility(ESlateVisibility::Hidden);
    
    FTimerHandle MenuTimerHandle; 
    GetWorld()->GetTimerManager().SetTimer(MenuTimerHandle, this, &UWBP_CodeResultsWidget::LoadMainMenu, TimeToMenu, false);
}
