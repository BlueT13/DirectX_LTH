#include "PreCompile.h"
#include "DungreedCore.h"
#include "CreateMapMode.h"
#include "TileMapMode.h"
#include "TitleGameMode.h"
#include "PlayGameMode.h"
#include "BossStageMode.h"

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
		Dir.Move("Image");

		std::vector<UEngineDirectory> Directorys = Dir.GetAllDirectory(true);
		for (size_t i = 0; i < Directorys.size(); i++)
		{
			std::string Name = Directorys[i].GetFolderName();
			UEngineSprite::LoadFolder(Directorys[i].GetFullPath());
		}

		std::vector<UEngineFile> Files = Dir.GetAllFile({ ".png" }, true);
		for (UEngineFile& File : Files)
		{
			UEngineSprite::Load(File.GetFullPath());
		}

		UEngineSprite::CreateCutting("Tiles.png", 18, 6);
		UEngineSprite::CreateCutting("DungeonEat_sheet.png", 28, 1);
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

	UEngineEditorGUI::CreateEditorWindow<ContentsGUI>("Contents");
	UEngineEditorGUI::CreateEditorWindow<MapEditorGUI>("MapEditor");

	GEngine->CreateLevel<ACreateMapMode>("CreateMapLevel");
	GEngine->CreateLevel<ATileMapMode>("TileLevel");

	GEngine->CreateLevel<ATitleGameMode>("TitleLevel");
	GEngine->CreateLevel<APlayGameMode>("PlayLevel");
	GEngine->CreateLevel<ABossStageMode>("BossStageLevel");

	GEngine->ChangeLevel("TitleLevel");
}