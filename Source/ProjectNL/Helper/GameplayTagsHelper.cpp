#include "GameplayTagsHelper.h"
#include "NativeGameplayTags.h"

// TODO: 해당 코드는 DefaultGameplayTags.ini 파일을 통해 자동으로 Generate될 수 있도록 처리하기
namespace NlGameplayTags
{
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_Combat, "Ability.Combat"
																, "특정 캐릭터의 전투 모드에 대한 Root Tag");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_Combat_Attack, "Ability.Combat.Attack"
																, "특정 캐릭터의 기본 공격 Tag");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_Util_DoubleJump
																, "Ability.Util.DoubleJump"
																, "현재 캐릭터가 DoubleJump가 가능한 상황임을 나타내는 Tag - (ex. 무기 및 스킬을 통해 해당 태그 확보 가능)")

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Category_Entity, "Category.Entity"
																, "해당 액터의 카테고리가 엔티티임을 나타내는 Root Tag")
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Category_Entity_Player
																, "Category.Entity.Player"
																, "해당 액터의 카테고리가 플레이어임을 나타냄")
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Category_Entity_Neutral
																, "Category.Entity.Neutral"
																, "해당 액터의 카테고리가 중립 엔티티임을 나타냄")
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Category_Entity_Enemy, "Category.Entity.Enemy"
																, "해당 액터의 카테고리가 적대적 엔티티임을 나타냄")

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Status_Combat, "Status.Combat"
																, "현재 캐릭터가 전투 모드임을 암시하는 Tag");

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(State_Player, "State.Player"
																, "현재 캐릭터의 애니메이션 상태를 표현하는 Root Tag");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(State_Player_Idle, "State.Player.Idle"
																, "현재 플레이어가 특정 애니메이션에 국한되지 않은 상태");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(State_Player_Jump, "State.Player.Jump"
																, "현재 플레이어가 일반 점프인 상태");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(State_Player_DoubleJump
																, "State.Player.DoubleJump"
																, "현재 플레이어가 더블 점프 상태");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(State_Player_Equip, "State.Player.Equip"
																, "특정 캐릭터가 전투 모드에 돌입하기 위한 무기 뽑기 과정");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(State_Player_UnEquip, "State.Player.UnEquip"
																, "특정 캐릭터가 전투 모드 종료를 위한 무기 넣기 과정");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(State_Player_Attack, "State.Player.Attack"
																, "특정 캐릭터가 공격 중인 상태임을 명시");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(State_Player_Damaged, "State.Player.Damaged"
																, "특정 캐릭터가 피격 상태임을 명시");
}
