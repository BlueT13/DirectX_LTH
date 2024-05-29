#include "PreCompile.h"
#include "FlameSnake.h"
#include "EnvyrokBullet.h"
#include "Player.h"

AFlameSnake::AFlameSnake()
{
}

AFlameSnake::~AFlameSnake()
{
}

void AFlameSnake::ChangeDir()
{
	DefaultComponent->SetScale({ -1.0f, 1.0f, 1.0f });
	Renderer->SetPivot(EPivot::RIGHTBOTTOM);
}

void AFlameSnake::BeginPlay()
{
	Super::BeginPlay();

	Renderer->CreateAnimation("FlameSnakeGeneration", "FlameSnakeGeneration", 0.1f);
	Renderer->CreateAnimation("FlameSnakeIdle", "FlameSnakeIdle", 0.1f);
	Renderer->CreateAnimation("FlameSnakeAttack", "FlameSnakeAttack", 0.1f, false);

	Renderer->SetAutoSize(UDungreedConstValue::AutoSize, true);
	Renderer->SetOrder(ERenderOrder::Monster);
	Renderer->SetPivot(EPivot::LEFTBOTTOM);

	Collision->SetScale(FlameSnakeColScale);
	Collision->SetPosition({ 122,144,0 });

	MonsterHp = 6;

	ColMapTex = UDungreedConstValue::ColMap;
	ColMapX = ColMapTex->GetScale().X * UDungreedConstValue::AutoSize;
	ColMapY = ColMapTex->GetScale().Y * UDungreedConstValue::AutoSize;
	ColMapHalfX = ColMapTex->GetScale().hX() * UDungreedConstValue::AutoSize;
	ColMapHalfY = ColMapTex->GetScale().hY() * UDungreedConstValue::AutoSize;

	StateInit();
}

void AFlameSnake::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (MonsterHp <= 0)
	{
		State.ChangeState("FlameSnakeDie");
		return;
	}

	State.Update(_DeltaTime);
}

void AFlameSnake::StateInit()
{
	// 스테이트 생성
	State.CreateState("FlameSnakeGeneration");
	State.CreateState("FlameSnakeIdle");
	State.CreateState("FlameSnakeAttack");
	State.CreateState("FlameSnakeDie");

	// 함수들 세팅
	State.SetUpdateFunction("FlameSnakeGeneration", std::bind(&AFlameSnake::Generation, this, std::placeholders::_1));
	State.SetStartFunction("FlameSnakeGeneration", [this]()
		{
			this->Renderer->ChangeAnimation("FlameSnakeGeneration");
		});

	State.SetUpdateFunction("FlameSnakeIdle", std::bind(&AFlameSnake::Idle, this, std::placeholders::_1));
	State.SetStartFunction("FlameSnakeIdle", [this]()
		{
			CurFireTime = FireRate;
			this->Renderer->ChangeAnimation("FlameSnakeIdle");
		});

	State.SetUpdateFunction("FlameSnakeAttack", std::bind(&AFlameSnake::Attack, this, std::placeholders::_1));
	State.SetStartFunction("FlameSnakeAttack", [this]()
		{
			this->Renderer->ChangeAnimation("FlameSnakeAttack");
			
			DelayCallBack(1.0f, [=]() {
				std::shared_ptr<AEnvyrokBullet> EnvyrokBullet0 = GetWorld()->SpawnActor<AEnvyrokBullet>("EnvyrokBullet");
				std::shared_ptr<AEnvyrokBullet> EnvyrokBullet1 = GetWorld()->SpawnActor<AEnvyrokBullet>("EnvyrokBullet");
				std::shared_ptr<AEnvyrokBullet> EnvyrokBullet2 = GetWorld()->SpawnActor<AEnvyrokBullet>("EnvyrokBullet");

				if (GetActorLocation().X < ColMapHalfX)
				{
					FVector Diff = { 180, 224, 0 };
					FVector CreateBulletPos = GetActorLocation() + Diff;
					EnvyrokBullet0->SetActorLocation(CreateBulletPos);
					EnvyrokBullet1->SetActorLocation(CreateBulletPos);
					EnvyrokBullet2->SetActorLocation(CreateBulletPos);

					FVector PlayerPos = APlayer::MainPlayer->GetActorLocation();
					FVector AttackDir = PlayerPos - CreateBulletPos;
					float Rot = AttackDir.RightVectorToAngle2DDeg();
					Rot -= 90.0f;

					EnvyrokBullet0->SetActorRotation({ 0.0f, 0.0f, Rot });
					EnvyrokBullet1->SetActorRotation({ 0.0f, 0.0f, Rot + 30.0f });
					EnvyrokBullet2->SetActorRotation({ 0.0f, 0.0f, Rot - 30.0f });
				}
				else
				{
					FVector Diff = { -180, 224, 0 };
					FVector CreateBulletPos = GetActorLocation() + Diff;
					EnvyrokBullet0->SetActorLocation(CreateBulletPos);
					EnvyrokBullet1->SetActorLocation(CreateBulletPos);
					EnvyrokBullet2->SetActorLocation(CreateBulletPos);

					FVector PlayerPos = APlayer::MainPlayer->GetActorLocation();
					FVector AttackDir = PlayerPos - CreateBulletPos;
					float Rot = AttackDir.RightVectorToAngle2DDeg();
					Rot -= 90.0f;

					EnvyrokBullet0->SetActorRotation({ 0.0f, 0.0f, Rot });
					EnvyrokBullet1->SetActorRotation({ 0.0f, 0.0f, Rot + 30.0f });
					EnvyrokBullet2->SetActorRotation({ 0.0f, 0.0f, Rot - 30.0f });
				}
				});
		});

	State.SetStartFunction("FlameSnakeDie", [this]()
		{
			Destroy();
		});

	State.ChangeState("FlameSnakeGeneration");
}

void AFlameSnake::Generation(float _DeltaTime)
{
	if (Renderer->IsCurAnimationEnd())
	{
		State.ChangeState("FlameSnakeIdle");
		return;
	}
}

void AFlameSnake::Idle(float _DeltaTime)
{
	CurFireTime -= _DeltaTime;
	if (CurFireTime < 0)
	{
		State.ChangeState("FlameSnakeAttack");
		return;
	}
}

void AFlameSnake::Attack(float _DeltaTime)
{
	if (Renderer->IsCurAnimationEnd())
	{
		State.ChangeState("FlameSnakeIdle");
		return;
	}
}
