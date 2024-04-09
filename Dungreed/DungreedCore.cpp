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

		std::vector<UEngineDirectory> Directorys = Dir.GetAllDirectory(true);
		for (size_t i = 0; i < Directorys.size(); i++)
		{
			std::string Name = Directorys[i].GetFolderName();
			UEngineSprite::LoadFolder(Directorys[i].GetFullPath());
		}

		//std::vector<UEngineFile> Files = Dir.GetAllFile({ ".png" }, true);
		//for (UEngineFile& File : Files)
		//{
		//	UEngineSprite::Load(File.GetFullPath());
		//}
	}

	//{
	//	UEngineDirectory Dir;
	//	Dir.MoveToSearchChild("Resources");
	//	Dir.Move("Sound");
	//	std::vector<UEngineFile> Files = Dir.GetAllFile({ ".wav" });
	//	for (UEngineFile& File : Files)
	//	{
	//		//File.Open(EIOOpenMode::Read, EIODataType::Binary);

	//		//char Arr[100];
	//		//File.Read(Arr, 100);

	//		UEngineSound::Load(File.GetFullPath());
	//	}
	//	
	//	// UEngineSound::SoundPlay("~~~.wav");
	//}

	GEngine->CreateLevel<ATitleGameMode>("TitleLevel");
	GEngine->CreateLevel<APlayGameMode>("PlayLevel");
	GEngine->ChangeLevel("TitleLevel");
}