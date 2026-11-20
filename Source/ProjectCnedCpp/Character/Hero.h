// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Hero.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class UActorInteraction;

UCLASS()
class PROJECTCNEDCPP_API AHero : public ACharacter
{
	GENERATED_BODY()

	

public:
	// Sets default values for this character's properties
	AHero();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	USpringArmComponent* CameraBoom;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	UCameraComponent* FollowCamera;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputMappingContext* IMC;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* MoveInput;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* LookInput;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* SprintInput;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	UInputAction* JumpInput;
	

	UCharacterMovementComponent* MovementComponent;

	float DeltaTimeI;

	UPROPERTY(VisibleAnywhere, Category = "Bools")
	bool IsJumping = false;

	
	void Move(const FInputActionValue& value);

	void Look(const FInputActionValue& value);
	
	void Sprint(const FInputActionValue& value);

	void EnhancedJump(const FInputActionValue& value);

	virtual void OnJumped_Implementation() override;

	virtual void Landed(const FHitResult& Hit) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UWidgetComponent* InteractComponent;


	

	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly)
	TObjectPtr<UActorInteraction> InteractionComponent;

};
