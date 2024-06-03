#include "PreCompile.h"
#include "BossStageMap.h"

ABossStageMap::ABossStageMap()
{
	DefaultComponent = CreateDefaultSubObject<UDefaultSceneComponent>("DefaultComponent");
	SetRoot(DefaultComponent);

	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(DefaultComponent);

	ColMapRenderer = CreateDefaultSubObject<USpriteRenderer>("ColMapRenderer");
	ColMapRenderer->SetupAttachment(DefaultComponent);
}

ABossStageMap::~ABossStageMap()
{
}

void ABossStageMap::MapRendererSwitch()
{
	if (Renderer->IsActive())
	{
		Renderer->SetActive(false);
		ColMapRenderer->SetActive(true);
	}
	else
	{
		Renderer->SetActive(true);
		ColMapRenderer->SetActive(false);
	}
}

void ABossStageMap::BeginPlay()
{
	Super::BeginPlay();

	Renderer->SetSprite("Background.png");
	Renderer->SetOrder(ERenderOrder::Map);
	Renderer->SetAutoSize(UDungreedConstValue::AutoSize, true);

	ColMapRenderer->SetSprite("BossRoom_Col.png");
	ColMapRenderer->SetOrder(ERenderOrder::ColMap);
	ColMapRenderer->SetAutoSize(UDungreedConstValue::AutoSize, true);
	ColMapRenderer->SetActive(false);

	UEngineSerializer Ser;
}

void ABossStageMap::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

