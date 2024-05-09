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

	// 충돌
	Collision->CollisionStay(ECollisionOrder::Player, [=](std::shared_ptr<UCollision> _Collision)
		{
			FVector PlayerPos = APlayer::MainPlayer->GetActorLocation();
			FVector ThisPos = GetActorLocation();
			FVector TrapToPlayerDir = PlayerPos - ThisPos;
			//if (PlayerPos.Y >= ThisPos.Y)
			//{
			//	TrapToPlayerDir.X = 0.0f;
			//	APlayer::MainPlayer->State.ChangeState("PlayerIdle");
			//}

			// 아예 안겹칠 위치로 무조건 순간이동 시켜야 한다.
			while (true == IsCol)
			{
				APlayer::MainPlayer->AddActorLocation(TrapToPlayerDir.Normalize2DReturn());
			}
		}
	);


	Collision->CollisionEnter(ECollisionOrder::Player, [=](std::shared_ptr<UCollision> _Collision)
		{
			int a = 0;
			IsCol = true;
			//APlayer::MainPlayer->State.ChangeState("PlayerIdle");
		}
	);

	Collision->CollisionExit(ECollisionOrder::Player, [=](std::shared_ptr<UCollision> _Collision)
		{
			int a = 0;
			IsCol = false;
		}
	);
}

