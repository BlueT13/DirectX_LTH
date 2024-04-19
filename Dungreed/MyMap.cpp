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

	//Renderer->SetSprite("Town",0);
	Renderer->SetSprite("1.png");
	Renderer->SetAutoSize(UDungreedConstValue::AutoSize, true);
}

void AMyMap::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
