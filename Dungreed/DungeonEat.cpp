#include "PreCompile.h"
#include "DungeonEat.h"
#include "Player.h"

ADungeonEat::ADungeonEat()
{
	DefaultComponent = CreateDefaultSubObject<UDefaultSceneComponent>("DefaultComponent");
	SetRoot(DefaultComponent);

	Renderer0 = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer0->SetupAttachment(DefaultComponent);

	Renderer1 = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer1->SetupAttachment(DefaultComponent);

	Collision = CreateDefaultSubObject<UCollision>("Collision");
	Collision->SetupAttachment(DefaultComponent);
	// Collision은 반드시 SetCollisionGroup을 해야 한다.
	Collision->SetCollisionGroup(ECollisionOrder::Map);
	Collision->SetCollisionType(ECollisionType::Rect);
}

ADungeonEat::~ADungeonEat()
{
}

void ADungeonEat::BeginPlay()
{
	Super::BeginPlay();

	Renderer0->CreateAnimation("EatStart", "DungeonEat_sheet.png", 0.1f, false, 0, 8);
	Renderer0->SetAutoSize(UDungreedConstValue::AutoSize, true);
	Renderer0->SetOrder(ERenderOrder::DungeonEat);
	Renderer0->SetSprite("DungeonEat_sheet.png", 8);

	Renderer1->CreateAnimation("EatEnd", "DungeonEat_sheet.png", 0.1f, false, 9, 27);
	Renderer1->SetAutoSize(UDungreedConstValue::AutoSize, true);
	Renderer1->SetOrder(ERenderOrder::DungeonEat);

	Collision->SetScale(ColScale);
	Collision->SetPosition({ 0,-100,0 });
}

void ADungeonEat::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);



	Collision->CollisionEnter(ECollisionOrder::Player, [=](std::shared_ptr<UCollision> _Collision)
		{
			APlayer::MainPlayer->InputOff();
			APlayer::MainPlayer->State.ChangeState("PlayerIdle");
			Renderer0->ChangeAnimation("EatStart");
			DelayCallBack(3.0f, [=]() {
				GEngine->ChangeLevel("BossStageLevel");
				APlayer::MainPlayer->InputOn();
				});
		}
	);

	Collision->CollisionStay(ECollisionOrder::Player, [=](std::shared_ptr<UCollision> _Collision)
		{
			if (Renderer0->IsCurAnimationEnd())
			{
				Renderer0->SetActive(false);
				APlayer::MainPlayer->SetActive(false);
				Renderer1->ChangeAnimation("EatEnd");
			}
		}
	);

	Collision->CollisionExit(ECollisionOrder::Player, [=](std::shared_ptr<UCollision> _Collision)
		{
		}
	);
}

