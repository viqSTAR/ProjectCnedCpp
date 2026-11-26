// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectCnedCpp/Character/ActorComponents/ActorInteraction.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/Actor.h"
#include "ProjectCnedCpp/Character/Hero.h"
#include "EnhancedInputComponent.h"
#include "ProjectCnedCpp/Character/Interface/I_Interaction.h"
#include "ProjectCnedCpp/Enums/E_InteractionType.h"
#include "Components/WidgetComponent.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Blueprint/UserWidget.h"
#include "ProjectCnedCpp/UI/InteractionButton.h"
#include "ProjectCnedCpp/Character/ActorComponents/ActorInventory.h"
#include "ProjectCnedCpp/Character/ActorComponents/CombatComponent.h"


// Sets default values for this component's properties
UActorInteraction::UActorInteraction()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	

	

	// ...
}


// Called when the game starts
void UActorInteraction::BeginPlay()
{
	Super::BeginPlay();

	
	
	

	Character = Cast<AHero>(GetOwner());
	if (Character) {
		Character->GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &UActorInteraction::OnOverlapBegin);
		Character->GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &UActorInteraction::OnOverlapEnd);

		if (IsValid(InteractClass)) 
			
			{
				InteractWidget = CreateWidget<UUserWidget>(GetWorld(), InteractClass);
				Widget = Cast<UInteractionButton>(InteractWidget);
			}
		if (IsValid(InteractWidget)){
			//InteractWidget->AddToViewport();
		}
			
		
		//Character->InteractComponent->SetWidget(InteractWidget);
	}
	UE_LOG(LogTemp, Warning, TEXT("Chichua"));

	// ...
	Enhanced = Cast<UEnhancedInputComponent>(Character->InputComponent);
	if (Enhanced)
	{
		Enhanced->BindAction(InteractInput, ETriggerEvent::Started, this, &UActorInteraction::PickupItem);
		Enhanced->BindAction(InteractInput, ETriggerEvent::Ongoing, this, &UActorInteraction::PickupOngoing);
		Enhanced->BindAction(InteractInput, ETriggerEvent::Completed, this, &UActorInteraction::PickupCancelled);
		Enhanced->BindAction(InteractInput, ETriggerEvent::Canceled, this, &UActorInteraction::PickupCancelled);
	}	
}


// Called every frame
void UActorInteraction::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UActorInteraction::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	UE_LOG(LogTemp, Warning, TEXT("Begin: %s"), *OtherActor->GetName());
	if (OtherActor && OtherActor->Implements<UI_Interaction>())
	{
		
		
		Widget = Cast<UInteractionButton>(InteractWidget);
		Widget->Progress->SetPercent(0);

		TapElapsed = 0;
		//II_Interaction::Execute_OnPickup(OtherActor, GetOwner());
		ItemActorArray.AddUnique(OtherActor);
		ArrayLength = ItemActorArray.Num();
		if (!ItemActorArray.IsEmpty()) { IntType = II_Interaction::Execute_GetInteractionType(ItemActorArray[ArrayLength - 1]); }
		if (Character)
		{
			Character->InteractComponent->SetWidget(InteractWidget);
			UActorInteraction::SetLocation(OtherActor, Character->InteractComponent);
			
			
			if (Widget)
			{

				const EInteractionType EIType = II_Interaction::Execute_GetInteractionType(OtherActor);
				if(Widget->Name)
				{
					Widget->Name->SetText(II_Interaction::Execute_ItemName(OtherActor));
				}
				if (Widget->Description)
				{
					Widget->Description->SetText(II_Interaction::Execute_ItemDescription(OtherActor));
				}
				if (Widget->Prompt)
				{
					FText PromptText = StaticEnum<EInteractionType>()->GetDisplayNameTextByValue(static_cast<int64>(EIType));
					if (II_Interaction::Execute_GetInteractionType(OtherActor) == EITpress)
					{
						Widget->Prompt->SetText(PromptText);
					}
					else {

						FText UnitTime;

						switch (EIType)
						{
						case EIThold:
							UnitTime = FText::FromString(TEXT("Seconds"));
							break;
						case EITtap:
							UnitTime = FText::FromString(TEXT("Times"));
							break;
						default:
							break;
						}
						Widget->Prompt->SetText(FText::Format(FText::FromString(TEXT("{0} {1} {2} ")), PromptText, FText::AsNumber(II_Interaction::Execute_ItemCounter(OtherActor)), UnitTime));

						
					}
				}
			}
		}
		for (AActor* ArrayActor : ItemActorArray)
		{
			if(ArrayActor)
			UE_LOG(LogTemp, Warning, TEXT("%s"), *ArrayActor->GetName());
		}
		
	}
}

