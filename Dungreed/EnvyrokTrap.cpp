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

			float CurInterY = abs(PlayerPos.Y - ThisPos.Y);
			float InterY = abs(PlayerScale.Y * 0.5f) + abs(ThisScale.Y * 0.5f);
			float4 UpVector = float4(0.0f, InterY - CurInterY, 0.0f);

			float CurInterX = abs(PlayerPos.X - ThisPos.X);
			float InterX = abs(PlayerScale.X * 0.5f) + abs(ThisScale.X * 0.5f);
			float4 RightVector = float4(InterX - CurInterX, 0.0f, 0.0f);


			if (CurInterY < InterY - 16.0f && ThisPos.X < PlayerPos.X)
			{
				_Collision->GetActor()->AddActorLocation(RightVector);
			}
			else if (CurInterY < InterY - 16.0f && ThisPos.X > PlayerPos.X)
			{
				_Collision->GetActor()->AddActorLocation(-RightVector);
			}
			else if (0 < PlayerPos.Y - ThisPos.Y)
			{
				_Collision->GetActor()->AddActorLocation(UpVector);

			}
			else if (0 > PlayerPos.Y - ThisPos.Y)
			{
				APlayer::MainPlayer->JumpVector = FVector::Zero;
				_Collision->GetActor()->AddActorLocation(-UpVector);
			}


		}
	);
}

