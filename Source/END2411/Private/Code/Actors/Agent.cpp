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
	UpdateBlackboardHealth(1.0f);
	Rifle->OnAmmoChanged.AddDynamic(this, &AAgent::UpdateBlackboardAmmo);
	Rifle->ReloadAmmo();
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

void AAgent::EnemyReload_Implementation()
{
	if (Rifle) {
		Rifle->RequestReload();
	}

}



void AAgent::HandleActionFinished()
{ 

	// Send AI Message "ActionFinished"
	FAIMessage::Send(this, FAIMessage(FName("ActionFinished"), this, true));
	//UE_LOG(LogTemp, Warning, TEXT("Sent ai message"));
	
}

void AAgent::UpdateBlackboardHealth(float Ratio)
{
	AAIController* aiController;
	APawn* AsPawn = Cast<APawn>(GetController());
	if (AsPawn != nullptr)
	{
		aiController = Cast<AAIController>(AsPawn->GetController());
	}
	else {
		aiController = Cast<AAIController>(GetController());
	}
	if (aiController && aiController->GetBlackboardComponent()) 
	{
		// Get the Blackboard component from the AI Controller
		UBlackboardComponent* Blackboard = aiController->GetBlackboardComponent(); 

		// Set the value of the HealthRatio key on the Blackboard
		Blackboard->SetValueAsFloat(TEXT("HealthRatio"), Ratio); 
	}
}

void AAgent::UpdateBlackboardAmmo(float Current, float Max)
{
	AAIController* aiController;
	APawn* AsPawn = Cast<APawn>(GetController());
	if (AsPawn != nullptr)
	{
		aiController = Cast<AAIController>(AsPawn->GetController());
	}
	else {
		aiController = Cast<AAIController>(GetController());
	}
	if (aiController && aiController->GetBlackboardComponent())
	{
		// Get the Blackboard component from the AI Controller
		UBlackboardComponent* Blackboard = aiController->GetBlackboardComponent();

		// Set the value of the Ammo key on the Blackboard
		Blackboard->SetValueAsFloat(TEXT("Ammo"), Current);
	}
}

void AAgent::HandleHurt(float Ratio)
{
	UpdateBlackboardHealth(Ratio);
}
