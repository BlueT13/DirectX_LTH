#include "PreCompile.h"
#include "TileMap.h"
#include <EngineCore/TileRenderer.h>

ATileMap::ATileMap() 
{
	TileRenderer = CreateDefaultSubObject<UTileRenderer>("Renderer");
	SetRoot(TileRenderer);
}

ATileMap::~ATileMap() 
{
}

