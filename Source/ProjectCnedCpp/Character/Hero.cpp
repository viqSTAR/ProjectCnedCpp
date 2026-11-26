// Fill out your copyright notice in the Description page of Project Settings.



#include "ProjectCnedCpp/Character/Hero.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "ProjectCnedCpp/Character/ActorComponents/ActorInventory.h"
#include "ProjectCnedCpp/Character/ActorComponents/ActorInteraction.h"
#include "ProjectCnedCpp/Character/ActorComponents/CombatComponent.h"




// Sets default values
AHero::AHero()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ViewCamera"));
	FollowCamera->SetupAttachment(CameraBoom);
	InteractionComponent = CreateDefaultSubobject<UActorInteraction>(TEXT("Interaction"));
	InventoryComponent = CreateDefaultSubobject<UActorInventory>(TEXT("Inventory"));
	CombatComponent = CreateDefaultSubobject<UCombatComponent>(TEXT("Combat"));
	InteractComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("InteractWidget"));
	//InteractComponent->SetupAttachment(GetRootComponent());
	InteractComponent->SetWidgetSpace(EWidgetSpace::Screen);
	InteractComponent->SetDrawSize(FVector2D(100.f, 40.f));
	
	

}

// Called when the game starts or when spawned
void AHero::BeginPlay()
{
	Super::BeginPlay();

	if (InteractionComponent)
	{
		AddInstanceComponent(InteractionComponent);
		InteractionComponent->RegisterComponent();
	}

	

	MovementComponent = this->GetCharacterMovement();
	MovementComponent->MaxWalkSpeed = 300.f;

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer())
		{
			if (UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
			{
				if (IMC)
				{
					InputSystem->AddMappingContext(IMC, 0);
				}
			}
		}
	}
	
	
}

// Called every frame
void AHero::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	DeltaTimeI = DeltaTime;

}

// Called to bind functionality to input
void AHero::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	Input->BindAction(MoveInput, ETriggerEvent::Triggered, this, &AHero::Move);
	Input->BindAction(LookInput, ETriggerEvent::Triggered, this, &AHero::Look);
	Input->BindAction(JumpInput, ETriggerEvent::Started, this, &AHero::EnhancedJump);
	Input->BindAction(SprintInput, ETriggerEvent::Ongoing, this, &AHero::Sprint);
	Input->BindAction(SprintInput, ETriggerEvent::Canceled, this, &AHero::Sprint);
	Input->BindAction(SprintInput, ETriggerEvent::Completed, this, &AHero::Sprint);


}

void AHero::Move(const FInputActionValue& value)
{
	FVector2D MoveValue = value.Get<FVector2D>();

	const FRotator ControlRotation = GetControlRotation();

	const FRotator YawRotation(0.f, ControlRotation.Yaw, 0.f);

	const FVector Right = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	const FVector Forward = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

	AddMovementInput(Forward, MoveValue.Y);
	AddMovementInput(Right, MoveValue.X);

}

void AHero::Look(const FInputActionValue& value)
{
	FVector2D LookValue = value.Get<FVector2D>();
	AddControllerYawInput(LookValue.X);
	AddControllerPitchInput(LookValue.Y);
}

void AHero::Sprint(const FInputActionValue& value)
{
	bool IsSprinting = value.Get<bool>();
	MovementComponent->MaxWalkSpeed = IsSprinting ? 900.f : 300.f;
}

void AHero::EnhancedJump(const FInputActionValue& value)
{

	if (IsJumping == false)
	{
		Jump();
	}

}

void AHero::OnJumped_Implementation()
{
	Super::OnJumped_Implementation();
	IsJumping = true;
}

void AHero::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);
	
	FTimerHandle DelayHandle;
	GetWorldTimerManager().SetTimer(DelayHandle, FTimerDelegate::CreateLambda([this]()
		{
			IsJumping = false;
		}), 0.2f, false);

	

}






