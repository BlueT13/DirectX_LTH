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

	std::shared_ptr<UCamera> Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation(FVector(0.0f, 0.0f, -100.0f));

	TitleImage = GetWorld()->SpawnActor<ATitleImage>("TitleImage");
	TitleImage->SetActorLocation({ 0.0f, 0.0f, 100.0f });
}

void ATitleGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

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