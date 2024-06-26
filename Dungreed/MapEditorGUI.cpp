#include "PreCompile.h"
#include "MapEditorGUI.h"
#include "TileMapMode.h"
#include <EngineCore/TileRenderer.h>
#include "TileMap.h"
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/Camera.h>

MapEditorGUI::MapEditorGUI()
{
}

MapEditorGUI::~MapEditorGUI()
{
}

void MapEditorGUI::Init()
{
	Dir.MoveToSearchChild("Resources");
	Dir.Move("Save");
}

void MapEditorGUI::Tick(ULevel* _Level, float _Delta)
{
	_Level->GetMainCamera();

	std::string LevelName = _Level->GetName();

	if ("CreateMapLevel" == _Level->GetName())
	{
		On();

		float Speed = 500.0f;
		if (true == UEngineInput::IsPress('A'))
		{
			_Level->GetMainCamera()->AddActorLocation(float4::Left * _Delta * Speed);
		}

		if (true == UEngineInput::IsPress('D'))
		{
			_Level->GetMainCamera()->AddActorLocation(float4::Right * _Delta * Speed);
		}

		if (true == UEngineInput::IsPress('W'))
		{
			_Level->GetMainCamera()->AddActorLocation(float4::Up * _Delta * Speed);
		}

		if (true == UEngineInput::IsPress('S'))
		{
			_Level->GetMainCamera()->AddActorLocation(float4::Down * _Delta * Speed);
		}
	}
	else
	{
		Off();
	}

	std::shared_ptr<AGameMode> Mode = _Level->GetGameMode();

	ATileMapMode* Ptr = dynamic_cast<ATileMapMode*>(Mode.get());

	if (nullptr == Ptr)
	{
		return;
	}

	UTileRenderer* TileRenderer = Ptr->TileMap->TileRenderer;

	if (true == UEngineInput::IsPress(VK_LBUTTON))
	{
		float4 MousePos = GEngine->EngineWindow.GetScreenMousePos();
		MousePosWorld = _Level->GetMainCamera()->ScreenPosToWorldPos(MousePos);

		TileRenderer->SetTile(MousePosWorld, SelectSpriteIndex);
	}


}

void MapEditorGUI::OnGui(ULevel* _Level, float _Delta)
{

	float4 MousePos = GEngine->EngineWindow.GetScreenMousePos();
	MousePosWorld = _Level->GetMainCamera()->ScreenPosToWorldPos(MousePos);

	std::shared_ptr<AGameMode> Mode = _Level->GetGameMode();

	ATileMapMode* Ptr = dynamic_cast<ATileMapMode*>(Mode.get());

	if (nullptr == Ptr)
	{
		return;
	}

	UTileRenderer* TileRenderer = Ptr->TileMap->TileRenderer;


	ImGui::InputInt2("TileSize", TileCount);

	if (true == ImGui::Button("Create"))
	{
		TileRenderer->CreateTileMap("Tiles.png", { TileSize, TileSize }, TileCount[0], TileCount[1], 0);
		_Level->GetMainCamera()->SetActorLocation({ TileSize * TileCount[0] / 2, TileSize * TileCount[1] / 2 });
	}

	if (true == ImGui::Button("Save"))
	{
		UEngineSerializer Ser;
		TilesData = TileRenderer->GetTileMapData();
		Ser << TilesData;

		UEngineFile File = Dir.GetPathFromFile("SaveData.Data");
		File.Open(EIOOpenMode::Write, EIODataType::Binary);
		File.Save(Ser);
	}

	if (true == ImGui::Button("Load"))
	{
		UEngineSerializer Ser;

		UEngineFile File = Dir.GetPathFromFile("SaveData.Data");
		File.Open(EIOOpenMode::Read, EIODataType::Binary);
		File.Load(Ser);

		Ser >> TilesData;
		TileRenderer->CreateTileMap("Tiles.png", { TileSize, TileSize }, TilesData[0].size(), TilesData.size(), 0);

		for (size_t y = 0; y < TilesData.size(); y++)
		{
			for (size_t x = 0; x < TilesData[y].size(); x++)
			{
				TileRenderer->SetTile(x, y, TilesData[y][x]);
			}
		}
	}

	ImGui::Text(("WorldMouse : " + MousePosWorld.ToString()).c_str());
	float4 Index = TileRenderer->ConvertTileIndex(MousePosWorld);
	ImGui::Text(("TileIndexPos : " + Index.ToString()).c_str());
	ImGui::Text(std::format("Index : {} {}", Index.iX(), Index.iY()).c_str());


	std::shared_ptr<UEngineSprite> Sprite = UEngineSprite::FindRes("Tiles.png");


	// 다이렉트 디바이스랑
	// 다이렉트 컨텍스
	// imgui는 내부에서 자신의 쉐이더를 사용합니다.

	// imgui에서 사용하는 쉐이더에 내 텍스처가 들어간다.
	// ImVec2

	// IMgui는 무조건 char* Event체크를 합니다;
	if (SelectSpriteIndex != -1)
	{
		FSpriteInfo Info = Sprite->GetSpriteInfo(SelectSpriteIndex);

		ImVec2 UV0 = { Info.CuttingPosition.X, Info.CuttingPosition.Y };
		ImVec2 UV1 = { Info.CuttingSize.X, Info.CuttingSize.Y };

		UV1.x = UV1.x + UV0.x;
		UV1.y = UV1.y + UV0.y;

		ImGui::ImageButton("Select", Info.Texture->GetSRV(), { 100, 100 }, UV0, UV1);
	}
	else
	{
		ImGui::ImageButton("Select", nullptr, { 100, 100 });
	}

	ImGui::BeginChild("TileSelect", { 0, 0 }, false, ImGuiWindowFlags_HorizontalScrollbar);


	for (int i = 0; i < Sprite->GetInfoSize(); i++)
	{
		FSpriteInfo Info = Sprite->GetSpriteInfo(i);

		ImVec2 UV0 = { Info.CuttingPosition.X, Info.CuttingPosition.Y };
		ImVec2 UV1 = { Info.CuttingSize.X, Info.CuttingSize.Y };

		UV1.x = UV1.x + UV0.x;
		UV1.y = UV1.y + UV0.y;

		std::string Text = std::to_string(i);

		// 줄바꿈을 자동으로 해준다.
		if (true == ImGui::ImageButton(Text.c_str(), Info.Texture->GetSRV(), { 64, 64 }, UV0, UV1))
		{
			SelectSpriteIndex = i;
		}

		if ((i + 1) % 18)
		{
			ImGui::SameLine();
		}
	}

	// Index 내가 찍어야할 스프라이트

	// 

	//ImGui::TextUnformatted("child_2");
	//ImGui::GetWindowDrawList()->AddLine({ 0, 0 }, { 500, 500 }, 0xFFFFFFFF);
	//ImGui::SetCursorPos({ 1500, 1500 });
	//ImGui::TextUnformatted("hello");
	ImGui::EndChild();

}