#include "PreCompile.h"
#include "PlayerAttEffect.h"
#include "Envyrok.h"

APlayerAttEffect::APlayerAttEffect()
{
	DefaultComponent = CreateDefaultSubObject<UDefaultSceneComponent>("DefaultComponent");
	SetRoot(DefaultComponent);

	PlayerAttEffectRenderer = CreateDefaultSubObject<USpriteRenderer>("AttackEffectRenderer");
	PlayerAttEffectRenderer->SetupAttachment(DefaultComponent);

	PlayerAttEffectCollision = CreateDefaultSubObject<UCollision>("AttackEffectCollision");
	PlayerAttEffectCollision->SetupAttachment(DefaultComponent);
	// Collision은 반드시 SetCollisionGroup을 해야 한다.
	PlayerAttEffectCollision->SetCollisionGroup(ECollisionOrder::PlayerAttack);
	PlayerAttEffectCollision->SetCollisionType(ECollisionType::Rect);
}

APlayerAttEffect::~APlayerAttEffect()
{
}

void APlayerAttEffect::BeginPlay()
{
	Super::BeginPlay();

	PlayerAttEffectRenderer->CreateAnimation("PlayerAttackEffect", "PlayerAttackEffect", 0.1f);
	PlayerAttEffectRenderer->SetAutoSize(UDungreedConstValue::AutoSize, true);
	PlayerAttEffectRenderer->SetOrder(ERenderOrder::Player);
	PlayerAttEffectRenderer->ChangeAnimation("PlayerAttackEffect");

	PlayerAttEffectCollision->SetScale(PlayerAttColScale);

}

void APlayerAttEffect::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	// 충돌
	PlayerAttEffectCollision->CollisionStay(ECollisionOrder::Monster, [=](std::shared_ptr<UCollision> _Collision)
		{
			int a = 0;

			// _Collison[0]->GetActor()->Destroy();
		}
	);


	PlayerAttEffectCollision->CollisionEnter(ECollisionOrder::Monster, [=](std::shared_ptr<UCollision> _Collision)
		{
			int a = 0;

			AEnvyrok* Envyrok = dynamic_cast<AEnvyrok*>(_Collision->GetActor());

			Envyrok->GetHit(2);
		}
	);

	PlayerAttEffectCollision->CollisionExit(ECollisionOrder::Monster, [=](std::shared_ptr<UCollision> _Collision)
		{
			int a = 0;

			// _Collison[0]->GetActor()->Destroy();
		}
	);


	// 애니메이션 끝나면 삭제
	if (PlayerAttEffectRenderer->IsCurAnimationEnd())
	{
		Destroy();
	}
}

