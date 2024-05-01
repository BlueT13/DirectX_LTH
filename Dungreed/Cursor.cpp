#include "PreCompile.h"
#include "Cursor.h"

ACursor::ACursor()
{
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	SetRoot(Renderer);
}

ACursor::~ACursor()
{
}

void ACursor::BeginPlay()
{
	Super::BeginPlay();

	Renderer->SetSprite("Cursor.png");
	Renderer->SetAutoSize(UDungreedConstValue::AutoSize, true);
	Renderer->SetOrder(ERenderOrder::Cursor);
}

void ACursor::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

