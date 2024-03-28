#include "PreCompile.h"
#include "EngineCore.h"
#include <EngineBase/EngineFile.h>
#include <EngineBase/EngineDirectory.h>
#include <EnginePlatform/EngineSound.h>
#include <EngineCore/EngineTexture.h>
#include "Level.h"

UEngineCore::UEngineCore() 
{
}

UEngineCore::~UEngineCore() 
{
	// 엔진이 종료할때 기존 엔진 옵션을 세이브 하고 한다.
	UEngineDirectory Dir;
	Dir.MoveToSearchChild("Config");
	UEngineFile File = Dir.GetPathFromFile("EngineOption.EData");
	UEngineSerializer Ser;
	EngineOption.Serialize(Ser);
	File.Open(EIOOpenMode::Write, EIODataType::Text);
	File.Save(Ser);
}

UEngineCore* GEngine = nullptr;

void UEngineCore::EngineStart(HINSTANCE _Inst)
{
	// 릭체크
	LeakCheck;
	GEngine = this;

	EngineOptionInit();

	EngineWindow.Open(EngineOption.WindowTitle);
	// 디바이스 초기화전에 크기가 다정해지면 해상도가 이미 결정 된거에요.
	// EngineOption.WindowScale 해상도
	// 해상도는 윈도우 크기와 관련이 없습니다.
	EngineWindow.SetWindowScale(EngineOption.WindowScale);
	EngineDevice.Initialize(EngineWindow, EngineOption.ClearColor);


	{
		UserCorePtr->Initialize();
		MainTimer.TimeCheckStart();
	}

	UEngineWindow::WindowMessageLoop(
		std::bind(&UEngineCore::EngineFrameUpdate, this),
		std::bind(&UEngineCore::EngineEnd, this)
	);
}

void UEngineCore::EngineOptionInit()
{
	UEngineDirectory Dir;
	Dir.MoveToSearchChild("Config");

	if (false == Dir.IsFile("EngineOption.EData"))
	{
		UEngineFile File = Dir.GetPathFromFile("EngineOption.EData");
		UEngineSerializer Ser;
		EngineOption.Serialize(Ser);

		File.Open(EIOOpenMode::Write, EIODataType::Text);
		File.Save(Ser);
	}

	{
		UEngineFile File = Dir.GetPathFromFile("EngineOption.EData");
		UEngineSerializer Ser;
		File = Dir.GetPathFromFile("EngineOption.EData");
		File.Open(EIOOpenMode::Read, EIODataType::Text);
		File.Load(Ser);
		EngineOption.DeSerialize(Ser);
	}

}

void UEngineCore::EngineEnd()
{
	// 어차피 자동으로 지워지는 리소스들을 왜 굳이 여기서 클리어를 직접 해주지?
	// 엔진이 종료되는 시점에 텍스처를 모두다 삭제한다.
	UEngineSound::ResourcesRelease();
	UEngineTexture::ResourcesRelease();
}

void UEngineCore::EngineFrameUpdate()
{
	float DeltaTime = MainTimer.TimeCheck();
	UEngineInput::KeyCheckTick(DeltaTime);

	if (nullptr != NextLevel)
	{
		CurLevel = NextLevel;
		NextLevel = nullptr;
	}

	CurLevel->Tick(DeltaTime);

	// 화면 지우고
	EngineDevice.RenderStart();
	// 게임에 요소들을 그리고

	// CurLevel->Render();

	// 억지로 그냥 그려본다.

	// 출력한다
	EngineDevice.RenderEnd();
}

std::shared_ptr<ULevel> UEngineCore::NewLevelCreate(std::string& _Name, std::shared_ptr<AActor> _GameMode)
{
	std::shared_ptr<ULevel> Level = std::make_shared<ULevel>();
	Level->PushActor(_GameMode);
	Level->BeginPlay();
	Levels[_Name] = Level;
	return Level;
}