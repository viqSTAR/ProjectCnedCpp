// Fill out your copyright notice in the Description page of Project Settings.



#include "ProjectCnedCpp/Character/ActorComponents/ActorHealth.h"


// Sets default values for this component's properties
UActorHealth::UActorHealth()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UActorHealth::BeginPlay()
{
	Super::BeginPlay();

	if (GetOwner())
	{
		GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UActorHealth::HandleTakeAnyDamage);
	}

	// ...
	
}


// Called every frame
void UActorHealth::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UActorHealth::HealthReduce(float DamageAmount)
{

	if (DamageAmount <= 0.f || Health <= 0.f) return;
	Health = FMath::Clamp(Health - DamageAmount, 0.f, MaxHealth);
	UE_LOG(LogTemp, Warning, TEXT("Health: %f"), Health);
}

void UActorHealth::HandleTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	UActorHealth::HealthReduce(Damage);
}




