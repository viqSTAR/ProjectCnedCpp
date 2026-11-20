// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InputAction.h"
#include "ProjectCnedCpp/Enums/E_InteractionType.h"
#include "ActorInteraction.generated.h"

class UInputAction;
class AActor;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTCNEDCPP_API UActorInteraction : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UActorInteraction();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;



public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void OnOverlapBegin(
		UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult
	);
	UFUNCTION()
	void OnOverlapEnd(
		UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex
	);

	class AHero* Character;

	UPROPERTY(BlueprintReadOnly)
	TArray<TObjectPtr<AActor>> ItemActorArray;

	void PickupItem();

	void PickupItemOnType();

	void PickupOngoing(const FInputActionInstance& Instance);
	void PickupCancelled();

	float TimeElapsed = 0.f;
	int TapElapsed = 0;
	EInteractionType IntType = EInteractionType::EITpress;

	int ArrayLength;

	class UEnhancedInputComponent* Enhanced;
	

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> InteractInput;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UWidgetComponent* InteractComponent; 

	UPROPERTY()
	class UUserWidget* InteractWidget;

	UPROPERTY(EditDefaultsOnly, Category = "UserInteract")
	TSubclassOf<UUserWidget> InteractClass;

	UPROPERTY()
	class UInteractionButton* Widget;

private:
	bool isInteracted = false;

	void SetLocation(AActor* Other, UWidgetComponent* Component);

	void SetPercentages(class UInteractionButton* Button, float Counter, float Completed);

	
		
};
