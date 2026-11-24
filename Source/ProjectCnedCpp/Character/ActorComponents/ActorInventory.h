// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ProjectCnedCpp/Item/ItemInstance.h"
#include "ProjectCnedCpp/Item/ItemDefinition.h"
#include "ActorInventory.generated.h"


class UItemDefinition;
class UItemInstance;
class UInputAction;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTCNEDCPP_API UActorInventory : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UActorInventory();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TArray<TObjectPtr<UItemInstance>> ItemInventory;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TArray<TObjectPtr<UItemInstance>> WeaponInventory;


	void Add(TSubclassOf<UItemDefinition> ItemDef);

	UFUNCTION(BlueprintCallable)
	void Drop(UItemInstance* ItemInst);

	class UEnhancedInputComponent* Enhanced;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> InventoryInput;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory")
	TSubclassOf<UUserWidget> InventoryWidget;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TSubclassOf<UUserWidget> WeaponInventoryWidget;

	void ShowInventory();

	void HideInventory();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UsableInstances")
	UItemInstance* usableInstance = nullptr;

protected:
	UPROPERTY(Transient)
	TObjectPtr<UUserWidget> InventoryUI;
	UPROPERTY(Transient)
	TObjectPtr<UUserWidget> WeaponInventoryUI;
		
};
