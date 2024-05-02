#include "PreCompile.h"
#include "PlayerAttEffect.h"

APlayerAttEffect::APlayerAttEffect()
{
	DefaultComponent = CreateDefaultSubObject<UDefaultSceneComponent>("DefaultComponent");
	SetRoot(DefaultComponent);

	PlayerAttEffectRenderer = CreateDefaultSubObject<USpriteRenderer>("AttackEffectRenderer");
	PlayerAttEffectRenderer->SetupAttachment(DefaultComponent);

	PlayerAttEffectCollision = CreateDefaultSubObject<UCollision>("AttackEffectCollision");
	PlayerAttEffectCollision->SetupAttachment(DefaultComponent);
	// Collision은 반드시 SetCollisionGroup을 해야 한다.
	PlayerAttEffectCollision->SetCollisionGroup(ECollisionOrder::Attack);
	PlayerAttEffectCollision->SetCollisionType(ECollisionType::Rect);
}

APlayerAttEffect::~APlayerAttEffect()
{
}

void APlayerAttEffect::BeginPlay()
{
	Super::BeginPlay();

	PlayerAttCollisionVector = { 150, 150, 100 };

	PlayerAttEffectRenderer->CreateAnimation("PlayerAttackEffect", "PlayerAttackEffect", 0.1f);
	PlayerAttEffectRenderer->SetAutoSize(UDungreedConstValue::AutoSize, true);
	PlayerAttEffectRenderer->SetOrder(ERenderOrder::Player);
	PlayerAttEffectRenderer->ChangeAnimation("PlayerAttackEffect");

	PlayerAttEffectCollision->SetScale(PlayerAttCollisionVector);

}

void APlayerAttEffect::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (PlayerAttEffectRenderer->IsCurAnimationEnd())
	{
		Destroy();
	}
}

