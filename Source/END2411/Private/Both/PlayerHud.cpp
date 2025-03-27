// Fill out your copyright notice in the Description page of Project Settings.


#include "Both/PlayerHud.h"
#include "Components/ProgressBar.h"
#include "Components/Image.h"
#include "Code/Actors/CodeRifle.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Blueprint/SlateBlueprintLibrary.h"
#include "Components/TextBlock.h"
#include "Code/Actors/Spawner.h"
#include "GameFramework/PlayerController.h"

#include "../END2411.h"

void UPlayerHud::NativeConstruct()
{
	Super::NativeConstruct();

	DynamicMaterial = Crosshair->GetDynamicMaterial();
}

void UPlayerHud::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	FGeometry Geometry = Crosshair->GetCachedGeometry();
	FVector2D GeometryAbsoluteSize = Geometry.GetAbsoluteSize();
	FVector2D HalfSize = GeometryAbsoluteSize * 0.5f;
	FVector2D PixelPosition, ViewportPosition;
	USlateBlueprintLibrary::LocalToViewport(GetWorld(), Geometry, FVector2D(0, 0), PixelPosition, ViewportPosition);

	PixelPosition += HalfSize;

	APlayerController* PlayerController = GetOwningPlayer();
	if (!PlayerController) {
		return;
	}


	FVector WorldPosition, WorldDirection, Start, End;
	if (PlayerController->DeprojectScreenPositionToWorld(PixelPosition.X, PixelPosition.Y, WorldPosition, WorldDirection)) {
		Start = WorldPosition;
		End = (WorldDirection * 100000.0f) + WorldPosition;
		FCollisionObjectQueryParams ObjectQueryParams;
		ObjectQueryParams.AddObjectTypesToQuery(ECC_Pawn);
		ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);


		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(GetOwningPlayerPawn());

		APawn* Pawn = GetOwningPlayerPawn();
		QueryParams.AddIgnoredActor(Pawn);
		QueryParams.AddIgnoredActor(PlayerController->GetPawn());


		FHitResult HitResult;
		if (GetWorld()->LineTraceSingleByObjectType(HitResult, Start, End, ObjectQueryParams, QueryParams))
		{
			EndPointCode = HitResult.Location;
			APawn* HitPawn = Cast<APawn>(HitResult.GetActor());
			ASpawner* HitSpawner = Cast<ASpawner>(HitResult.GetActor());
			if (HitPawn || HitSpawner)
			{
				DynamicMaterial->SetVectorParameterValue(ColorName, DangerColor);
			}
			else
			{
				DynamicMaterial->SetVectorParameterValue(ColorName, SafeColor);
			}
		}
		else
		{
			EndPointCode = End;
			DynamicMaterial->SetVectorParameterValue(ColorName, SafeColor);
		}
	}
}

FVector UPlayerHud::GetDestinationCode() const
{
	return EndPointCode;
}

FVector UPlayerHud::GetDestination() const
{
	return EndPointCode;
}



void UPlayerHud::SetHealth_Implementation(float newPercentHealth)
{
	HealthBar->SetPercent(newPercentHealth); 
	//UE_LOG(Game, Log, TEXT("Percent = %f"), newPercentHealth);
}

void UPlayerHud::SetAmmo_Implementation(float Current, float Max) 
{
	// set current and max ammo
	int intCurr = static_cast<int>(Current);
	FString StringCurr = FString::Printf(TEXT("%d"), intCurr);
	CurrentAmmo->SetText(FText::FromString(StringCurr));
	int intMax = static_cast<int>(Max);
	FString StringMax = FString::Printf(TEXT("%d"), intMax);
	MaxAmmo->SetText(FText::FromString(StringMax));
}
