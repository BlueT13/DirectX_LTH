#include "PreCompile.h"
#include "PlayGameMode.h"
#include "Player.h"

APlayGameMode::APlayGameMode() 
{
}

APlayGameMode::~APlayGameMode() 
{
}

void APlayGameMode::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->SpawnActor<APlayer>("Player");
}

void APlayGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

}