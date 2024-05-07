#include "PreCompile.h"
#include "Player.h"

std::shared_ptr<APlayer> APlayer::MainPlayer = nullptr;

APlayer::APlayer()
{
	DefaultComponent = CreateDefaultSubObject<UDefaultSceneComponent>("DefaultComponent");
	SetRoot(DefaultComponent);

	RotationComponent = CreateDefaultSubObject<UDefaultSceneComponent>("RotationComponent");
	RotationComponent->SetupAttachment(DefaultComponent);

	BodyRenderer = CreateDefaultSubObject<USpriteRenderer>("BodyRenderer");
	BodyRenderer->SetupAttachment(DefaultComponent);

	HandRenderer = CreateDefaultSubObject<USpriteRenderer>("HandRenderer");
	HandRenderer->SetupAttachment(DefaultComponent);

	WeaponRenderer = CreateDefaultSubObject<USpriteRenderer>("WeaponRenderer");
	WeaponRenderer->SetupAttachment(RotationComponent);

	//AttackEffectRenderer = CreateDefaultSubObject<USpriteRenderer>("WeaponRenderer");
	//AttackEffectRenderer->SetupAttachment(RotationComponent);

	PlayerCollision = CreateDefaultSubObject<UCollision>("PlayerCollision");
	PlayerCollision->SetupAttachment(DefaultComponent);
	// Collision은 반드시 SetCollisionGroup을 해야 한다.
	PlayerCollision->SetCollisionGroup(ECollisionOrder::Player);
	PlayerCollision->SetCollisionType(ECollisionType::Rect);

	InputOn();
}

APlayer::~APlayer()
{
}

void APlayer::BeginPlay()
{
	Super::BeginPlay();

	BodyRenderer->CreateAnimation("PlayerDie", "PlayerDie", 0.1f);
	BodyRenderer->CreateAnimation("PlayerIdle", "PlayerIdle", 0.1f);
	BodyRenderer->CreateAnimation("PlayerJump", "PlayerJump", 0.1f);
	BodyRenderer->CreateAnimation("PlayerRun", "PlayerRun", 0.1f);

	BodyRenderer->SetAutoSize(UDungreedConstValue::AutoSize, true);
	BodyRenderer->SetOrder(ERenderOrder::Player);
	BodyRenderer->SetPivot(EPivot::BOT);

	HandRenderer->SetSprite("PlayerHand.png");
	HandRenderer->SetAutoSize(UDungreedConstValue::AutoSize, true);
	HandRenderer->SetOrder(ERenderOrder::Player);

	WeaponRenderer->SetSprite("ShortSword.png");
	WeaponRenderer->SetAutoSize(UDungreedConstValue::AutoSize, true);
	WeaponRenderer->SetOrder(ERenderOrder::WeaponBack);
	WeaponRenderer->SetPivot(EPivot::BOT);

	//AttackEffectRenderer->CreateAnimation("AttackEffect", "AttackEffect", 0.1f);
	//AttackEffectRenderer->SetAutoSize(UDungreedConstValue::AutoSize, true);
	//AttackEffectRenderer->SetOrder(ERenderOrder::Player);

	PlayerCollision->SetScale(PlayerColScale);
	PlayerCollision->SetPosition({ 0,32,0 });

	Cursor = GetWorld()->SpawnActor<ACursor>("Cursor",EUpdateOrder::Cursor);
	WindowScale = GEngine->EngineWindow.GetWindowScale();

	ColMapTex = UDungreedConstValue::ColMap;
	ColMapY = ColMapTex->GetScale().Y * UDungreedConstValue::AutoSize;

	HandRenderer->SetPosition({ -26, 20, 0 });

	// 무기 최초 위치 설정
	RotationComponent->SetPosition({ 24, 40, 0 });
	WeaponRenderer->SetPosition({ -4, 24, 0 });
	WeaponRenderer->SetRotationDeg({ 0, 0, 15 });

	//AttackEffectRenderer->SetPosition({ 20,0,0 });

	FVector UpPos = { 0,40,0 };
	PlayerCenterPos = GetActorLocation() + UpPos;

	StateInit();
}

void APlayer::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	CursorCheck();
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

void APlayer::ColorColCheck()
{
	CalPlayerPos();
	BottomColor = ColMapTex->GetColor({ PlayerPos.X, PlayerPos.Y, PlayerPos.Z }, Color8Bit::Black);
	BottomLeftColor = ColMapTex->GetColor({ PlayerPos.X - 30.0f, PlayerPos.Y, PlayerPos.Z }, Color8Bit::Black);
	BottomRightColor = ColMapTex->GetColor({ PlayerPos.X + 30.0f, PlayerPos.Y, PlayerPos.Z }, Color8Bit::Black);
	TopColor = ColMapTex->GetColor({ PlayerPos.X, PlayerPos.Y - 80.0f, PlayerPos.Z }, Color8Bit::Black);
	LeftColor = ColMapTex->GetColor({ PlayerPos.X - 30.0f, PlayerPos.Y - 40.0f, PlayerPos.Z }, Color8Bit::Black);
	RightColor = ColMapTex->GetColor({ PlayerPos.X + 30.0f, PlayerPos.Y - 40.0f, PlayerPos.Z }, Color8Bit::Black);

	GroundColor = ColMapTex->GetColor({ PlayerPos.X, PlayerPos.Y - 1.0f, PlayerPos.Z }, Color8Bit::Black);

	NextBottomLeftColor = ColMapTex->GetColor({ PlayerNextPos.X - 40.0f, PlayerNextPos.Y - 1.0f, PlayerNextPos.Z }, Color8Bit::Black);
	NextBottomRightColor = ColMapTex->GetColor({ PlayerNextPos.X + 40.0f, PlayerNextPos.Y - 1.0f, PlayerNextPos.Z }, Color8Bit::Black);
	NextTopColor = ColMapTex->GetColor({ PlayerNextPos.X, PlayerNextPos.Y - 80.0f, PlayerNextPos.Z }, Color8Bit::Black);
}

void APlayer::CalPlayerPos()
{
	PlayerPos = GetActorLocation();
	// PlayerPos.Y = 맵의 y축 길이 - PlayerPos.Y;
	PlayerPos.Y = ColMapY - PlayerPos.Y;
	PlayerPos /= UDungreedConstValue::AutoSize;
}

void APlayer::CursorCheck()
{
	PlayerPos = GetActorLocation();
	CursorPos = GEngine->EngineWindow.GetScreenMousePos();

	InGameCursorPos = GetWorld()->GetMainCamera()->ScreenPosToWorldPos(GEngine->EngineWindow.GetScreenMousePos());
	//InGameCursorPos = { PlayerPos.X + CursorPos.X - WindowScale.hX() , PlayerPos.Y - CursorPos.Y + WindowScale.hY(), 0.0f };

	Cursor->SetActorLocation(InGameCursorPos);
}
