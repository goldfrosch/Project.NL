﻿#include "GameplayTagsHelper.h"
#include "NativeGameplayTags.h"

// TODO: 해당 코드는 DefaultGameplayTags.ini 파일을 통해 자동으로 Generate될 수 있도록 처리하기
namespace NlGameplayTags
{
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_Combat, "Ability.Combat"
																, "특정 캐릭터의 전투 모드에 대한 Root Tag");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_Combat_Attack, "Ability.Combat.Attack"
																, "특정 캐릭터의 기본 공격 Tag");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Status_Combat, "Status.Combat"
																, "현재 캐릭터가 전투 모드임을 암시하는 Tag");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(State_Player, "State.Player"
																, "현재 캐릭터의 애니메이션 상태를 표현하는 Root Tag");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(State_Player_Idle, "State.Player.Idle"
																, "현재 플레이어가 특정 애니메이션에 국한되지 않은 상태");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(State_Player_Equip, "State.Player.Equip"
																, "특정 캐릭터가 전투 모드에 돌입하기 위한 무기 뽑기 과정");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(State_Player_UnEquip, "State.Player.UnEquip"
																, "특정 캐릭터가 전투 모드 종료를 위한 무기 넣기 과정");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(State_Player_Attack, "State.Player.Attack"
																, "특정 캐릭터가 공격 중인 상태임을 명시");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(State_Player_Damaged, "State.Player.Damaged"
																, "특정 캐릭터가 피격 상태임을 명시");
}