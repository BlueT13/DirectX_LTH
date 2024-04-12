#include "PreCompile.h"
#include "PlayGameMode.h"
#include "Player.h"
#include "Background.h"
#include <EngineCore/Camera.h>

APlayGameMode::APlayGameMode() 
{
}

APlayGameMode::~APlayGameMode() 
{
}

void APlayGameMode::BeginPlay()
{
	Super::BeginPlay();

	UDungreedConstValue::MapTexture = UEngineTexture::FindRes("Background.png");
	UDungreedConstValue::MapTextureScale = UDungreedConstValue::MapTexture->GetScale();

	std::shared_ptr<UCamera> Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation(FVector(0.0f, 0.0f, -100.0f));

	GetWorld()->SpawnActor<APlayer>("Player");

	std::shared_ptr<ABackground> Background = GetWorld()->SpawnActor<ABackground>("Background");
	Background->SetActorLocation({ 0.0f,0.0f, 0.0f });
}

void APlayGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

}