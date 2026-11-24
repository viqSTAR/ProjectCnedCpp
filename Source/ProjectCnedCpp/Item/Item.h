// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectCnedCpp/Item/ItemInfo.h"
#include "ProjectCnedCpp/Character/Interface/I_Interaction.h"
#include "ProjectCnedCpp/Enums/E_InteractionType.h"
#include "Item.generated.h"

class UIF_InteractionType;

UCLASS()
class PROJECTCNEDCPP_API AItem : public AActor, public II_Interaction
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FInventoryItemInfo ItemInfo;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	class UStaticMeshComponent* MeshComponent;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	class USphereComponent* SphereComponent;
	


	virtual void OnPickup_Implementation(AActor* Actor) override;

	virtual EInteractionType GetInteractionType_Implementation() override;

	virtual float ItemCounter_Implementation() override;
	virtual FText ItemName_Implementation() override;
	virtual FText ItemDescription_Implementation() override;
	virtual FVector ItemLocation_Implementation() override;
	virtual EItemType GetItemType_Implementation() override;
	
	


	

};
