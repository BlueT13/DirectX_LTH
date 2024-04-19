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

	Renderer->SetSprite("Tow_Col.png");
	Renderer->SetAutoSize(4.0f, true);
}

void ABackground::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

