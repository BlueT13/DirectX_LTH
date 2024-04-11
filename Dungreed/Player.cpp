#include "PreCompile.h"
#include "Player.h"

APlayer::APlayer()
{
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	InputOn();
}

APlayer::~APlayer()
{
}

void APlayer::BeginPlay()
{
	Super::BeginPlay();

	Renderer->CreateAnimation("Die", "Die");
	Renderer->CreateAnimation("Idle", "Idle");
	Renderer->CreateAnimation("Jump", "Jump");
	Renderer->CreateAnimation("Run", "Run", 0.1f);

	Renderer->SetAutoSize(10.0f, true);
	Renderer->SetOrder(ERenderOrder::Player);

	StateInit();
}

void APlayer::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
}