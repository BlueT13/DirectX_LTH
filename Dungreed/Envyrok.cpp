#include "PreCompile.h"
#include "Envyrok.h"
#include <memory>

AEnvyrok::AEnvyrok()
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

	InputOn();
}

AEnvyrok::~AEnvyrok()
{
}

void AEnvyrok::GetHit(int _Damage)
{
	Renderer->SetPlusColor({ 10.0f,10.0f,10.0f,0.0f });

	DelayCallBack(0.1f, [=]() {
		Renderer->SetPlusColor(FVector::Zero);
		});
	Hp -= _Damage;
}

void AEnvyrok::BeginPlay()
{
	Super::BeginPlay();

	Renderer->CreateAnimation("EnvyrokIdle", "EnvyrokIdle", 0.1f);
	Renderer->CreateAnimation("EnvyrokDieStart", "EnvyrokDie", 3.0f, false, 0, 0);
	Renderer->CreateAnimation("EnvyrokDie", "EnvyrokDie", 0.2f, false);
	Renderer->CreateAnimation("EnvyrokAirSpike_Start", "EnvyrokAirSpike_Start", 0.1f, false);
	Renderer->CreateAnimation("EnvyrokAirSpike", "EnvyrokAirSpike", 0.1f, true);
	Renderer->CreateAnimation("EnvyrokAirSpike_End", "EnvyrokAirSpike_End", 0.1f, false);

	Renderer->SetAutoSize(UDungreedConstValue::AutoSize, true);
	Renderer->SetOrder(ERenderOrder::Monster);
	Renderer->SetPivot(EPivot::BOT);

	Collision->SetScale(EnvyrokColScale);
	Collision->SetPosition({ 0,48,0 });

	ColMapTex = UDungreedConstValue::ColMap;
	ColMapX = ColMapTex->GetScale().X * UDungreedConstValue::AutoSize;
	ColMapY = ColMapTex->GetScale().Y * UDungreedConstValue::AutoSize;
	ColMapHalfX = ColMapTex->GetScale().hX() * UDungreedConstValue::AutoSize;
	ColMapHalfY = ColMapTex->GetScale().hY() * UDungreedConstValue::AutoSize;

	StateInit();

}

void AEnvyrok::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
}

void AEnvyrok::ColorColCheck()
{
	EnvyrokPos = GetActorLocation();
	EnvyrokPos.Y = ColMapY - EnvyrokPos.Y;
	EnvyrokPos /= UDungreedConstValue::AutoSize;

	BottomColor = ColMapTex->GetColor({ EnvyrokPos.X, EnvyrokPos.Y, EnvyrokPos.Z }, Color8Bit::Black);
}

