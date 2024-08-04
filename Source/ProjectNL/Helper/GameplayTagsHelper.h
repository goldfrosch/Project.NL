﻿#pragma once
#include "NativeGameplayTags.h"

struct FGameplayTag;

namespace NlGameplayTags
{
	PROJECTNL_API FGameplayTag FindTagByString(const FString& TagString
																						, bool bMatchPartialString = false);

	PROJECTNL_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Combat)
	PROJECTNL_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Combat_Attack)
	PROJECTNL_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Util_DoubleJump)
	PROJECTNL_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Category_Entity)
	PROJECTNL_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Category_Entity_Player)
	PROJECTNL_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Category_Entity_Neutral)
	PROJECTNL_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Category_Entity_Enemy)
	PROJECTNL_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Status_Combat)
	PROJECTNL_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Player)
	PROJECTNL_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Player_Idle)
	PROJECTNL_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Player_Jump)
	PROJECTNL_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Player_DoubleJump)
	PROJECTNL_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Player_Equip)
	PROJECTNL_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Player_UnEquip)
	PROJECTNL_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Player_Attack)
	PROJECTNL_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(State_Player_Damaged)
}
