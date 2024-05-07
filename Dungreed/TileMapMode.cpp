#include "PreCompile.h"
#include "TileMapMode.h"
#include <EngineCore/TileRenderer.h>
#include "TileMap.h"


ATileMapMode::ATileMapMode() 
{
}

ATileMapMode::~ATileMapMode() 
{
}

void ATileMapMode::BeginPlay()
{
	Super::BeginPlay();

	TileMap = GetWorld()->SpawnActor<ATileMap>("TileMap", EUpdateOrder::Map);
}

void ATileMapMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