void AEnvyrok::StateInit()
{
	// 스테이트 생성
	State.CreateState("EnvyrokIdle");
	State.CreateState("EnvyrokDie");
	State.CreateState("EnvyrokAirSpike_Start");
	State.CreateState("EnvyrokAirSpike");
	State.CreateState("EnvyrokAirSpike_End");
	State.CreateState("EnvyrokSpawnTrap");

	// 함수들 세팅
	State.SetUpdateFunction("EnvyrokIdle", std::bind(&AEnvyrok::Idle, this, std::placeholders::_1));
	State.SetStartFunction("EnvyrokIdle", [this]()
		{
			CurAttackTime = AttackTime;
			this->Renderer->ChangeAnimation("EnvyrokIdle");
		});

	State.SetUpdateFunction("EnvyrokDie", std::bind(&AEnvyrok::Die, this, std::placeholders::_1));
	State.SetStartFunction("EnvyrokDie", [this]()
		{
			Collision->SetActive(false);
			Renderer->SetPosition({ 0,-192,0 });
			this->Renderer->ChangeAnimation("EnvyrokDieStart");
		});

	State.SetUpdateFunction("EnvyrokAirSpike_Start", std::bind(&AEnvyrok::AirSpike_Start, this, std::placeholders::_1));
	State.SetStartFunction("EnvyrokAirSpike_Start", [this]()
		{
			Renderer->SetPosition({ 0,-32,0 });
			this->Renderer->ChangeAnimation("EnvyrokAirSpike_Start");
		});

	State.SetUpdateFunction("EnvyrokAirSpike", std::bind(&AEnvyrok::AirSpike, this, std::placeholders::_1));
	State.SetStartFunction("EnvyrokAirSpike", [this]()
		{
			JumpVector = FVector::Up * 1200.0f;
			CurFireTime = FireRate;

			if (GetActorLocation().X < ColMapHalfX)
			{
				AirSpikeDir = FVector::Right;
			}
			else
			{
				AirSpikeDir = FVector::Left;
			}

			this->Renderer->ChangeAnimation("EnvyrokAirSpike");
		});

	State.SetUpdateFunction("EnvyrokAirSpike_End", std::bind(&AEnvyrok::AirSpike_End, this, std::placeholders::_1));
	State.SetStartFunction("EnvyrokAirSpike_End", [this]()
		{
			this->Renderer->ChangeAnimation("EnvyrokAirSpike_End");
		});

	State.SetUpdateFunction("EnvyrokSpawnTrap", std::bind(&AEnvyrok::SpawnTrap, this, std::placeholders::_1));
	State.SetStartFunction("EnvyrokSpawnTrap", [this]()
		{
			Renderer->SetPosition({ 0,-32,0 });
			CurBlockTime = BlockTime;
			CurAwayTime = AwayTime;

			// 블록 생성
			LeftBlocks.push_back(GetWorld()->SpawnActor<AEnvyrokTrap>("EnvyrokTrap0"));
			LeftBlocks.push_back(GetWorld()->SpawnActor<AEnvyrokTrap>("EnvyrokTrap1"));
			LeftBlocks.push_back(GetWorld()->SpawnActor<AEnvyrokTrap>("EnvyrokTrap2"));
			LeftBlocks.push_back(GetWorld()->SpawnActor<AEnvyrokTrap>("EnvyrokTrap3"));
			RightBlocks.push_back(GetWorld()->SpawnActor<AEnvyrokTrap>("EnvyrokTrap4"));
			RightBlocks.push_back(GetWorld()->SpawnActor<AEnvyrokTrap>("EnvyrokTrap5"));
			RightBlocks.push_back(GetWorld()->SpawnActor<AEnvyrokTrap>("EnvyrokTrap6"));
			RightBlocks.push_back(GetWorld()->SpawnActor<AEnvyrokTrap>("EnvyrokTrap7"));

			// 블록 생성 위치 설정
			LeftBlocks[0]->SetActorLocation({ ColMapHalfX - 640 , ColMapHalfY - 32, 0.0f });
			LeftBlocks[1]->SetActorLocation({ ColMapHalfX - 640 , ColMapHalfY + 100, 0.0f });
			LeftBlocks[2]->SetActorLocation({ ColMapHalfX - 640 , ColMapHalfY + 232, 0.0f });
			LeftBlocks[3]->SetActorLocation({ ColMapHalfX - 640 , ColMapHalfY + 364, 0.0f });
			RightBlocks[0]->SetActorLocation({ ColMapHalfX + 640 , ColMapHalfY - 32, 0.0f });
			RightBlocks[1]->SetActorLocation({ ColMapHalfX + 640 , ColMapHalfY + 100, 0.0f });
			RightBlocks[2]->SetActorLocation({ ColMapHalfX + 640 , ColMapHalfY + 232, 0.0f });
			RightBlocks[3]->SetActorLocation({ ColMapHalfX + 640 , ColMapHalfY + 364, 0.0f });

			// 안전 블록 선택
			for (size_t i = 0; i < LeftBlocks.size(); i++)
			{
				LeftBlocks[i]->SetIsSafe(false);
				RightBlocks[i]->SetIsSafe(false);
			}

			if (SafeBlockInt < 4)
			{
				LeftBlocks[SafeBlockInt]->SetIsSafe(true);
				RightBlocks[SafeBlockInt]->SetIsSafe(true);
				SafeBlockInt++;
			}
			else
			{
				SafeBlockInt = 0;
				LeftBlocks[SafeBlockInt]->SetIsSafe(true);
				RightBlocks[SafeBlockInt]->SetIsSafe(true);
			}

			for (size_t i = 0; i < LeftBlocks.size(); i++)
			{
				if (LeftBlocks[i]->GetIsSafe())
				{
					LeftBlocks[i]->AddActorLocation({ -130.0f, 0.0f, 0.0f });
				}
			}
			for (size_t i = 0; i < RightBlocks.size(); i++)
			{
				if (RightBlocks[i]->GetIsSafe())
				{
					RightBlocks[i]->AddActorLocation({ 130.0f, 0.0f, 0.0f });
				}
			}
		});

	State.ChangeState("EnvyrokIdle");
}

