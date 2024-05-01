#include "PreCompile.h"
#include "AttackEffect.h"

AAttackEffect::AAttackEffect()
{
	AttackEffectRenderer = CreateDefaultSubObject<USpriteRenderer>("WeaponRenderer");
	SetRoot(AttackEffectRenderer);
}

AAttackEffect::~AAttackEffect()
{
}

void AAttackEffect::BeginPlay()
{
	Super::BeginPlay();

	AttackEffectRenderer->CreateAnimation("AttackEffect", "AttackEffect", 0.1f);
	AttackEffectRenderer->SetAutoSize(UDungreedConstValue::AutoSize, true);
	AttackEffectRenderer->SetOrder(ERenderOrder::Player);
	AttackEffectRenderer->ChangeAnimation("AttackEffect");
}

void AAttackEffect::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (AttackEffectRenderer->IsCurAnimationEnd())
	{
		Destroy();
	}
}

