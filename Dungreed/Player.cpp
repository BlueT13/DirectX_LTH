#include "PreCompile.h"
#include "Player.h"

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

	StateInit();
}

void APlayer::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	State.Update(_DeltaTime);
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

void APlayer::ColorColCheck(float _DeltaTime)
{
	std::shared_ptr<UEngineTexture> Tex = UDungreedConstValue::ColMap;
	float MapY = Tex->GetScale().Y * UDungreedConstValue::AutoSize;

	PlayerPos = GetActorLocation();
	// PlayerPos.Y = ¸ÊÀÇ yÃà ±æÀÌ - PlayerPos.Y;
	PlayerPos.Y = MapY - PlayerPos.Y;
	PlayerPos /= UDungreedConstValue::AutoSize;

	Color = Tex->GetColor(PlayerPos, Color8Bit::White);
}
