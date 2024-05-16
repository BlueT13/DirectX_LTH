#include "PreCompile.h"
#include "EngineDepthStencil.h"
#include "EngineCore.h"

UEngineDepthStencil::UEngineDepthStencil() 
{
}

UEngineDepthStencil::~UEngineDepthStencil() 
{
	if (nullptr != State)
	{
		State->Release();
	}
}

void UEngineDepthStencil::ResCreate(const D3D11_DEPTH_STENCIL_DESC& _Info)
{
	HRESULT Result =  GEngine->GetDirectXDevice()->CreateDepthStencilState(&_Info, &State);
#ifdef _DEBUG
	if (S_OK != Result)
	{
		MsgBoxAssert("레스터라이저 생성에 실패했습니다.");
		return;
	} 
#endif
}

void UEngineDepthStencil::Setting()
{
#ifdef _DEBUG
	if (nullptr == State)
	{
		MsgBoxAssert("만들어지지 않은 레스터라이저를 세팅하려고 했습니다" + GetName());
	}
#endif

	GEngine->GetDirectXContext()->OMSetDepthStencilState(State, 0);
}