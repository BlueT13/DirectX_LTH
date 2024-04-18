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

	MyMap = GetWorld()->SpawnActor<AMyMap>("MyMap");
	MyMap->SetActorLocation({ 640.0f, 640.0f, 100.0f });
}

void ACreateMapMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