void AEnvyrok::Idle(float _DeltaTime)
{
	EnvyrokDirCheck();

	if (Hp <= 0)
	{
		State.ChangeState("EnvyrokDie");
		return;
	}

	CurAttackTime -= _DeltaTime;
	if (CurAttackTime < 0)
	{
		State.ChangeState("EnvyrokAirSpike_Start");
		return;
	}

}

void AEnvyrok::Die(float _DeltaTime)
{
	if (Renderer->IsCurAnimationEnd())
	{
		Renderer->ChangeAnimation("EnvyrokDie");
	}
}

void AEnvyrok::AirSpike_Start(float _DeltaTime)
{
	EnvyrokDirCheck();

	if (Renderer->IsCurAnimationEnd())
	{
		State.ChangeState("EnvyrokAirSpike");
	}
}

void AEnvyrok::AirSpike(float _DeltaTime)
{
	Gravity(_DeltaTime);
	JumpPower = JumpVector + GravityVector;
	ColorColCheck();

	// Bullet 생성
	CurFireTime -= _DeltaTime;
	if (CurFireTime < 0)
	{
		CurFireTime = FireRate;

		std::shared_ptr<AEnvyrokBullet> EnvyrokBullet0 = GetWorld()->SpawnActor<AEnvyrokBullet>("EnvyrokBullet");
		std::shared_ptr<AEnvyrokBullet> EnvyrokBullet1 = GetWorld()->SpawnActor<AEnvyrokBullet>("EnvyrokBullet");
		std::shared_ptr<AEnvyrokBullet> EnvyrokBullet2 = GetWorld()->SpawnActor<AEnvyrokBullet>("EnvyrokBullet");
		std::shared_ptr<AEnvyrokBullet> EnvyrokBullet3 = GetWorld()->SpawnActor<AEnvyrokBullet>("EnvyrokBullet");

		EnvyrokBullet0->SetActorLocation(GetActorLocation());
		EnvyrokBullet1->SetActorLocation(GetActorLocation());
		EnvyrokBullet2->SetActorLocation(GetActorLocation());
		EnvyrokBullet3->SetActorLocation(GetActorLocation());

		if (GetActorLocation().X < ColMapHalfX)
		{
			EnvyrokBullet0->SetActorRotation({ 0.0f, 0.0f, 30.0f });
			EnvyrokBullet1->SetActorRotation({ 0.0f, 0.0f, 120.0f });
			EnvyrokBullet2->SetActorRotation({ 0.0f, 0.0f, 210.0f });
			EnvyrokBullet3->SetActorRotation({ 0.0f, 0.0f, 300.0f });
		}
		else
		{
			EnvyrokBullet0->SetActorRotation({ 0.0f, 0.0f, -30.0f });
			EnvyrokBullet1->SetActorRotation({ 0.0f, 0.0f, 60.0f });
			EnvyrokBullet2->SetActorRotation({ 0.0f, 0.0f, 150.0f });
			EnvyrokBullet3->SetActorRotation({ 0.0f, 0.0f, 240.0f });
		}
	}

	// 착지
	if (0 >= JumpPower.Y)
	{
		if (BottomColor == Color8Bit::Black)
		{
			GravityVector = FVector::Zero;
			State.ChangeState("EnvyrokAirSpike_End");
			return;
		}
	}

	AddActorLocation(JumpPower * _DeltaTime);
	AddActorLocation(AirSpikeDir * _DeltaTime * Speed);

}

