#include "PreCompile.h"
#include "TileMapLevel.h"
#include <EngineCore/TileRenderer.h>
#include "TileMap.h"


ATileMapLevel::ATileMapLevel() 
{
}

ATileMapLevel::~ATileMapLevel() 
{
}

void ATileMapLevel::BeginPlay()
{
	Super::BeginPlay();

	TileMap = GetWorld()->SpawnActor<ATileMap>("TileMap", ERenderOrder::Map);
}

void ATileMapLevel::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
