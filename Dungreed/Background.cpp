#include "PreCompile.h"
#include "Background.h"

ABackground::ABackground()
{
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
}

ABackground::~ABackground()
{
}

void ABackground::BeginPlay()
{
	Super::BeginPlay();

	SetActorScale3D(FVector(1920.0f, 1080.0f, 0.0f));

	Renderer->SetSprite("Background");
}

void ABackground::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

