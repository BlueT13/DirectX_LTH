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

	Renderer->SetAutoSize(UDungreedConstValue::AutoSize, true);
	Renderer->SetOrder(ERenderOrder::Monster);

	Collision->SetScale(EnvyrokColScale);

	ColMapTex = UDungreedConstValue::ColMap;

	StateInit();
}

void AEnvyrok::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
}

void AEnvyrok::StateInit()
{
	// 스테이트 생성
	State.CreateState("EnvyrokIdle");
	State.CreateState("EnvyrokDie");

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
}

void AEnvyrok::Die(float _DeltaTime)
{
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

