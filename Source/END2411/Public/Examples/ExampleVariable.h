// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ExampleVariable.generated.h"

UCLASS(ABSTRACT) 
class END2411_API AExampleVariable : public AActor
{
	GENERATED_BODY() 
	
public:	
	// Sets default values for this actor's properties
	AExampleVariable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool CPlusPlusOnly; // not seen by blueprint

	// Read Only Types Exposed to Blueprint
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Variables|ReadOnly") // node creation
	bool VisibleAnywhere;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Variables|ReadOnly")
	uint8 VisibleDefaultsOnly; // byte

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Variables|ReadOnly")
	int32 VisibleInstanceOnlyOdd; // int
	
	UPROPERTY(VisibleInstanceOnly, Category = "Variables|ReadOnly")
	int64 VisibleInstanceOnly; // int

	// Exposed as Read Write Types
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables|ReadWrite") // write node
	float EditAnywhere;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Variables|ReadWrite")
	FName EditDefaultsOnlyOdd; 
	
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Variables|ReadWrite")
	FString EditInstanceOnlyOdd; 

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Variables|ReadWrite")
	FText EditDefaultsOnly;
	
	UPROPERTY(EditInstanceOnly, Category = "Variables|ReadWrite")
	FVector EditInstanceOnly;

	// Class Reference
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Variable|ClassReference")
	TSubclassOf<AActor> ClassType;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
