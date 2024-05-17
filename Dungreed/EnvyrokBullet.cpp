#include "PreCompile.h"
#include "EnvyrokBullet.h"
#include "Player.h"

AEnvyrokBullet::AEnvyrokBullet() 
{
	DefaultComponent = CreateDefaultSubObject<UDefaultSceneComponent>("DefaultComponent");
	SetRoot(DefaultComponent);

	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(DefaultComponent);

	Collision = CreateDefaultSubObject<UCollision>("Collision");
	Collision->SetupAttachment(DefaultComponent);
	Collision->SetCollisionGroup(ECollisionOrder::MonsterAttack);
	Collision->SetCollisionType(ECollisionType::Rect);
}

AEnvyrokBullet::~AEnvyrokBullet() 
{
}

void AEnvyrokBullet::BeginPlay()
{
	Super::BeginPlay();
	
	Renderer->CreateAnimation("EnvyrokBullet", "EnvyrokBullet", 0.1f);
	Renderer->SetAutoSize(UDungreedConstValue::AutoSize, true);
	Renderer->SetOrder(ERenderOrder::Monster);
	Renderer->ChangeAnimation("EnvyrokBullet");

	Collision->SetScale(ColScale);

	DelayCallBack(3.0f, [=]() {
		Destroy();
		});
}

void AEnvyrokBullet::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	
	AddActorLocation(GetActorTransform().GetUp() * 500.0f * _DeltaTime);

	// Ãæµ¹
	Collision->CollisionStay(ECollisionOrder::Player, [=](std::shared_ptr<UCollision> _Collision)
		{
			int a = 0;
		}
	);


	Collision->CollisionEnter(ECollisionOrder::Player, [=](std::shared_ptr<UCollision> _Collision)
		{
			int a = 0;
			
			Destroy();
			APlayer* Player = dynamic_cast<APlayer*>(_Collision->GetActor());
			Player->GetHit(5);
		}
	);

	Collision->CollisionExit(ECollisionOrder::Player, [=](std::shared_ptr<UCollision> _Collision)
		{
			int a = 0;
		}
	);
}

