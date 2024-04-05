#include "PreCompile.h"
#include "DungreedCore.h"
#include "PlayGameMode.h"
#include "TitleGameMode.h"
#include <EngineCore/EngineSprite.h>

UDungreedCore::UDungreedCore()
{
}

UDungreedCore::~UDungreedCore()
{
}

void UDungreedCore::Initialize()
{
	{
		UEngineDirectory Dir;
		Dir.MoveToSearchChild("Resources");
		Dir.Move("Image");
		std::vector<UEngineFile> Files = Dir.GetAllFile({ ".png" }, true);
		for (UEngineFile& File : Files)
		{
			// CuttingTest.png texture로도 한장이 로드가 됐고
			// 스프라이트로도 1장짜리로 로드가 된 상황이야.
			UEngineSprite::Load(File.GetFullPath());
		}

		// 로드폴더는 이렇게 한다고 칩시다.
		std::vector<UEngineDirectory> Directorys = Dir.GetAllDirectory();
		for (size_t i = 0; i < Directorys.size(); i++)
		{
			std::string Name = Directorys[i].GetFolderName();
			UEngineSprite::LoadFolder(Directorys[i].GetFullPath());
		}

		// 특정 스프라이트나 
		// 특정 텍스처를 찾아서
		// 만약 스프라이트가 존재하지 않는다면
		// 이걸 사용하는 순간 만들어내고 자른다.
		// 이미 이 이름을 가진 스프라이트가 존재한다.
		// 그러면 기존의 스프라이트 데이터는 날려버리고
		// 자른 스프라이트 데이터 변경한다.
		UEngineSprite::CreateCutting("CuttingTest.png", 4, 3);
	}


	{
		UEngineDirectory Dir;
		Dir.MoveToSearchChild("Resources");
		Dir.Move("Sound");
		std::vector<UEngineFile> Files = Dir.GetAllFile({ ".wav" });
		for (UEngineFile& File : Files)
		{
			//File.Open(EIOOpenMode::Read, EIODataType::Binary);

			//char Arr[100];
			//File.Read(Arr, 100);

			UEngineSound::Load(File.GetFullPath());
		}
		// UEngineSound::SoundPlay("anipang_ingame_wav.wav");
	}

	GEngine->CreateLevel<APlayGameMode>("PlayLevel");
	GEngine->CreateLevel<ATitleGameMode>("TitleLevel");
	GEngine->ChangeLevel("TitleLevel");


}