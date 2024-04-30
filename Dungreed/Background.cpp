#include "PreCompile.h"
#include "Background.h"

ABackground::ABackground()
{
	DefaultComponent = CreateDefaultSubObject<UDefaultSceneComponent>("DefaultComponent");
	SetRoot(DefaultComponent);

	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(DefaultComponent);

	ColMapRenderer = CreateDefaultSubObject<USpriteRenderer>("ColMapRenderer");
	ColMapRenderer->SetupAttachment(DefaultComponent);

	//TileRenderer = CreateDefaultSubObject<UTileRenderer>("TileRenderer");
	//SetRoot(TileRenderer);
}

ABackground::~ABackground()
{
}

void ABackground::MapRendererSwitch()
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

void ABackground::BeginPlay()
{
	Super::BeginPlay();

	Renderer->SetSprite("Town.png");
	Renderer->SetOrder(ERenderOrder::Map);
	Renderer->SetAutoSize(UDungreedConstValue::AutoSize, true);


	ColMapRenderer->SetSprite("Town_Col.png");
	ColMapRenderer->SetOrder(ERenderOrder::ColMap);
	ColMapRenderer->SetAutoSize(UDungreedConstValue::AutoSize, true);
	ColMapRenderer->SetActive(false);

	//UEngineSerializer Ser;

	//Dir.MoveToSearchChild("Resources");
	//Dir.Move("Save");
	//UEngineFile File = Dir.GetPathFromFile("SaveData.Data");
	//File.Open(EIOOpenMode::Read, EIODataType::Binary);
	//File.Load(Ser);

	//Ser >> TilesData;
	//TileRenderer->CreateTileMap("Tiles.png", { 64.0f, 64.0f }, TilesData.size(), TilesData[0].size(), 0);
	//for (size_t y = 0; y < TilesData.size(); y++)
	//{
	//	for (size_t x = 0; x < TilesData[y].size(); x++)
	//	{
	//		TileRenderer->SetTile(x, y, TilesData[y][x]);
	//	}
	//}
	//TileRenderer->SetOrder(ERenderOrder::Map);
}

void ABackground::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

