#include "GameplayTagsHelper.h"
#include "NativeGameplayTags.h"

// TODO: 해당 코드는 DefaultGameplayTags.ini 파일을 통해 자동으로 Generate될 수 있도록 처리하기
namespace NlGameplayTags
{
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_Combat, "Ability.Combat", "특정 캐릭터의 전투 모드에 대한 Root Tag");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_Combat_Attack, "Ability.Combat.Attack", "특정 캐릭터의 기본 공격 Tag");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_Combat_Sheathing, "Ability.Combat.Sheathing"
																, "특정 캐릭터가 전투 모드에 돌입하기 위한 무기 뽑기 과정");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Ability_Combat_UnSheathing, "Ability.Combat.UnSheathing"
																, "특정 캐릭터가 전투 모드 종료를 위한 무기 넣기 과정");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(Status_Combat, "Status.Combat", "현재 캐릭터가 전투 모드임을 암시하는 Tag");
}
