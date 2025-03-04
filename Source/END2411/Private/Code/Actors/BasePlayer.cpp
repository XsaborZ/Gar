// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Actors/BasePlayer.h"  // this should always be first
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

#include "Code/Actors/CodeRifle.h"

#include "Both/PlayerHUD.h"

#include "../END2411.h"

ABasePlayer::ABasePlayer()
{
	PrimaryActorTick.bStartWithTickEnabled = false;
	PrimaryActorTick.bCanEverTick = false;

	// Allocating memory
	
#pragma region Day 1 SpringArm & Camera

	// Spring Arm
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetRelativeLocation(FVector(0.0f,80.0f,90.0f)); // changed day 6

	SpringArm->TargetArmLength = 205.0f; //added day 6

	SpringArm->SetupAttachment(GetRootComponent()  /*, only need to use this if using sockets, used in week 2 */ );

#pragma region Day 2 allow rotation to be applied to springarm Pitch not to camera
	// spring arm rotation turned on for pitch
	SpringArm->bUsePawnControlRotation = true;
	// camera rotation turned off for pitch
	//Camera->bUsePawnControlRotation = false;
#pragma endregion

	// Camera
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);  

#pragma endregion


}

void ABasePlayer::BeginPlay() {
	Super::BeginPlay();

	PlayerController = Cast<APlayerController>(GetController());

	if (PlayerController && WidgetClass) {
		PlayerHUDWidget = CreateWidget<UUserWidget>(PlayerController, WidgetClass);
		if (PlayerHUDWidget) {
			PlayerHUDWidget->AddToViewport();
			UE_LOG(Game, Log, TEXT("Player HUD Widget created and added to viewport"));
		}
		else {
			UE_LOG(Game, Error, TEXT("Failed to create Player HUD Widget"));
			Destroy();
		}
	}
	else {
		UE_LOG(Game, Error, TEXT("We need a valid PlayerController and WidgetClass"));
		Destroy();
	}

}

void ABasePlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
#pragma region Day 2 Camera rotation added

	// Always call your parent function
	// ** if you want it's same functionality
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// camera
	PlayerInputComponent->BindAxis("TurnRight", this, &ABasePlayer::AddControllerYawInput);  // left and right - only camera
	PlayerInputComponent->BindAxis("LookUp", this, &ABasePlayer::AddControllerPitchInput);  // up and down - only to spring arm

#pragma endregion

#pragma region Day 3 Movement

	// Movement
	PlayerInputComponent->BindAxis("MoveForward", this, &ABasePlayer::InputAxisMoveForward); // Move Forward and backwards
	PlayerInputComponent->BindAxis("Strafe", this, &ABasePlayer::InputAxisStrafe);	// move left and right

#pragma endregion


	PlayerInputComponent->BindAction("AttackInput", EInputEvent::IE_Pressed, this, &ABasePlayer::AttackInput);


}

#pragma region Day 3 Movement axis functions

void ABasePlayer::InputAxisMoveForward(float AxisValue)
{
	//FRotator Break = GetControlRotation();
	//FRotator Make(0., Break.Yaw, 0.);
	//FVector WorldDirection = Make.Vector();
	//FRotator(0., GetControlRotation().Yaw, 0.).Vector() does the same thing as above
	AddMovementInput(FRotator(0., GetControlRotation().Yaw, 0.).Vector(), AxisValue);
}

void ABasePlayer::InputAxisStrafe(float AxisValue)
{
	AddMovementInput(FRotationMatrix(FRotator(0., GetControlRotation().Yaw, 0.)).GetScaledAxis(EAxis::Y), AxisValue);
}

#pragma endregion



void ABasePlayer::AttackInput()
{
	Rifle->Attack(); 
}

void ABasePlayer::HandleHurt(float Ratio)
{
	Super::HandleHurt(Ratio);
	UPlayerHud* HUD = Cast<UPlayerHud>(PlayerHUDWidget);
	HUD->SetHealth(Ratio);
	
}

void ABasePlayer::HandleDeadStart(float Ratio)
{
	Super::HandleDeadStart(Ratio);
	UPlayerHud* HUD = Cast<UPlayerHud>(PlayerHUDWidget);
	HUD->SetHealth(Ratio);
	DisableInput(PlayerController);
}

FRotator ABasePlayer::GetBaseAimRotation() const
{
	// return the rotaton based on reticle location
	Super::GetBaseAimRotation();
	FVector Destination = Cast<UPlayerHud>(PlayerHUDWidget)->GetDestinationCode();
	FVector Direction = Destination - Rifle->GetSource(); 
	FRotator NewRotation = FRotationMatrix::MakeFromX(Direction).Rotator(); 

	return NewRotation; 
}
