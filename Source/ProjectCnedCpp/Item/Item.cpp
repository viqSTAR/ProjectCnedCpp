// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectCnedCpp/Item/Item.h"
#include "ProjectCnedCpp/Item/ItemDefinition.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Components/SceneComponent.h"
#include "ProjectCnedCpp/ItemFragments/IF_InteractionType.h"
#include "ProjectCnedCpp/Character/ActorComponents/ActorInventory.h"


// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(MeshComponent);
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	SphereComponent->SetupAttachment(RootComponent);
	SphereComponent->SetSphereRadius(25.f);
	
	

}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();

	
	
	if (ItemInfo.ItemDefinition->GetDefaultObject<UItemDefinition>()->Mesh)
		MeshComponent->SetStaticMesh(ItemInfo.ItemDefinition->GetDefaultObject<UItemDefinition>()->Mesh);
	//ItemInfo.ItemDefinition = UItemA;
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItem::OnPickup_Implementation(AActor* Actor)
{
	UE_LOG(LogTemp, Warning, TEXT("%s picked %s"), *Actor->GetName(), *GetName());
	UActorInventory* Inventory = Actor->FindComponentByClass<UActorInventory>();
	if (Inventory)
	{
		Inventory->Add(ItemInfo.ItemDefinition);
	}
	
}

EInteractionType AItem::GetInteractionType_Implementation()

{
	const UIF_InteractionType* Fragment = Cast<UIF_InteractionType>(ItemInfo.ItemDefinition->GetDefaultObject<UItemDefinition>()->FindFragmentByClass(ItemInfo.ItemDefinition, UIF_InteractionType::StaticClass()));
	if (Fragment)
	{
		
		return Fragment->InteractionType.GetValue();
	}
	else
	{
		return EITpress;
	}
	return EInteractionType();
}

float AItem::ItemCounter_Implementation()
{
	const UIF_InteractionType* Fragment = Cast<UIF_InteractionType>(ItemInfo.ItemDefinition->GetDefaultObject<UItemDefinition>()->FindFragmentByClass(ItemInfo.ItemDefinition, UIF_InteractionType::StaticClass()));

	if (Fragment)
	{
		return Fragment->ItemCounter;
	}
	return 1.f;
}

FText AItem::ItemName_Implementation()
{
	if (ItemInfo.ItemDefinition->GetDefaultObject<UItemDefinition>())
	{
		return ItemInfo.ItemDefinition->GetDefaultObject<UItemDefinition>()->ItemName;
	}
	
	return FText::FromString(TEXT("Item"));
}

FText AItem::ItemDescription_Implementation()
{
	if (ItemInfo.ItemDefinition->GetDefaultObject<UItemDefinition>())
	{
		return ItemInfo.ItemDefinition->GetDefaultObject<UItemDefinition>()->ItemDescription;
	}
	return FText::FromString(TEXT("Description"));
}

FVector AItem::ItemLocation_Implementation()
{
	
		return FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z + 100.f);
	
}



