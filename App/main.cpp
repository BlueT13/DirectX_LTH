#include <Windows.h>
#include <EngineCore/EngineCore.h>
#include <GameCore/GameCore.h>

#pragma comment (lib, "EngineBase.lib")
#pragma comment (lib, "EnginePlatform.lib")
#pragma comment (lib, "EngineCore.lib")
#pragma comment (lib, "GameCore.lib")

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UEngineCore::Start<UGameCore>(hInstance);
}