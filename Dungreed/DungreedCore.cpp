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
			UEngineSprite::Load(File.GetFullPath());
		}

		std::vector<UEngineDirectory> Directorys = Dir.GetAllDirectory();
		for (size_t i = 0; i < Directorys.size(); i++)
		{
			std::string Name = Directorys[i].GetFolderName();
			UEngineSprite::LoadFolder(Directorys[i].GetFullPath());
		}

		//// 특정 스프라이트나 
		//// 특정 텍스처를 찾아서
		//// 만약 스프라이트가 존재하지 않는다면
		//// 이걸 사용하는 순간 만들어내고 자른다.
		//// 이미 이 이름을 가진 스프라이트가 존재한다면
		//// 기존의 스프라이트 데이터는 날려버리고
		//// 자른 스프라이트 데이터로 변경한다.
		//UEngineSprite::CreateCutting("CuttingTest.png", 4, 3);
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