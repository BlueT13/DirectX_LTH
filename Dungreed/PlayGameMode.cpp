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

	UDungreedConstValue::MapTexture = UEngineTexture::FindRes("1.png");
	UDungreedConstValue::MapTextureScale = UDungreedConstValue::MapTexture->GetScale();

	Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation({ 0.0f, -0.0f, -100.0f });

	{
		Player = GetWorld()->SpawnActor<APlayer>("Player");
		Player->SetActorLocation({ 0.0f, 700.0f, 0.0f });
	}

	{
		std::shared_ptr<ABackground> Background = GetWorld()->SpawnActor<ABackground>("Background");
		// (���� x�� ����/2, ���� y�� ����/2, 0.0f)
		Background->SetActorLocation({ 640.0f, 640.0f, 0.0f });
	}

}

void APlayGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	Camera->SetActorLocation({ Player->GetActorLocation().X,Player->GetActorLocation().Y,-100.0f });
}