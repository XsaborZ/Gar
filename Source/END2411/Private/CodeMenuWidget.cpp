// Fill out your copyright notice in the Description page of Project Settings.


#include "CodeMenuWidget.h"
#include "Both/CodeButton.h"
#include "Kismet/GameplayStatics.h"
#include "Utility/CodeGameInstance.h"

void UCodeMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(GetWorld());
	UCodeGameInstance* CodeGameInstance = Cast<UCodeGameInstance>(GameInstance); 

	if (CodeGameInstance) {

		StartGameButton->OnClickedDelegate.AddDynamic(CodeGameInstance, &UCodeGameInstance::LoadFirstLevel);
		QuitGameButton->OnClickedDelegate.AddDynamic(CodeGameInstance, &UCodeGameInstance::QuitGame);
	}
}