void UActorInteraction::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	TapElapsed = 0;
	UE_LOG(LogTemp, Warning, TEXT("End: %s"), *OtherActor->GetName());
	ItemActorArray.Remove(OtherActor);
	ArrayLength = ItemActorArray.Num();
	Widget->Progress->SetPercent(0);

	if(!ItemActorArray.IsEmpty()){ IntType = II_Interaction::Execute_GetInteractionType(ItemActorArray[ArrayLength - 1]); }

	if (Character && Character->InteractComponent)
	{
		Character->InteractComponent->SetWidget(nullptr);
	}
	
	for (AActor* ArrayActor : ItemActorArray)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *ArrayActor->GetName());
	}
}

void UActorInteraction::PickupItem()
{
	if (!ItemActorArray.IsEmpty())
	{

		
		
		if(IntType == EITpress)
		{
			II_Interaction::Execute_OnPickup(ItemActorArray[ArrayLength-1], GetOwner());
		}
		if (IntType == EITtap)
		{
			float TimeCounter = II_Interaction::Execute_ItemCounter(ItemActorArray[ArrayLength -1]);
			int TapCounter = static_cast<int32>(TimeCounter);

			TapElapsed++;
			if (TapElapsed == TapCounter)
			{
				II_Interaction::Execute_OnPickup(ItemActorArray[ArrayLength - 1], GetOwner());
			}

			SetPercentages(Widget, TapElapsed, TapCounter);
		}

		

		UActorInventory* Inventory = GetOwner()->FindComponentByClass<UActorInventory>();
		UCombatComponent* Combat = GetOwner()->FindComponentByClass<UCombatComponent>();
		UItemInstance* ItemInst = nullptr;
		if (Inventory && Combat)
		{
			if (Inventory->WeaponInventory.IsValidIndex(0) && Inventory->WeaponInventory[0] && Combat->WeaponMeshA)
			{
				ItemInst = Inventory->WeaponInventory[0];
				Combat->WeaponMeshA->SetStaticMesh(ItemInst->Struct.ItemDefinition->GetDefaultObject<UItemDefinition>()->Mesh);
			}
			if (Inventory->WeaponInventory.IsValidIndex(1) && Inventory->WeaponInventory[1] && Combat->WeaponMeshB)
			{
				ItemInst = Inventory->WeaponInventory[1];
				Combat->WeaponMeshB->SetStaticMesh(ItemInst->Struct.ItemDefinition->GetDefaultObject<UItemDefinition>()->Mesh);
			}
			if (Inventory->WeaponInventory.Num() == 1)
			{
				if (Combat && Combat->CharacterState == ECharacterState::ECSUnequipped)
				{
					Combat->AttachToHostler(0);
					Combat->WeaponEquipUnEquip(0);
				}
			}
			else if(Inventory->WeaponInventory.Num() == 2) {
				if (Combat && Combat->CharacterState == ECharacterState::ECSUnequipped)
				{
					Combat->AttachToHostler(1);
					Combat->WeaponEquipUnEquip(1);
				}
				else if (Combat && Combat->CharacterState == ECharacterState::ECSEquipped)
				{
					Combat->AttachToHostler(1);
				}
				
			}
		}
		
		

		

	}
	
}


void UActorInteraction::PickupOngoing(const FInputActionInstance& Instance)
{

	if (!ItemActorArray.IsEmpty())
	{
		
		if (IntType == EIThold && !isInteracted) {
			
			TimeElapsed = Instance.GetElapsedTime();
			float TimeCounter = II_Interaction::Execute_ItemCounter(ItemActorArray[ArrayLength - 1]);
			SetPercentages(Widget, TimeElapsed, TimeCounter);
			if (TimeElapsed >= TimeCounter) { 
				II_Interaction::Execute_OnPickup(ItemActorArray[ArrayLength - 1], GetOwner()); 
				isInteracted = true;
			}
			
		}
	}
	

}

void UActorInteraction::PickupCancelled()
{
	TimeElapsed = 0.f;
	isInteracted = false;

	if (ItemActorArray.IsEmpty() || !IsValid(ItemActorArray.Last()))
	{
		return;
	}

	if (II_Interaction::Execute_GetInteractionType(ItemActorArray.Last()) == EIThold
		&& IsValid(Widget)
		&& IsValid(Widget->Progress))
	{
		Widget->Progress->SetPercent(0.f);
	}
}

void UActorInteraction::SetLocation(AActor* Other, UWidgetComponent* Component)
{
	FVector Location = II_Interaction::Execute_ItemLocation(Other);
	Component->SetWorldLocation(Location);

}

void UActorInteraction::SetPercentages(UInteractionButton* Button, float Counter, float Completed)
{
	if (Button->Progress)
	{
		Button->Progress->SetPercent(( Counter/ Completed));
	}
}





