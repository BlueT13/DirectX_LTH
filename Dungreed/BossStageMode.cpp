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

	BossStageMap = GetWorld()->SpawnActor<ABossStageMap>("BossStageMap");
	float MapHalfX = UDungreedConstValue::ColMap->GetScale().hX();
	float MapHalfY = UDungreedConstValue::ColMap->GetScale().hY();
	BossStageMap->SetActorLocation({ MapHalfX * UDungreedConstValue::AutoSize, MapHalfY * UDungreedConstValue::AutoSize, 0.0f });

	Player = GetWorld()->SpawnActor<APlayer>("Player");
	Player->SetActorLocation({ MapHalfX, MapHalfY + 200.0f, 0.0f });
}

void ABossStageMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	Camera->SetActorLocation({ Player->GetActorLocation().X, Player->GetActorLocation().Y,-100.0f });

	float4 Pos = Camera->GetActorLocation();

	// 카메라 이동 범위 제한
	float a = Camera->GetActorLocation().X - GEngine->EngineWindow.GetWindowScale().hX();
	if (a < 0)
	{
		Camera->SetActorLocation({ Camera->GetActorLocation().X - a, Camera->GetActorLocation().Y, -100.0f });
	}

	if (true == UEngineInput::IsDown('O'))
	{
		BossStageMap->MapRendererSwitch();
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
