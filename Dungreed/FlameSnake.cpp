#include "PreCompile.h"
#include "FlameSnake.h"

AFlameSnake::AFlameSnake() 
{
	DefaultComponent = CreateDefaultSubObject<UDefaultSceneComponent>("DefaultComponent");
	SetRoot(DefaultComponent);

	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(DefaultComponent);

	Collision = CreateDefaultSubObject<UCollision>("Collision");
	Collision->SetupAttachment(DefaultComponent);
	// Collision�� �ݵ�� SetCollisionGroup�� �ؾ� �Ѵ�.
	Collision->SetCollisionGroup(ECollisionOrder::Monster);
	Collision->SetCollisionType(ECollisionType::Rect);
}

AFlameSnake::~AFlameSnake() 
{
}

void AFlameSnake::BeginPlay()
{
	Super::BeginPlay();

	Renderer->CreateAnimation("FlameSnakeGeneration", "FlameSnakeGeneration", 0.1f);
	Renderer->CreateAnimation("FlameSnakeIdle", "FlameSnakeIdle", 0.1f);
	Renderer->CreateAnimation("FlameSnakeAttack", "FlameSnakeAttack", 0.1f, false);

	Renderer->SetAutoSize(UDungreedConstValue::AutoSize, true);
	Renderer->SetOrder(ERenderOrder::Monster);
	Renderer->SetPivot(EPivot::BOT);

	Collision->SetScale(FlameSnakeColScale);
	Collision->SetPosition({ 0,0,0 });

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

	State.Update(_DeltaTime);
}

void AFlameSnake::StateInit()
{
	// ������Ʈ ����
	State.CreateState("FlameSnakeGeneration");
	State.CreateState("FlameSnakeIdle");
	State.CreateState("FlameSnakeAttack");
	State.CreateState("FlameSnakeDie");

	// �Լ��� ����
	State.SetUpdateFunction("FlameSnakeGeneration", std::bind(&AFlameSnake::Generation, this, std::placeholders::_1));
	State.SetStartFunction("FlameSnakeGeneration", [this]()
		{
			this->Renderer->ChangeAnimation("FlameSnakeGeneration");
		});

	State.SetUpdateFunction("FlameSnakeIdle", std::bind(&AFlameSnake::Idle, this, std::placeholders::_1));
	State.SetStartFunction("FlameSnakeIdle", [this]()
		{
			this->Renderer->ChangeAnimation("FlameSnakeIdle");
		});

	State.SetUpdateFunction("FlameSnakeAttack", std::bind(&AFlameSnake::Attack, this, std::placeholders::_1));
	State.SetStartFunction("FlameSnakeAttack", [this]()
		{
			this->Renderer->ChangeAnimation("FlameSnakeAttack");
		});

	State.SetStartFunction("FlameSnakeDie", [this]()
		{
			Destroy();
		});

	State.ChangeState("FlameSnakeGeneration");
}

void AFlameSnake::Generation(float _DeltaTime)
{
}

void AFlameSnake::Idle(float _DeltaTime)
{
}

void AFlameSnake::Attack(float _DeltaTime)
{
}
