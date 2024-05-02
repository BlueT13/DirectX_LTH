#include "PreCompile.h"
#include "AttackEffect.h"

AAttackEffect::AAttackEffect()
{
	DefaultComponent = CreateDefaultSubObject<UDefaultSceneComponent>("DefaultComponent");
	SetRoot(DefaultComponent);

	AttackEffectRenderer = CreateDefaultSubObject<USpriteRenderer>("AttackEffectRenderer");
	AttackEffectRenderer->SetupAttachment(DefaultComponent);

	AttackEffectCollision = CreateDefaultSubObject<UCollision>("AttackEffectCollision");
	AttackEffectCollision->SetupAttachment(DefaultComponent);
	// Collision은 반드시 SetCollisionGroup을 해야 한다.
	AttackEffectCollision->SetCollisionGroup(ECollisionOrder::Attack);
	AttackEffectCollision->SetCollisionType(ECollisionType::Rect);
}

AAttackEffect::~AAttackEffect()
{
}

void AAttackEffect::BeginPlay()
{
	Super::BeginPlay();

	AttackCollisionVector = { 100, 150, 100 };

	AttackEffectRenderer->CreateAnimation("AttackEffect", "AttackEffect", 0.1f);
	AttackEffectRenderer->SetAutoSize(UDungreedConstValue::AutoSize, true);
	AttackEffectRenderer->SetOrder(ERenderOrder::Player);
	AttackEffectRenderer->ChangeAnimation("AttackEffect");

	AttackEffectCollision->SetScale(AttackCollisionVector);

}

void AAttackEffect::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (AttackEffectRenderer->IsCurAnimationEnd())
	{
		Destroy();
	}
}

