// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Actors/Agent.h"
#include "Code/Actors/CodeRifle.h" 
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BrainComponent.h"

AAgent::AAgent()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;
}

void AAgent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	InputAction();
}
void AAgent::BeginPlay() 
{
	Super::BeginPlay();

	Rifle->OnActionStopped.AddDynamic(this, &AAgent::HandleActionFinished);
}

void AAgent::PostRegisterAllComponents()
{
	Super::PostRegisterAllComponents();

	GetMesh()->SetVectorParameterValueOnMaterials("Tint", FVector{ 1.0f, 0.612817f, 0.0f });
}

void AAgent::InputAction()
{
	PerformAttack();
}

void AAgent::PerformAttack_Implementation()
{
	if (Rifle)
		Rifle->Attack();
	else {
		UE_LOG(LogTemp, Warning, TEXT("Agent has no weapon!"));
	}
}

void AAgent::HandleActionFinished()
{ 

	// Send AI Message "ActionFinished"
	FAIMessage::Send(this, FAIMessage(FName("ActionFinished"), this, true));
	
}