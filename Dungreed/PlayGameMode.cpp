#include "PreCompile.h"
#include "PlayGameMode.h"

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
	Player->SetActorLocation({ MapHalfX - 100.0f, MapHalfY - 300.0f, 0.0f });

	DungeonEat = GetWorld()->SpawnActor<ADungeonEat>("DungeonEat", EUpdateOrder::Map);
	DungeonEat->SetActorLocation({ MapHalfX + 200.0f, MapHalfY - 372.0f, 0.0f });

	Background = GetWorld()->SpawnActor<ABackground>("Background", EUpdateOrder::Background);

	// UI
	UEngineFont::Load("¸¼Àº °íµñ");

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
	PlayerHpUI->SetText(PlayerHpString);

	HpImage = CreateWidget<UImage>(GetWorld(), "StartImage");
	HpImage->AddToViewPort(0);
	HpImage->SetSprite("PlayerHp.png");
	HpImage->SetAutoSize(1.0f, true);
	HpImage->SetPosition({ -460, 280 });

	// »ç¿îµå
	TownSound = UEngineSound::SoundPlay("0.Town.wav");
	TownSound.SetVolume(1.0f);
	TownSound.Loop();
	TownSound.Off();
}

void APlayGameMode::Tick(float _DeltaTime)
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
		TownMap->MapRendererSwitch();
		Background->MapRendererSwitch();
	}

	if (true == UEngineInput::IsDown('P'))
	{
		GEngine->ChangeLevel("BossStageLevel");
	}
	if (true == UEngineInput::IsDown(VK_ESCAPE))
	{
		GEngine->EngineWindow.Off();
	}
}

void APlayGameMode::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);

	GEngine->EngineWindow.CursorOn();

	TownSound.Off();
}

void APlayGameMode::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);

	GEngine->EngineWindow.CursorOff();

	APlayer::MainPlayer = Player;

	TownSound.On();
}
