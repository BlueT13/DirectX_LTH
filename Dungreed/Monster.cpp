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
	// Collision은 반드시 SetCollisionGroup을 해야 한다.
	Collision->SetCollisionGroup(ECollisionOrder::Monster);
	Collision->SetCollisionType(ECollisionType::Rect);
}

AMonster::~AMonster()
{
}

void AMonster::GetHit(int _Damage)
{
	Renderer->SetPlusColor({ 10.0f,10.0f,10.0f,0.0f });

	DelayCallBack(0.1f, [=]() {
		Renderer->SetPlusColor(FVector::Zero);
		});
	MonsterHp -= _Damage;
}

void AMonster::BeginPlay()
{
	Super::BeginPlay();
}

void AMonster::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
