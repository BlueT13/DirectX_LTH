#include "PreCompile.h"
#include "PlayGameMode.h"
#include "Player.h"
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

	Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation({ 0.0f, 0.0f, -100.0f });

	TownMap = GetWorld()->SpawnActor<ATownMap>("TownMap", EUpdateOrder::Map);
	MapX = UDungreedConstValue::ColMap->GetScale().X;
	MapY = UDungreedConstValue::ColMap->GetScale().Y;
	MapHalfX = UDungreedConstValue::ColMap->GetScale().hX();
	MapHalfY = UDungreedConstValue::ColMap->GetScale().hY();
	TownMap->SetActorLocation({ MapHalfX * UDungreedConstValue::AutoSize, MapHalfY * UDungreedConstValue::AutoSize, 0.0f });

	Player = GetWorld()->SpawnActor<APlayer>("Player", EUpdateOrder::Player);
	Player->SetActorLocation({ MapHalfX, MapHalfY + 200.0f, 0.0f });

	Background = GetWorld()->SpawnActor<ABackground>("Background", EUpdateOrder::Background);
}

void APlayGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	Camera->SetActorLocation({ Player->GetActorLocation().X, Player->GetActorLocation().Y,-100.0f });

	// 카메라 이동 범위 제한
	float CameraLeft = Camera->GetActorLocation().X - GEngine->EngineWindow.GetWindowScale().hX();
	float CameraBottom = Camera->GetActorLocation().Y - GEngine->EngineWindow.GetWindowScale().hY();
	float CameraRight = Camera->GetActorLocation().X + GEngine->EngineWindow.GetWindowScale().hX();
	float CameraTop = Camera->GetActorLocation().Y + GEngine->EngineWindow.GetWindowScale().hY();

	if (0 > CameraLeft)
	{
		Camera->SetActorLocation({ GEngine->EngineWindow.GetWindowScale().hX(), Camera->GetActorLocation().Y, -100.0f });
	}
	if (0 > CameraBottom)
	{
		Camera->SetActorLocation({ Camera->GetActorLocation().X, GEngine->EngineWindow.GetWindowScale().hY(), -100.0f });
	}
	if (MapX < CameraRight)
	{
		Camera->SetActorLocation({ MapX - GEngine->EngineWindow.GetWindowScale().hX(), Camera->GetActorLocation().Y, -100.0f });
	}
	if (MapY < CameraTop)
	{
		Camera->SetActorLocation({ Camera->GetActorLocation().X, MapY - GEngine->EngineWindow.GetWindowScale().hY(), -100.0f });
	}

	if (true == UEngineInput::IsDown('O'))
	{
		TownMap->MapRendererSwitch();
	}
}

void APlayGameMode::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);

	GEngine->EngineWindow.CursorOn();
}

void APlayGameMode::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);

	GEngine->EngineWindow.CursorOff();

	APlayer::MainPlayer = Player;
}