void AEnvyrok::AirSpike_End(float _DeltaTime)
{
	EnvyrokDirCheck();

	if (Renderer->IsCurAnimationEnd())
	{
		Renderer->SetPosition(FVector::Zero);
		State.ChangeState("EnvyrokSpawnTrap");
		return;
	}
}

void AEnvyrok::SpawnTrap(float _DeltaTime)
{
	CurBlockTime -= _DeltaTime;
	CurAwayTime -= _DeltaTime;

	if (0.0f < CurBlockTime)
	{
		return;
	}

	// Trap 이동
	for (size_t i = 0; i < LeftBlocks.size(); i++)
	{
		if (LeftBlocks[i]->GetActorLocation().X < ColMapHalfX - 130 && !LeftBlocks[i]->GetIsSafe())
		{
			LeftBlocks[i]->AddActorLocation(FVector::Right * 2000.0f * _DeltaTime);
		}
		if (LeftBlocks[i]->GetActorLocation().X < ColMapHalfX - 260 && LeftBlocks[i]->GetIsSafe())
		{
			LeftBlocks[i]->AddActorLocation(FVector::Right * 2000.0f * _DeltaTime);
		}
	}
	for (size_t i = 0; i < RightBlocks.size(); i++)
	{
		if (RightBlocks[i]->GetActorLocation().X > ColMapHalfX + 130 && !RightBlocks[i]->GetIsSafe())
		{
			RightBlocks[i]->AddActorLocation(FVector::Left * 2000.0f * _DeltaTime);
		}
		if (RightBlocks[i]->GetActorLocation().X > ColMapHalfX + 260 && RightBlocks[i]->GetIsSafe())
		{
			RightBlocks[i]->AddActorLocation(FVector::Left * 2000.0f * _DeltaTime);
		}
	}

	// Trap 충돌 체크
	std::set<int> LeftCheck;
	for (size_t i = 0; i < LeftBlocks.size(); i++)
	{
		LeftBlocks[i]->Collision->CollisionStay(ECollisionOrder::Player, [&](std::shared_ptr<UCollision> _Collision)
			{
				LeftCheck.insert(i);
			});
	}

	std::set<int> RightCheck;
	for (size_t i = 0; i < RightBlocks.size(); i++)
	{
		RightBlocks[i]->Collision->CollisionStay(ECollisionOrder::Player, [&](std::shared_ptr<UCollision> _Collision)
			{
				RightCheck.insert(i);
			});
	}

	for (int Count : LeftCheck)
	{
		if (RightCheck.contains(Count))
		{
			APlayer::MainPlayer->GetHit(10);
			break;
		}
	}

	if (CurAwayTime < 0)
	{
		for (size_t i = 0; i < LeftBlocks.size(); i++)
		{
			LeftBlocks[i]->AddActorLocation(FVector::Left * 4000.0f * _DeltaTime);
		}
		for (size_t i = 0; i < RightBlocks.size(); i++)
		{
			RightBlocks[i]->AddActorLocation(FVector::Right * 4000.0f * _DeltaTime);
		}

		if (LeftBlocks[0]->GetActorLocation().X < 100)
		{
			for (size_t i = 0; i < LeftBlocks.size(); i++)
			{
				LeftBlocks[i]->Destroy();
			}
			for (size_t i = 0; i < RightBlocks.size(); i++)
			{
				RightBlocks[i]->Destroy();
			}
			LeftBlocks.clear();
			RightBlocks.clear();
			Renderer->SetPosition(FVector::Zero);
			State.ChangeState("EnvyrokIdle");
			return;
		}
	}
}

void AEnvyrok::EnvyrokDirCheck()
{
	EnvyrokPos = GetActorLocation();

	if (EnvyrokPos.X <= APlayer::MainPlayer->GetActorLocation().X)
	{
		DefaultComponent->SetScale({ 1.0f, 1.0f, 1.0f });
	}
	else
	{
		DefaultComponent->SetScale({ -1.0f, 1.0f, 1.0f });
	}
}

void AEnvyrok::Gravity(float _DeltaTime)
{
	GravityVector += FVector::Down * 2000.0f * _DeltaTime;
}

