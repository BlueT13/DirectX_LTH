#include "PreCompile.h"
#include "BossStageTileMap.h"

ABossStageTileMap::ABossStageTileMap()
{
	DefaultComponent = CreateDefaultSubObject<UDefaultSceneComponent>("DefaultComponent");
	SetRoot(DefaultComponent);

	TileRenderer = CreateDefaultSubObject<UTileRenderer>("TileRenderer");
	TileRenderer->SetupAttachment(DefaultComponent);
}

ABossStageTileMap::~ABossStageTileMap()
{
}

void ABossStageTileMap::BeginPlay()
{
	Super::BeginPlay();

	UEngineSerializer Ser;

	Dir.MoveToSearchChild("Resources");
	Dir.Move("Save");
	UEngineFile File = Dir.GetPathFromFile("SaveData.Data");
	File.Open(EIOOpenMode::Read, EIODataType::Binary);
	File.Load(Ser);

	Ser >> TilesData;
	TileRenderer->CreateTileMap("Tiles.png", { 64.0f, 64.0f }, TilesData[0].size(), TilesData.size(), 0);
	for (size_t y = 0; y < TilesData.size(); y++)
	{
		for (size_t x = 0; x < TilesData[y].size(); x++)
		{
			TileRenderer->SetTile(x, y, TilesData[y][x]);
		}
	}
	TileRenderer->SetOrder(ERenderOrder::TileMap);
}

void ABossStageTileMap::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

