// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ProjectCnedCpp/Item/ItemInstance.h"
#include "ProjectCnedCpp/Item/ItemDefinition.h"
#include "ActorInventory.generated.h"


class UItemDefinition;
class UItemInstance;

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

	TArray<TObjectPtr<UItemInstance>> ItemInventory;

	void Add(TSubclassOf<UItemDefinition> ItemDef);

	

		
};
