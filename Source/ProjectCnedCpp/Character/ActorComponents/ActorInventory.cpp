// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectCnedCpp/Character/ActorComponents/ActorInventory.h"

// Sets default values for this component's properties
UActorInventory::UActorInventory()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UActorInventory::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UActorInventory::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UActorInventory::Add(TSubclassOf<UItemDefinition> ItemDef)
{
	if (ItemDef)
	{
		UItemDefinition* Definition = ItemDef.GetDefaultObject();
		UItemInstance* Instance = NewObject<UItemInstance>(this);
		Instance->Initialize(Definition);

		ItemInventory.Add(Instance);

		UE_LOG(LogTemp, Warning, TEXT("ItemAdded"));
		
	}
}

