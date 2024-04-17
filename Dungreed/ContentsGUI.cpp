#include "PreCompile.h"
#include "ContentsGUI.h"

ContentsGUI::ContentsGUI() 
{
}

ContentsGUI::~ContentsGUI() 
{
}

void ContentsGUI::Init() 
{
}

void ContentsGUI::OnGui(ULevel* _Level, float _Delta)
{
	if (true == ImGui::Button("TitleLevel"))
	{
		GEngine->ChangeLevel("TitleLevel");
	}

	if (true == ImGui::Button("PlayLevel"))
	{
		GEngine->ChangeLevel("PlayLevel");
	}

	if (true == ImGui::Button("CreateMapLevel"))
	{
		GEngine->ChangeLevel("CreateMapLevel");
	}
}