// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectCnedCpp/Character/ActorComponents/ActorInventory.h"
#include "EnhancedInputComponent.h"
#include "InputAction.h"
#include "Blueprint/UserWidget.h"
#include "ProjectCnedCpp/Item/Item.h"
#include "ProjectCnedCpp/ItemFragments/IF_ItemType.h"
#include "ProjectCnedCpp/UI/InventoryUi.h"
#include "ProjectCnedCpp/ItemFragments/IF_ItemAction.h"

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

	if (InventoryWidget)
	{
		InventoryUI = CreateWidget<UUserWidget>(GetWorld(), InventoryWidget);
	}

	// ...
	if (GetOwner())
	{
		Enhanced = Cast<UEnhancedInputComponent>(GetOwner()->InputComponent);
	}
	if (Enhanced)
	{
		Enhanced->BindAction(InventoryInput, ETriggerEvent::Started, this, &UActorInventory::ShowInventory);
		Enhanced->BindAction(InventoryInput, ETriggerEvent::Completed, this, &UActorInventory::HideInventory);
		Enhanced->BindAction(InventoryInput, ETriggerEvent::Canceled, this, &UActorInventory::HideInventory);
	}

	UInventoryUi* InventoryRef = Cast<UInventoryUi>(InventoryUI);

	if (InventoryRef)
	{
		InventoryRef->InventoryComponent = this;
		InventoryRef->OnInventoryChanged.AddUObject(InventoryRef, &UInventoryUi::AddItemToInventory);
	}
	
	
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

		const UIF_ItemType* ActionFragment = Cast<UIF_ItemType>(UItemDefinition::FindFragmentByClass(Instance
			->Struct.ItemDefinition, UIF_ItemType::StaticClass()));

		EItemType ItemType = ActionFragment ? ActionFragment->ItemType.GetValue() : EItemType::EITItem;

		if (ItemType == EITWeapon)
		{
			if (WeaponInventory.Num() < 2)
			{
				WeaponInventory.Add(Instance);
			}
			else
			{
				WeaponInventory[0] = Instance;
			}
			return;
		}
		
		for (UItemInstance* Item : ItemInventory)
		{
			if (Item->Struct.ItemDefinition == ItemDef)
			{
				Item->Struct.StackCount++;
				UInventoryUi* InventoryRef = Cast<UInventoryUi>(InventoryUI);
				if (InventoryRef)
				{
					InventoryRef->OnInventoryChanged.Broadcast();
				}
				return;
			}
		}


			ItemInventory.Add(Instance);

		

		UE_LOG(LogTemp, Warning, TEXT("ItemAdded"));
		
	}
	UInventoryUi* InventoryRef = Cast<UInventoryUi>(InventoryUI);
	if (InventoryRef)
	{
		InventoryRef->OnInventoryChanged.Broadcast();
	}
}

void UActorInventory::Drop(UItemInstance* ItemInst)
{
	
	if (ItemInst)
	{
		UItemInstance* Instance = ItemInst;
		if (Instance && GetWorld() && GetOwner())
		{
			if (usableInstance == Instance)
			{
				usableInstance = nullptr;
			}
			if (Instance->Struct.StackCount > 1)
			{
				Instance->Struct.StackCount--;
			}
			else
			{
				ItemInventory.Remove(Instance);
			}
			

			FTransform SpawnTransform(FRotator::ZeroRotator, GetOwner()->GetActorLocation() + GetOwner()->GetActorForwardVector() * 200.f );
			
			AItem* Droppeditem = GetWorld()->SpawnActorDeferred<AItem>(AItem::StaticClass(), SpawnTransform);
			
			if (Droppeditem)
			{
				Droppeditem->ItemInfo.ItemDefinition = Instance->Struct.ItemDefinition;

				Droppeditem->FinishSpawning(SpawnTransform);
			}
			
			
		}
	}
	UInventoryUi* InventoryRef = Cast<UInventoryUi>(InventoryUI);
	if (InventoryRef)
	{
		InventoryRef->OnInventoryChanged.Broadcast();
	}
}

void UActorInventory::ShowInventory()
{
	if (InventoryUI)
	{
		InventoryUI->AddToViewport();
		if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
		{
			PC->bShowMouseCursor = true;
			PC->SetInputMode(FInputModeGameAndUI());
			int32 ViewportX, ViewportY;
			PC->GetViewportSize(ViewportX, ViewportY);
			PC->SetMouseLocation(ViewportX / 2, ViewportY / 2);
			
		}
		UInventoryUi* InventoryRef = Cast<UInventoryUi>(InventoryUI);
		if (InventoryRef)
		{
			InventoryRef->InventoryComponent = this;
			InventoryRef->AddItemToInventory();

		}
	}
}

void UActorInventory::HideInventory()
{
	if (usableInstance != nullptr)
	{
		
		for (UItemInstance* Item : ItemInventory)
		{
			if (Item == usableInstance)
			{
				const UIF_ItemAction* ActionFragment = Cast<UIF_ItemAction>(Item->Struct.ItemDefinition->GetDefaultObject<UItemDefinition>()->FindFragmentByClass(Item->Struct.ItemDefinition,UIF_ItemAction::StaticClass()));

				if (ActionFragment && GetOwner())
				{
					ActionFragment->UseItemAction(GetOwner());
				}
				
				
				
				if (Item->Struct.StackCount > 1)
				{
					Item->Struct.StackCount--;
				}
				else
				{
					ItemInventory.Remove(Item);
				}
				break;
			}
		}
		usableInstance = nullptr;
	}
	if (InventoryUI)
	{
		InventoryUI->RemoveFromParent();
	}
	if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
	{
		PC->bShowMouseCursor = false;
		PC->SetInputMode(FInputModeGameOnly());
		

	}
}

