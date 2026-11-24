// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ProjectCnedCpp/Enums/E_InteractionType.h"
#include "ProjectCnedCpp/Item/ItemType.h"
#include "I_Interaction.generated.h"


// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UI_Interaction : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECTCNEDCPP_API II_Interaction
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void OnPickup(AActor* Actor);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	EInteractionType GetInteractionType();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	EItemType GetItemType();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	float ItemCounter();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	FText ItemName();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	FText ItemDescription();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	FVector ItemLocation();


	
};
