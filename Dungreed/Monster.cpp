#include "PreCompile.h"
#include "Monster.h"

AMonster::AMonster()
{
	DefaultComponent = CreateDefaultSubObject<UDefaultSceneComponent>("DefaultComponent");
	SetRoot(DefaultComponent);

	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(DefaultComponent);

	Collision = CreateDefaultSubObject<UCollision>("Collision");
	Collision->SetupAttachment(DefaultComponent);
	// Collision�� �ݵ�� SetCollisionGroup�� �ؾ� �Ѵ�.
	Collision->SetCollisionGroup(ECollisionOrder::Monster);
	Collision->SetCollisionType(ECollisionType::Rect);
}

AMonster::~AMonster()
{
}

void AMonster::GetHit(int _Damage)
{
	MonsterHp -= _Damage;
	if (MonsterHp <= 0)
	{
		return;
	}

	Renderer->SetPlusColor({ 10.0f,10.0f,10.0f,0.0f });

	DelayCallBack(0.1f, [=]() {
		Renderer->SetPlusColor(FVector::Zero);
		});
}

void AMonster::BeginPlay()
{
	Super::BeginPlay();
}

void AMonster::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
