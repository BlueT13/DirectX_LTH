#include "PreCompile.h"
#include "CreateMapMode.h"

ACreateMapMode::ACreateMapMode() 
{
}

ACreateMapMode::~ACreateMapMode() 
{
}

void ACreateMapMode::BeginPlay()
{
	Super::BeginPlay();

	MyMap = GetWorld()->SpawnActor<AMyMap>("MyMap", EUpdateOrder::Map);
	MyMap->SetActorLocation({ 640.0f, 640.0f, 100.0f });
}

void ACreateMapMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void ACreateMapMode::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);
}

void ACreateMapMode::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);

	
}

