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
			// CuttingTest.png texture�ε� ������ �ε尡 �ư�
			// ��������Ʈ�ε� 1��¥���� �ε尡 �� ��Ȳ�̾�.
			UEngineSprite::Load(File.GetFullPath());
		}

		// �ε������� �̷��� �Ѵٰ� Ĩ�ô�.
		std::vector<UEngineDirectory> Directorys = Dir.GetAllDirectory();
		for (size_t i = 0; i < Directorys.size(); i++)
		{
			std::string Name = Directorys[i].GetFolderName();
			UEngineSprite::LoadFolder(Directorys[i].GetFullPath());
		}

		// Ư�� ��������Ʈ�� 
		// Ư�� �ؽ�ó�� ã�Ƽ�
		// ���� ��������Ʈ�� �������� �ʴ´ٸ�
		// �̰� ����ϴ� ���� ������ �ڸ���.
		// �̹� �� �̸��� ���� ��������Ʈ�� �����Ѵ�.
		// �׷��� ������ ��������Ʈ �����ʹ� ����������
		// �ڸ� ��������Ʈ ������ �����Ѵ�.
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