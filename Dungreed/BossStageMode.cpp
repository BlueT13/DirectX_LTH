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

	Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation({ 0.0f, 0.0f, -100.0f });

	BossStageMap = GetWorld()->SpawnActor<ABossStageMap>("BossStageMap", EUpdateOrder::Map);
	MapX = UDungreedConstValue::ColMap->GetScale().X;
	MapY = UDungreedConstValue::ColMap->GetScale().Y;
	MapHalfX = UDungreedConstValue::ColMap->GetScale().hX();
	MapHalfY = UDungreedConstValue::ColMap->GetScale().hY();
	BossStageMap->SetActorLocation({ MapHalfX * UDungreedConstValue::AutoSize, MapHalfY * UDungreedConstValue::AutoSize, 0.0f });

	Player = GetWorld()->SpawnActor<APlayer>("Player", EUpdateOrder::Player);
	Player->SetActorLocation({ MapHalfX - 480.0f, MapHalfY + 320.0f, 0.0f });

	Envyrok = GetWorld()->SpawnActor<AEnvyrok>("Envyrok", EUpdateOrder::Monster);
	Envyrok->SetActorLocation({ MapHalfX + 512.0f, MapHalfY - 96.0f, 0.0f });

	//Envyrok = GetWorld()->SpawnActor<AEnvyrok>("Envyrok", 100);
	//GEngine->SetOrderTimeScale(100, 0.2f);
	//GEngine->SetGlobalTimeScale(0.1f);
}

void ABossStageMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	Camera->SetActorLocation({ Player->GetActorLocation().X, Player->GetActorLocation().Y + 96.0f, -100.0f });

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
		BossStageMap->MapRendererSwitch();
	}

	if (true == UEngineInput::IsDown(VK_ESCAPE))
	{
		GEngine->EngineWindow.Off();
	}
}

void ABossStageMode::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);

	GEngine->EngineWindow.CursorOn();
}

void ABossStageMode::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);

	GEngine->EngineWindow.CursorOff();

	APlayer::MainPlayer = Player;
}
