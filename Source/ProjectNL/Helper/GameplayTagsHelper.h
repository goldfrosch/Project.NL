#pragma once
#include "NativeGameplayTags.h"

struct FGameplayTag;

namespace NlGameplayTags
{
	PROJECTNL_API FGameplayTag FindTagByString(const FString& TagString
																						, bool bMatchPartialString = false);

	PROJECTNL_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Combat)
	PROJECTNL_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Combat_Attack)
	PROJECTNL_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Status_Combat)
	PROJECTNL_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Player)
	PROJECTNL_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Player_Idle)
	PROJECTNL_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Player_Equip)
	PROJECTNL_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Player_UnEquip)
	PROJECTNL_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Player_Attack)
	PROJECTNL_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Player_Damaged)
}
