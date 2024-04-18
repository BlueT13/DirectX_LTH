#include "PreCompile.h"
#include "MyMap.h"

AMyMap::AMyMap()
{
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	SetRoot(Renderer);
}

AMyMap::~AMyMap()
{
}

void AMyMap::BeginPlay()
{
	Super::BeginPlay();

	Renderer->SetSprite("Town",0);
	Renderer->SetAutoSize(4.0f, true);
}

void AMyMap::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
