// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryUi.generated.h"
class UVerticalBox;
/**
 * 
 */
UCLASS()
class PROJECTCNEDCPP_API UInventoryUi : public UUserWidget
{
	GENERATED_BODY()

public:	
	UPROPERTY(meta = (BindWidget))
	UVerticalBox* InventoryWrapBox;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TSubclassOf<UUserWidget> InventoryItemClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	int32 MaxInventoryItems = 20;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TArray<UUserWidget*> InventoryItems;
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void AddItemToInventory();
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void RemoveItemFromInventory(UUserWidget* Item);
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void ClearInventory();

	class UActorInventory* InventoryComponent;
	
};
