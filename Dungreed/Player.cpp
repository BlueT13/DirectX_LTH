#include "PreCompile.h"
#include "Player.h"

std::shared_ptr<APlayer> APlayer::MainPlayer = nullptr;

APlayer::APlayer()
{
	DefaultRenderer = CreateDefaultSubObject<USpriteRenderer>("DefaultRenderer");
	SetRoot(DefaultRenderer);

	RotationRenderer = CreateDefaultSubObject<USpriteRenderer>("RotationRenderer");
	RotationRenderer->SetupAttachment(DefaultRenderer);

	BodyRenderer = CreateDefaultSubObject<USpriteRenderer>("BodyRenderer");
	BodyRenderer->SetupAttachment(DefaultRenderer);

	HandRenderer = CreateDefaultSubObject<USpriteRenderer>("HandRenderer");
	HandRenderer->SetupAttachment(DefaultRenderer);

	WeaponRenderer = CreateDefaultSubObject<USpriteRenderer>("WeaponRenderer");
	WeaponRenderer->SetupAttachment(RotationRenderer);

	InputOn();
}

APlayer::~APlayer()
{
}

void APlayer::BeginPlay()
{
	Super::BeginPlay();

	BodyRenderer->CreateAnimation("Die", "Die", 0.1f);
	BodyRenderer->CreateAnimation("Idle", "Idle", 0.1f);
	BodyRenderer->CreateAnimation("Jump", "Jump", 0.1f);
	BodyRenderer->CreateAnimation("Run", "Run", 0.1f);

	BodyRenderer->SetAutoSize(UDungreedConstValue::AutoSize, true);
	BodyRenderer->SetOrder(ERenderOrder::Player);
	BodyRenderer->SetPivot(EPivot::BOT);

	HandRenderer->SetSprite("Hand.png");
	HandRenderer->SetAutoSize(UDungreedConstValue::AutoSize, true);
	HandRenderer->SetOrder(ERenderOrder::Player);

	WeaponRenderer->SetSprite("ShortSword010.png");
	WeaponRenderer->SetAutoSize(UDungreedConstValue::AutoSize, true);
	WeaponRenderer->SetOrder(ERenderOrder::WeaponBack);

	PlayerScale = GetActorScale3D();

	Cursor = GetWorld()->SpawnActor<ACursor>("Cursor");
	WindowScale = GEngine->EngineWindow.GetWindowScale();

	ColMapTex = UDungreedConstValue::ColMap;
	ColMapY = ColMapTex->GetScale().Y * UDungreedConstValue::AutoSize;

	StateInit();
}

void APlayer::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
	CursorCheck();

	DebugMessageFunction();
}

void APlayer::DebugMessageFunction()
{
	{
		std::string Msg = std::format("PlayerPos : {}\n", GetActorLocation().ToString());
		UEngineDebugMsgWindow::PushMsg(Msg);
	}

	{
		std::string Msg = std::format("MousePos : {}\n", GEngine->EngineWindow.GetScreenMousePos().ToString());
		UEngineDebugMsgWindow::PushMsg(Msg);
	}
}

void APlayer::ColorColCheck()
{
	CalPlayerPos();
	BottomColor = ColMapTex->GetColor({ PlayerPos.X, PlayerPos.Y, PlayerPos.Z }, Color8Bit::Black);
	BottomLeftColor = ColMapTex->GetColor({ PlayerPos.X - 4.0f, PlayerPos.Y, PlayerPos.Z }, Color8Bit::Black);
	BottomRightColor = ColMapTex->GetColor({ PlayerPos.X + 4.0f, PlayerPos.Y, PlayerPos.Z }, Color8Bit::Black);
	TopColor = ColMapTex->GetColor({ PlayerPos.X, PlayerPos.Y - 20.0f, PlayerPos.Z }, Color8Bit::Black);
	LeftColor = ColMapTex->GetColor({ PlayerPos.X - 8.0f, PlayerPos.Y - 10.0f, PlayerPos.Z }, Color8Bit::Black);
	RightColor = ColMapTex->GetColor({ PlayerPos.X + 8.0f, PlayerPos.Y - 10.0f, PlayerPos.Z }, Color8Bit::Black);

	GroundColor = ColMapTex->GetColor({ PlayerPos.X, PlayerPos.Y - 1.0f, PlayerPos.Z }, Color8Bit::Black);

	NextBottomLeftColor = ColMapTex->GetColor({ PlayerNextPos.X - 8.0f, PlayerNextPos.Y - 1.0f, PlayerNextPos.Z }, Color8Bit::Black);
	NextBottomRightColor = ColMapTex->GetColor({ PlayerNextPos.X + 8.0f, PlayerNextPos.Y - 1.0f, PlayerNextPos.Z }, Color8Bit::Black);
	NextTopColor = ColMapTex->GetColor({ PlayerNextPos.X, PlayerNextPos.Y - 20.0f, PlayerNextPos.Z }, Color8Bit::Black);
}

void APlayer::CalPlayerPos()
{
	PlayerPos = GetActorLocation();
	// PlayerPos.Y = ¸ÊÀÇ yÃà ±æÀÌ - PlayerPos.Y;
	PlayerPos.Y = ColMapY - PlayerPos.Y;
	PlayerPos /= UDungreedConstValue::AutoSize;
}

void APlayer::CursorCheck()
{
	PlayerPos = GetActorLocation();
	CursorPos = GEngine->EngineWindow.GetScreenMousePos();

	//InGameCursorPos = GetWorld()->GetMainCamera()->ScreenPosToWorldPos(GEngine->EngineWindow.GetScreenMousePos());
	InGameCursorPos = { PlayerPos.X + CursorPos.X - WindowScale.hX() , PlayerPos.Y - CursorPos.Y + WindowScale.hY(), 0.0f };

	Cursor->SetActorLocation(InGameCursorPos);
}
