#include "PreCompile.h"
#include "Background.h"

ABackground::ABackground()
{
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	SetRoot(Renderer);

	//TileRenderer = CreateDefaultSubObject<UTileRenderer>("TileRenderer");
	//SetRoot(TileRenderer);
}

ABackground::~ABackground()
{
}

void ABackground::BeginPlay()
{
	Super::BeginPlay();

	Renderer->SetSprite("Town.png");
	Renderer->SetAutoSize(UDungreedConstValue::AutoSize, true);

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

