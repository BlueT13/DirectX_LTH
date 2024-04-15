#include "PreCompile.h"
#include "TitleImage.h"

ATitleImage::ATitleImage()
{
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	SetRoot(Renderer);
}

ATitleImage::~ATitleImage()
{
}


void ATitleImage::BeginPlay()
{
	Super::BeginPlay();

	//DelayCallBack(1.0f, std::bind(&ATitleImage::RendererOff, this));

	Renderer->SetSprite("Title");
	Renderer->SetAutoSize(4.0f, true);
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