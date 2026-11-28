#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"
//#include "MovementTags.generated.h"
//
//UCLASS()
//class PROJECTCNEDCPP_API UMovementTags : public UObject
//{
//	GENERATED_BODY()
//};

namespace MovementTags{
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_State_DontMove);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_State_DontMove_Attacking);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_State_DontMove_Equipping);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_State_DontMove_Stunned);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_State_DontMove_Frozen);
}
