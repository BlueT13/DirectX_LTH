#include "PreCompile.h"
#include "DungreedCore.h"
#include "PlayGameMode.h"
#include "TitleGameMode.h"
#include "TileMapLevel.h"
#include "CreateMapMode.h"
#include <EngineCore/EngineSprite.h>

#include <EngineCore/EngineEditorGUI.h>
#include "ContentsGUI.h"
#include "MapEditorGUI.h"

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

		UEngineSprite::CreateCutting("Tiles.png", 18, 6);
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

	{
		UEngineEditorGUI::CreateEditorWindow<ContentsGUI>("Contents");
		UEngineEditorGUI::CreateEditorWindow<MapEditorGUI>("MapEditor");
	}

	GEngine->CreateLevel<ATitleGameMode>("TitleLevel");
	GEngine->CreateLevel<APlayGameMode>("PlayLevel");
	GEngine->CreateLevel<ATileMapLevel>("TileLevel");
	GEngine->CreateLevel<ACreateMapMode>("CreateMapLevel");
	
	GEngine->ChangeLevel("PlayLevel");
}