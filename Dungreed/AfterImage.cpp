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

	Renderer->SetSprite("CharIdle0.png");
	Renderer->SetAutoSize(UDungreedConstValue::AutoSize, true);
	Renderer->SetOrder(ERenderOrder::AfterImage);
	Renderer->SetMulColor({ 10.0f, 10.0f, 10.0f, 0.5f });
}

void AAfterImage::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

