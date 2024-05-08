#include "PreCompile.h"
#include "EnvyrokTrap.h"
#include "Player.h"

AEnvyrokTrap::AEnvyrokTrap()
{
	DefaultComponent = CreateDefaultSubObject<UDefaultSceneComponent>("DefaultComponent");
	SetRoot(DefaultComponent);

	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(DefaultComponent);

	Collision = CreateDefaultSubObject<UCollision>("Collision");
	Collision->SetupAttachment(DefaultComponent);
	Collision->SetCollisionGroup(ECollisionOrder::EnvyrokTrap);
	Collision->SetCollisionType(ECollisionType::Rect);
}

AEnvyrokTrap::~AEnvyrokTrap()
{
}

void AEnvyrokTrap::BeginPlay()
{
	Super::BeginPlay();

	Renderer->SetSprite("EnvyrokTrap.png");
	Renderer->SetAutoSize(UDungreedConstValue::AutoSize, true);
	Renderer->SetOrder(ERenderOrder::EnvyrokTrap);

	Collision->SetScale(ColScale);
}

void AEnvyrokTrap::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	// Ãæµ¹
	Collision->CollisionStay(ECollisionOrder::Player, [=](std::shared_ptr<UCollision> _Collision)
		{
			FVector PlayerPos = APlayer::MainPlayer->GetActorLocation();
			FVector ThisPos = GetActorLocation();
			FVector TrapToPlayerDir = FVector::Zero;
			if (PlayerPos.Y > ThisPos.Y)
			{
				TrapToPlayerDir = FVector::Up;
			}
			else
			{
				TrapToPlayerDir = PlayerPos - ThisPos;
			}
			FVector TrapToPlayerDirNormal = TrapToPlayerDir.Normalize2DReturn();


			APlayer::MainPlayer->AddActorLocation(TrapToPlayerDirNormal * _DeltaTime * 100.0f);
		}
	);


	Collision->CollisionEnter(ECollisionOrder::Player, [=](std::shared_ptr<UCollision> _Collision)
		{
			int a = 0;
		}
	);

	Collision->CollisionExit(ECollisionOrder::Player, [=](std::shared_ptr<UCollision> _Collision)
		{
			int a = 0;
		}
	);
}

