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

	UDungreedConstValue::ColMap = UEngineTexture::FindRes("Tow_Col.png");
	UDungreedConstValue::ColMapScale = UDungreedConstValue::ColMap->GetScale();

	Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation({ 0.0f, -0.0f, -100.0f });

	std::shared_ptr<ABackground> Background = GetWorld()->SpawnActor<ABackground>("Background");
	// (¸ÊÀÇ xÃà ±æÀÌ/2, ¸ÊÀÇ yÃà ±æÀÌ/2, 0.0f)
	float MapHalfX = Background->GetActorScale3D().hX();
	float MapHalfY = Background->GetActorScale3D().hY();
	Background->SetActorLocation({ MapHalfX, MapHalfY, 0.0f });

	Player = GetWorld()->SpawnActor<APlayer>("Player");
	Player->SetActorLocation({ MapHalfX, MapHalfY + 100.0f, 0.0f });
}

void APlayGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	Camera->SetActorLocation({ Player->GetActorLocation().X,Player->GetActorLocation().Y,-100.0f });
}