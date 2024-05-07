#include "PreCompile.h"
#include "AfterImage.h"

AAfterImage::AAfterImage()
{
	DefaultComponent = CreateDefaultSubObject<UDefaultSceneComponent>("DefaultComponent");
	SetRoot(DefaultComponent);

	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(DefaultComponent);
}

AAfterImage::~AAfterImage()
{
}

void AAfterImage::BeginPlay()
{
	Super::BeginPlay();

	Renderer->SetSprite("AfterImage.png");
	Renderer->SetAutoSize(UDungreedConstValue::AutoSize, true);
	Renderer->SetOrder(ERenderOrder::AfterImage);

	//Renderer->SetPlusColor({10000000.0f, 10000000.0f, 10000000.0f, 0.0f});
	//Renderer->SetMulColor({1.0f / 10000000.0f, 1.0f / 10000000.0f, 1.0f / 10000000.0f, 0.5f});
	Renderer->SetMulColor({ 1.0f,1.0f,1.0f,0.5f });

	DelayCallBack(0.2f, [=]() {
		Destroy();
		});
}

void AAfterImage::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

