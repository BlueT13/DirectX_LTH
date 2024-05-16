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
		MsgBoxAssert("�����Ͷ����� ������ �����߽��ϴ�.");
		return;
	} 
#endif
}

void UEngineDepthStencil::Setting()
{
#ifdef _DEBUG
	if (nullptr == State)
	{
		MsgBoxAssert("��������� ���� �����Ͷ������� �����Ϸ��� �߽��ϴ�" + GetName());
	}
#endif

	GEngine->GetDirectXContext()->OMSetDepthStencilState(State, 0);
}