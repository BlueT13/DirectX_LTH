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

	UDungreedConstValue::ColMap = UEngineTexture::FindRes("Town_Col.png");
	UDungreedConstValue::ColMapScale = UDungreedConstValue::ColMap->GetScale();

	Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation({ 0.0f, -0.0f, -100.0f });

	Background = GetWorld()->SpawnActor<ABackground>("Background");
	// (���� x�� ����/2, ���� y�� ����/2, 0.0f)
	float MapHalfX = Background->GetActorScale3D().hX();
	float MapHalfY = Background->GetActorScale3D().hY();
	Background->SetActorLocation({ MapHalfX, MapHalfY, 0.0f });

	Player = GetWorld()->SpawnActor<APlayer>("Player");
	Player->SetActorLocation({ MapHalfX, MapHalfY + 200.0f, 0.0f });

	GEngine->EngineWindow.CursorOff();
}

void APlayGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	Camera->SetActorLocation({ Player->GetActorLocation().X, Player->GetActorLocation().Y,-100.0f });

	if (true == UEngineInput::IsDown('O'))
	{
		Background->MapRendererSwitch();
	}
}

void APlayGameMode::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);
}

void APlayGameMode::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);

	APlayer::MainPlayer = Player;
}
