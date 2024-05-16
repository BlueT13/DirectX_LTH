#include "PreCompile.h"
#include "TitleGameMode.h"
#include <EngineCore/Camera.h>

ATitleGameMode::ATitleGameMode()
{
}

ATitleGameMode::~ATitleGameMode()
{
}

void ATitleGameMode::BeginPlay()
{
	Super::BeginPlay();

	TitleImage = GetWorld()->SpawnActor<ATitleImage>("TitleImage", EUpdateOrder::Map);
	TitleImage->SetActorLocation({ 0.0f, 0.0f, 100.0f });

	Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation(FVector(0.0f, 0.0f, -100.0f));

	StartImage = CreateWidget<UImage>(GetWorld(), "StartImage");
	StartImage->AddToViewPort(0);
	StartImage->SetSprite("Start_Off.png");
	StartImage->SetAutoSize(1.0f, true);
	StartImage->SetPosition({ 0, -100, 0 });

	ExitImage = CreateWidget<UImage>(GetWorld(), "ExitImage");
	ExitImage->AddToViewPort(0);
	ExitImage->SetSprite("Exit_Off.png");
	ExitImage->SetAutoSize(1.0f, true);
	ExitImage->SetPosition({ 0, -200, 0 });
}

void ATitleGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	StartImage->SetHover([=]()
		{
			StartImage->SetSprite("Start_On.png");
		});
	StartImage->SetUnHover([=]()
		{
			StartImage->SetSprite("Start_Off.png");
		});
	StartImage->SetDown([=]()
		{
			GEngine->ChangeLevel("PlayLevel");
		});

	ExitImage->SetHover([=]()
		{
			ExitImage->SetSprite("Exit_On.png");
		});
	ExitImage->SetUnHover([=]()
		{
			ExitImage->SetSprite("Exit_Off.png");
		});
	ExitImage->SetDown([=]()
		{
			GEngine->EngineWindow.Off();
		});


	if (true == UEngineInput::IsDown('P'))
	{
		GEngine->ChangeLevel("PlayLevel");
	}
	if (true == UEngineInput::IsDown(VK_ESCAPE))
	{
		GEngine->EngineWindow.Off();
	}
}

void ATitleGameMode::LevelEnd(ULevel* _NextLevel)
{
	Super::LevelEnd(_NextLevel);
}

void ATitleGameMode::LevelStart(ULevel* _PrevLevel)
{
	Super::LevelStart(_PrevLevel);
}