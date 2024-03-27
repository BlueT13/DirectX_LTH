#include "PreCompile.h"
#include "EngineGraphicDevice.h"

// 다이렉트 라이브러리를 사용하기 위해서


UEngineGraphicDevice::UEngineGraphicDevice() 
{
}

UEngineGraphicDevice::~UEngineGraphicDevice() 
{
	if (nullptr == Context)
	{
		Context->Release();
	}

	if (nullptr == Device)
	{
		Device->Release();
	}
}

IDXGIAdapter* UEngineGraphicDevice::GetHighPerFormanceAdapter()
{
	// 그래픽카드가 2개면

	IDXGIFactory* Factory = nullptr;
	IDXGIAdapter* Adapter = nullptr;

	// IDXGIFactory* Factory는 다이렉트x 라이브러리를 만드는 용도의 
	// 인터페이스입니다
	// Adapter를 만들어 내려면  Factory 필요하다.
	// CreateDXGIFactory()
	
	// 문법 이해 안되면 물어보세요
	HRESULT HR = CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&Factory));

	if (nullptr == Factory)
	{
		MsgBoxAssert("그래픽카드에서 팩토리 인터페이스를 생성하지 못했습니다");
		return nullptr;
	}

	size_t VideoMemory = 0;
	// 그래픽카드 램이 큰애가
	// 가장 성능이 좋은 그래픽카드라고 생각하겠다

	for (int Index = 0;; Index++)
	{
		IDXGIAdapter* CurAdapter = nullptr;

		Factory->EnumAdapters(Index, &CurAdapter);

		if (nullptr == CurAdapter)
		{
			break;
		}

		DXGI_ADAPTER_DESC Desc;
		CurAdapter->GetDesc(&Desc);

		if (VideoMemory <= Desc.DedicatedVideoMemory)
		{
			VideoMemory = Desc.DedicatedVideoMemory;

			if (nullptr != Adapter)
			{
				// 기존에 만약 어뎁터가 있다면
				// 그 어뎁터는 날려버리고
				Adapter->Release();
			}

			Adapter = CurAdapter;
			continue;
		}

		CurAdapter->Release();
	}

	Factory->Release();
	return Adapter;
}

void UEngineGraphicDevice::Initialize(const UEngineWindow& _Window)
{
	if (nullptr == _Window.GetHWND())
	{
		MsgBoxAssert("Open 되지 않은 윈도우로 그래픽카드 장치를 초기화하려고 했습니다.");
		return;
	}

	int iFlag = 0;

#ifdef _DEBUG
	// 디버그 모드일때만
	//  D3D11_CREATE_DEVICE_SINGLETHREADED = 0x1,
	//	D3D11_CREATE_DEVICE_DEBUG = 0x2,
	//	D3D11_CREATE_DEVICE_SWITCH_TO_REF = 0x4,
	//	D3D11_CREATE_DEVICE_PREVENT_INTERNAL_THREADING_OPTIMIZATIONS = 0x8,
	//	D3D11_CREATE_DEVICE_BGRA_SUPPORT = 0x20,
	//	D3D11_CREATE_DEVICE_DEBUGGABLE = 0x40,
	//	D3D11_CREATE_DEVICE_PREVENT_ALTERING_LAYER_SETTINGS_FROM_REGISTRY = 0x80,
	//	D3D11_CREATE_DEVICE_DISABLE_GPU_TIMEOUT = 0x100,
	//	D3D11_CREATE_DEVICE_VIDEO_SUPPORT = 0x800


	iFlag = D3D11_CREATE_DEVICE_DEBUG;
#endif

	// 내 그래픽카드가 다이렉트 x를 몇버전까지 지원할수 있는지 알아내기 위한 변수
	D3D_FEATURE_LEVEL Level = D3D_FEATURE_LEVEL_11_0;

	// 그래픽카드를 대표하는 핸들
	// 최대 성능 그래픽카드를 찾기 위한 함수
	IDXGIAdapter* Adapter = GetHighPerFormanceAdapter();

	if (nullptr == Adapter)
	{
		MsgBoxAssert("그래픽카드가 존재하지 않는 컴퓨터 입니다");
		return;
	}

	// 그래픽카드를 찾았으니
	// Adapter 그래픽카드에 명령을 내릴수 있느 그래픽카드에 명령을 내릴수 있는 디바이스와 컨텍스트를 만들겁니다.

	// D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_UNKNOWN  // 니가 알아서 해줘
	// D3D_DRIVER_TYPE_HARDWARE	= ( D3D_DRIVER_TYPE_UNKNOWN + 1 ) , 그래픽카드로
	// D3D_DRIVER_TYPE_REFERENCE = (D3D_DRIVER_TYPE_HARDWARE + 1), // 특화된 뭘할께
	// D3D_DRIVER_TYPE_NULL = (D3D_DRIVER_TYPE_REFERENCE + 1),
	// D3D_DRIVER_TYPE_SOFTWARE = (D3D_DRIVER_TYPE_NULL + 1), Cpu로 연산할께.
	// D3D_DRIVER_TYPE_WARP = (D3D_DRIVER_TYPE_SOFTWARE + 1)

	// 함수가 용도가 2개인거야

	HRESULT Result = D3D11CreateDevice(
		Adapter, // nullptr; 다이렉트 x가 
		D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_UNKNOWN, // -0 
		nullptr,
		iFlag,
		nullptr, // 팩처레벨 강제지정인데
		0, // 그중에서 내가 선택가능한 팩처레벨을 리턴해줘요 
		D3D11_SDK_VERSION, // 
		&Device,
		&Level, // 내가 선택한 팩처레벨
		&Context
	);

	if (nullptr == Context)
	{
		MsgBoxAssert("그래픽카드가 랜더링 제어 권한 컨텍스트를 생성하는데 실패했습니다.");
		return;
	}

	if (nullptr == Device)
	{
		MsgBoxAssert("그래픽카드가 메모리제어 권한 디바이스를 생성하는데 실패했습니다.");
		return;
	}
	
	// 나 포인터 썼다 무조건 null검사
	// 생각자체를 하지마 그냥 하는거니까.
	if (nullptr != Adapter)
	{
		Adapter->Release();
	}

	if (S_OK != Result)
	{
		MsgBoxAssert("디바이스 생성에 실패했습니다.");
		// DWORD Result = GetLastError(); // 이 에러에 대해서 자세하게 알수 있다.
		// 지금은 무시
		return;
	}

	if (D3D_FEATURE_LEVEL_11_0 != Level)
	{
		MsgBoxAssert("다이렉트 11버전을 사용할수 없는 그래픽카드 입니다.");
		return;
	}

	// CPU에서 쓰는 멀티쓰레드로도 안전하게 동작하게 하겠다.
	Result = CoInitializeEx(nullptr, COINIT_MULTITHREADED);

	if (S_OK != Result)
	{
		MsgBoxAssert("멀티쓰레드 옵션을 사용할 수가 없습니다.");
		return;
	}

	WindowPtr = &_Window;

}