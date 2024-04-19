#include "PreCompile.h"
#include "Background.h"

ABackground::ABackground()
{
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	SetRoot(Renderer);
}

ABackground::~ABackground()
{
}

void ABackground::BeginPlay()
{
	Super::BeginPlay();

	Renderer->SetSprite("Town.png");
	Renderer->SetAutoSize(UDungreedConstValue::AutoSize, true);
}

void ABackground::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

