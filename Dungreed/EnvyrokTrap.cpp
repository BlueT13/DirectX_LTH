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
			FVector PlayerPos = _Collision->GetWorldPosition();
			FVector ThisPos = GetActorLocation();
			FVector PlayerScale = _Collision->GetWorldScale();
			FVector ThisScale = Collision->GetWorldScale();
			float CurInter = abs(PlayerPos.Y - ThisPos.Y);
			float Inter = abs(PlayerScale.Y * 0.5f) + abs(ThisScale.Y * 0.5f);
			float4 UpVector = float4(0.0f, Inter - CurInter, 0.0f);

			APlayer::MainPlayer->JumpVector = FVector::Zero;
			APlayer::MainPlayer->GravityVector = FVector::Zero;
			

			_Collision->GetActor()->AddActorLocation(UpVector);


		}
	);


	Collision->CollisionEnter(ECollisionOrder::Player, [=](std::shared_ptr<UCollision> _Collision)
		{
			int a = 0;
			APlayer::MainPlayer->State.ChangeState("PlayerIdle");
		}
	);

	Collision->CollisionExit(ECollisionOrder::Player, [=](std::shared_ptr<UCollision> _Collision)
		{
			int a = 0;
		}
	);
}

