#include "PreCompile.h"
#include "Background.h"
#include "Player.h"

ABackground::ABackground()
{
	DefaultComponent = CreateDefaultSubObject<UDefaultSceneComponent>("DefaultComponent");
	SetRoot(DefaultComponent);

	Renderer0 = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer0->SetupAttachment(DefaultComponent);

	Renderer1 = CreateDefaultSubObject<USpriteRenderer>("Renderer1");
	Renderer1->SetupAttachment(DefaultComponent);

	Renderer2 = CreateDefaultSubObject<USpriteRenderer>("Renderer2");
	Renderer2->SetupAttachment(DefaultComponent);
}

ABackground::~ABackground()
{
}

void ABackground::BeginPlay()
{
	Super::BeginPlay();

	Renderer0->SetSprite("Sky_Day.png");
	Renderer0->SetOrder(ERenderOrder::Background_0);
	Renderer0->SetAutoSize(UDungreedConstValue::AutoSize, true);

	Renderer1->SetSprite("TownBG_Day.png");
	Renderer1->SetOrder(ERenderOrder::Background_1);
	Renderer1->SetAutoSize(UDungreedConstValue::AutoSize, true);

	Renderer2->SetSprite("TownLayer_Day.png");
	Renderer2->SetOrder(ERenderOrder::Background_2);
	Renderer2->SetAutoSize(UDungreedConstValue::AutoSize, true);
}

void ABackground::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	CameraPos = GetWorld()->GetMainCamera()->GetActorLocation();
	CameraPos.Z = 0.0f;


	Renderer0->SetPosition(CameraPos);
	Renderer1->SetPosition({ CameraPos.X, 568.0f, 0.0f });
	Renderer2->SetPosition({ CameraPos.X, 300.0f, 0.0f });

	//UVTest.X += _DeltaTime;
	//Renderer1->SetVertexUVPlus(UVTest);
}

