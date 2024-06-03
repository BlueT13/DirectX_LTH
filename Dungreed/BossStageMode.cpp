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
	
	BossStageTileMap = GetWorld()->SpawnActor<ABossStageTileMap>("BossStageTileMap", EUpdateOrder::Map);

	Player = GetWorld()->SpawnActor<APlayer>("Player", EUpdateOrder::Player);
	Player->SetActorLocation({ MapHalfX - 480.0f, MapHalfY + 320.0f, 0.0f });

	Envyrok = GetWorld()->SpawnActor<AEnvyrok>("Envyrok", EUpdateOrder::Monster);
	Envyrok->SetActorLocation({ MapHalfX + 512.0f, MapHalfY - 96.0f, 0.0f });

	// UI
	PlayerFullHpUI = CreateWidget<UTextWidget>(GetWorld(), "PlayerHpUI");
	PlayerFullHpUI->AddToViewPort(1);
	PlayerFullHpUI->SetFont("¸¼Àº °íµñ");
	PlayerFullHpUI->SetScale(32.0f);
	PlayerFullHpUI->SetColor(Color8Bit::White);
	PlayerFullHpUI->SetPosition({ -400, 280 });
	PlayerHpString = std::to_string(Player->PlayerHp);
	PlayerFullHpUI->SetText("/ " + PlayerHpString);

	PlayerHpUI = CreateWidget<UTextWidget>(GetWorld(), "PlayerHpUI");
	PlayerHpUI->AddToViewPort(1);
	PlayerHpUI->SetFont("¸¼Àº °íµñ");
	PlayerHpUI->SetScale(32.0f);
	PlayerHpUI->SetColor(Color8Bit::White);
	PlayerHpUI->SetPosition({ -460, 280 });

	HpImage = CreateWidget<UImage>(GetWorld(), "StartImage");
	HpImage->AddToViewPort(0);
	HpImage->SetSprite("PlayerHp.png");
	HpImage->SetAutoSize(1.0f, true);
	HpImage->SetPosition({ -460, 280 });

	// »ç¿îµå
	BossStageSound = UEngineSound::SoundPlay("4.lavaboss.wav");
	BossStageSound.SetVolume(1.0f);
	BossStageSound.Loop();
	BossStageSound.Off();
}

void ABossStageMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	Camera->SetActorLocation({ Player->GetActorLocation().X, Player->GetActorLocation().Y + 96.0f, -100.0f });

	// Ä«¸Þ¶ó ÀÌµ¿ ¹üÀ§ Á¦ÇÑ
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

	PlayerHpString = std::to_string(Player->PlayerHp);
	PlayerHpUI->SetText(PlayerHpString);
}

void ABossStageMode::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);

	GEngine->EngineWindow.CursorOn();

	BossStageSound.Off();
}

void ABossStageMode::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);

	GEngine->EngineWindow.CursorOff();

	APlayer::MainPlayer = Player;

	BossStageSound.On();
}
