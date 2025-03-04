// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Actors/Agent.h"
#include "Code/Actors/CodeRifle.h" 

AAgent::AAgent()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AAgent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	InputAction();
}

void AAgent::PostRegisterAllComponents()
{
	Super::PostRegisterAllComponents();

	GetMesh()->SetVectorParameterValueOnMaterials("Tint", FVector{ 1.0f, 0.612817f, 0.0f });
}

void AAgent::InputAction()
{
	if (Rifle)
		Rifle->Attack();
}
