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
	Renderer->SetAutoSize(1.0f, true);
	Renderer->SetOrder(ERenderOrder::Cursor);
}

void ACursor::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	//CursorPos = GEngine->EngineWindow.GetScreenMousePos();
	//SetActorLocation(CursorPos);
}

