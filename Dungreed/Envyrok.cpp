#include "PreCompile.h"
#include "Envyrok.h"

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

void AEnvyrok::BeginPlay()
{
	Super::BeginPlay();

	Renderer->CreateAnimation("EnvyrokIdle", "EnvyrokIdle", 0.1f);
	Renderer->CreateAnimation("EnvyrokDie", "EnvyrokDie", 0.1f);
	Renderer->CreateAnimation("EnvyrokAirSpike_Start", "EnvyrokAirSpike_Start", 0.1f, false);
	Renderer->CreateAnimation("EnvyrokAirSpike", "EnvyrokAirSpike", 0.1f, true);
	Renderer->CreateAnimation("EnvyrokAirSpike_End", "EnvyrokAirSpike_End", 0.1f, false);

	Renderer->SetAutoSize(UDungreedConstValue::AutoSize, true);
	Renderer->SetOrder(ERenderOrder::Monster);
	Renderer->SetPivot(EPivot::BOT);

	Collision->SetScale(EnvyrokColScale);
	Collision->SetPosition({ 0,48,0 });

	ColMapTex = UDungreedConstValue::ColMap;
	ColMapY = ColMapTex->GetScale().Y * UDungreedConstValue::AutoSize;

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

	// 함수들 세팅
	State.SetUpdateFunction("EnvyrokIdle", std::bind(&AEnvyrok::Idle, this, std::placeholders::_1));
	State.SetStartFunction("EnvyrokIdle", [this]()
		{
			this->Renderer->ChangeAnimation("EnvyrokIdle");
		});

	State.SetUpdateFunction("EnvyrokDie", std::bind(&AEnvyrok::Die, this, std::placeholders::_1));
	State.SetStartFunction("EnvyrokDie", [this]()
		{
			this->Renderer->ChangeAnimation("EnvyrokDie");
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
			this->Renderer->ChangeAnimation("EnvyrokAirSpike");
		});
	State.SetUpdateFunction("EnvyrokAirSpike_End", std::bind(&AEnvyrok::AirSpike_End, this, std::placeholders::_1));
	State.SetStartFunction("EnvyrokAirSpike_End", [this]()
		{
			this->Renderer->ChangeAnimation("EnvyrokAirSpike_End");
		});

	State.ChangeState("EnvyrokIdle");
}

void AEnvyrok::Idle(float _DeltaTime)
{
	EnvyrokDirCheck();

	if (true == IsPress('J'))
	{
		AddActorLocation(FVector::Left * _DeltaTime * 500.0f);
	}
	if (true == IsPress('L'))
	{
		AddActorLocation(FVector::Right * _DeltaTime * 500.0f);
	}
	if (true == IsPress('1'))
	{
		State.ChangeState("EnvyrokAirSpike_Start");
	}
}

void AEnvyrok::Die(float _DeltaTime)
{
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
	AddActorLocation(FVector::Left * _DeltaTime * Speed);
}

void AEnvyrok::AirSpike_End(float _DeltaTime)
{
	EnvyrokDirCheck();

	if (Renderer->IsCurAnimationEnd())
	{
		Renderer->SetPosition(FVector::Zero);
		State.ChangeState("EnvyrokIdle");
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

