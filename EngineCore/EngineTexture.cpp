#include "PreCompile.h"
#include "EngineTexture.h"
#include "EngineCore.h"

UEngineTexture::UEngineTexture() 
{
}

UEngineTexture::~UEngineTexture() 
{
	if (nullptr != RTV)
	{
		RTV->Release();
	}

	if (nullptr != Texture2D)
	{
		Texture2D->Release();
	}
}

void UEngineTexture::CreateRes(ID3D11Texture2D* _Texture)
{
	Texture2D = _Texture;

	Texture2D->GetDesc(&Desc);

	CreateRenderTargetView();
}

void UEngineTexture::CreateRenderTargetView()
{
	if (nullptr != RTV)
	{
		return;
	}

	if (nullptr == Texture2D)
	{
		MsgBoxAssert("만들어지지 않은 텍스처로 랜더타겟뷰를 생성하려고 했습니다.");
		return;
	}

	// 이제 텍스처 메모리에서 이미지를 수정할수 있는 권한을 만든다
	// 다이렉트에서 뭔가를 하려면 근본적으로 2가지 관련되어 있습니다.
	// 메모리 => Device
	// 랜더링 => Context
	HRESULT Result = GEngine->GetDirectXDevice()->CreateRenderTargetView(Texture2D, nullptr, &RTV);

	if (S_OK != Result)
	{
		MsgBoxAssert("랜더타겟 뷰 생성에 실패했습니다.");
		return;
	}
}