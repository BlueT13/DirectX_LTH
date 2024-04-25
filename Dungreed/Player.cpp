#include "PreCompile.h"
#include "Player.h"

std::shared_ptr<APlayer> APlayer::MainPlayer = nullptr;

APlayer::APlayer()
{
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	SetRoot(Renderer);
	InputOn();
}

APlayer::~APlayer()
{
}

void APlayer::BeginPlay()
{
	Super::BeginPlay();

	Renderer->CreateAnimation("Die", "Die", 0.1f);
	Renderer->CreateAnimation("Idle", "Idle", 0.1f);
	Renderer->CreateAnimation("Jump", "Jump", 0.1f);
	Renderer->CreateAnimation("Run", "Run", 0.1f);

	Renderer->SetAutoSize(UDungreedConstValue::AutoSize, true);
	Renderer->SetOrder(ERenderOrder::Player);
	Renderer->SetPivot(EPivot::BOT);

	PlayerScale = GetActorScale3D();

	Cursor = GetWorld()->SpawnActor<ACursor>("Cursor");
	WindowScale = GEngine->EngineWindow.GetWindowScale();

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
	std::shared_ptr<UEngineTexture> Tex = UDungreedConstValue::ColMap;
	float MapY = Tex->GetScale().Y * UDungreedConstValue::AutoSize;

	PlayerPos = GetActorLocation();
	// PlayerPos.Y = ¸ÊÀÇ yÃà ±æÀÌ - PlayerPos.Y;
	PlayerPos.Y = MapY - PlayerPos.Y;
	PlayerPos /= UDungreedConstValue::AutoSize;

	LeftColor = Tex->GetColor({ PlayerPos.X - 4.0f, PlayerPos.Y, PlayerPos.Z }, Color8Bit::Black);
	RightColor = Tex->GetColor({ PlayerPos.X + 4.0f, PlayerPos.Y, PlayerPos.Z }, Color8Bit::Black);
	UpColor = Tex->GetColor({ PlayerPos.X, PlayerPos.Y - 20.0f, PlayerPos.Z }, Color8Bit::Black);
	DownColor = Tex->GetColor({ PlayerPos.X, PlayerPos.Y, PlayerPos.Z }, Color8Bit::Black);
	BottomColor = Tex->GetColor({ PlayerPos.X, PlayerPos.Y - 1.0f, PlayerPos.Z }, Color8Bit::Black);
}

void APlayer::CursorCheck()
{
	PlayerPos = GetActorLocation();
	CursorPos = GEngine->EngineWindow.GetScreenMousePos();
	InGameCursorPos = { PlayerPos.X + CursorPos.X - WindowScale.hX() , PlayerPos.Y - CursorPos.Y + WindowScale.hY(), 0.0f };
	Cursor->SetActorLocation(InGameCursorPos);
}
