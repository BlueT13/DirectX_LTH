#include "PreCompile.h"
#include "BossStageMode.h"

ABossStageMode::ABossStageMode() 
{
}

ABossStageMode::~ABossStageMode() 
{
}

void ABossStageMode::BeginPlay()
{
	Super::BeginPlay();

	UDungreedConstValue::ColMap = UEngineTexture::FindRes("BossRoom_Col.png");
}

void ABossStageMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void ABossStageMode::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);
}

void ABossStageMode::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);
}
