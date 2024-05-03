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
	// Collision�� �ݵ�� SetCollisionGroup�� �ؾ� �Ѵ�.
	PlayerAttEffectCollision->SetCollisionGroup(ECollisionOrder::Attack);
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

	// �浹
	PlayerAttEffectCollision->CollisionStay(ECollisionOrder::Monster, [=](std::shared_ptr<UCollision> _Collison)
		{
			int a = 0;

			// _Collison[0]->GetActor()->Destroy();
		}
	);


	PlayerAttEffectCollision->CollisionEnter(ECollisionOrder::Monster, [=](std::shared_ptr<UCollision> _Collison)
		{
			int a = 0;

			 _Collison->GetActor()->Destroy();
		}
	);

	PlayerAttEffectCollision->CollisionExit(ECollisionOrder::Monster, [=](std::shared_ptr<UCollision> _Collison)
		{
			int a = 0;

			// _Collison[0]->GetActor()->Destroy();
		}
	);


	// �ִϸ��̼� ������ ����
	if (PlayerAttEffectRenderer->IsCurAnimationEnd())
	{
		Destroy();
	}
}

