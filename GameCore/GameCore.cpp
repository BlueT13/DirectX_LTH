#include "PreCompile.h"
#include "GameCore.h"
#include "PlayGameMode.h"

UGameCore::UGameCore()
{
}

UGameCore::~UGameCore()
{
}

void UGameCore::Initialize()
{
	GEngine->CreateLevel<APlayGameMode>("PlayLevel");
	GEngine->ChangeLevel("PlayLevel");

	//{
	//	UEngineDirectory Dir;
	//	Dir.MoveToSearchChild("ContentsResources");
	//	Dir.Move("Sound");
	//	std::list<UEngineFile> Files = Dir.AllFile({ ".wav" });
	//	for (UEngineFile& File : Files)
	//	{
	//		UEngineSound::Load(File.GetFullPath());
	//	}
	//	UEngineSound::SoundPlay("anipang_ingame_wav.wav");
	//}
}