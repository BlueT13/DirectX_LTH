#include "PreCompile.h"
#include "TitleImage.h"

ATitleImage::ATitleImage()
{
	DefaultComponent = CreateDefaultSubObject<UDefaultSceneComponent>("DefaultComponent");
	SetRoot(DefaultComponent);


	BackgroundRenderer = CreateDefaultSubObject<USpriteRenderer>("BackgroundRenderer");
	BackgroundRenderer->SetupAttachment(DefaultComponent);

	TitleImageRenderer = CreateDefaultSubObject<USpriteRenderer>("TitleImageRenderer");
	TitleImageRenderer->SetupAttachment(DefaultComponent);
}

ATitleImage::~ATitleImage()
{
}


void ATitleImage::BeginPlay()
{
	Super::BeginPlay();

	//DelayCallBack(1.0f, std::bind(&ATitleImage::RendererOff, this));

	BackgroundRenderer->SetSprite("Sky_Day.png");
	BackgroundRenderer->SetAutoSize(UDungreedConstValue::AutoSize, true);
	BackgroundRenderer->SetOrder(ERenderOrder::Background_0);

	TitleImageRenderer->SetSprite("TitleImage.png");
	TitleImageRenderer->SetAutoSize(UDungreedConstValue::AutoSize, true);
	TitleImageRenderer->SetOrder(ERenderOrder::Background_1);
	TitleImageRenderer->SetPosition({ 0,160,0 });
}

void ATitleImage::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

//void ATitleImage::RendererOn()
//{
//	Renderer->SetActive(true);
//	DelayCallBack(0.2f, std::bind(&ATitleImage::RendererOff, this));
//}
//
//void ATitleImage::RendererOff()
//{
//	Renderer->SetActive(false);
//	DelayCallBack(0.2f, std::bind(&ATitleImage::RendererOn, this));
//}