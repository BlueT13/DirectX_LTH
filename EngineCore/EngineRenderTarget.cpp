#include "PreCompile.h"
#include "EngineRenderTarget.h"
#include "EngineTexture.h"
#include "EngineCore.h"


URenderUnit UEngineRenderTarget::CopyUnit;

void UEngineRenderTarget::RenderTargetInit()
{
	UEngineRenderTarget::CopyUnit.SetMesh("FullRect");
	UEngineRenderTarget::CopyUnit.SetMaterial("TargetCopy");
}

UEngineRenderTarget::UEngineRenderTarget() 
{
}

UEngineRenderTarget::~UEngineRenderTarget() 
{
}

void UEngineRenderTarget::CreateTexture(DXGI_FORMAT _Format, float4 _Scale, float4 _ClearColor)
{
	D3D11_TEXTURE2D_DESC Desc = {0};

	// 3���� �ؽ�ó�� ����� �ִµ�.
	Desc.ArraySize = 1;
	Desc.Width = _Scale.iX();
	Desc.Height = _Scale.iY();
	Desc.Format = _Format;
	Desc.SampleDesc.Count = 1;
	Desc.SampleDesc.Quality = 0;
	Desc.MipLevels = 1;
	// �׷���ī�忡�� ����.
	Desc.Usage = D3D11_USAGE_DEFAULT;
	Desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_RENDER_TARGET | D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE;

	std::shared_ptr<UEngineTexture> Tex = UEngineTexture::Create(Desc);

	AddNewTexture(Tex, _ClearColor);
}

void UEngineRenderTarget::AddNewTexture(std::shared_ptr<UEngineTexture> _Texture, const float4& _Color)
{
	Textures.push_back(_Texture);
	RTVs.push_back(_Texture->GetRTV());
	ClearColors.push_back(_Color);
}

void UEngineRenderTarget::CreateDepthTexture(int _Index/* = 0*/)
{
	D3D11_TEXTURE2D_DESC Desc = { 0 };
	Desc.ArraySize = 1;

	Desc.Width = Textures[_Index]->GetScale().uiX();
	Desc.Height = Textures[_Index]->GetScale().uiY();

	// z�� �ϳ��� ����ϴ°�.
	// ���� 1����Ʈ�� ������ ���Ľ� ���̶�°����� ����Ѵ�.
	Desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;

	Desc.SampleDesc.Count = 1;
	Desc.SampleDesc.Quality = 0;

	Desc.MipLevels = 1;

	Desc.Usage = D3D11_USAGE_DEFAULT;
	Desc.CPUAccessFlags = 0;
	Desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_DEPTH_STENCIL;

	DepthTexture = UEngineTexture::Create(Desc);
}


void UEngineRenderTarget::Clear()
{
	// ���̷�Ʈ�� ���� 2��������
	
	// Device �޸�
	// contexts ������
	
	// ��� �׸��� Ŭ���� 

	for (size_t i = 0; i < RTVs.size(); i++)
	{
		GEngine->GetDirectXContext()->ClearRenderTargetView(RTVs[i], ClearColors[i].Arr1D);
	}

	if (nullptr != DepthTexture)
	{
		// 1.0f Ŭ���� �Ҷ� ���� ���̳�
		GEngine->GetDirectXContext()->ClearDepthStencilView(DepthTexture->GetDSV(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	}
}

void UEngineRenderTarget::Setting(bool IsDepth/* = false*/)
{
	ID3D11DepthStencilView* DSV = nullptr;

	if (true == IsDepth && nullptr != DepthTexture)
	{
		DSV = DepthTexture->GetDSV();
	}

	// ���̹��۴� ���߿�
	GEngine->GetDirectXContext()->OMSetRenderTargets(static_cast<UINT>(RTVs.size()), &RTVs[0], DSV);

}

void UEngineRenderTarget::Copy(std::shared_ptr<UEngineRenderTarget> _Other)
{
	Clear();
	Merge(_Other);
}

void UEngineRenderTarget::Merge(std::shared_ptr<UEngineRenderTarget> _Other, int _Index /*= 0*/)
{
	// ���� ����̴ϱ� 
	Setting();

	std::shared_ptr<UEngineTexture> CopyTarget = _Other->Textures[_Index];
	// ��û�߿��� 

	UEngineRenderTarget::CopyUnit.Resources->SettingTexture("Image", CopyTarget, "POINT");
	UEngineRenderTarget::CopyUnit.Render(0.0f);

}

void UEngineRenderTarget::Effect(float _DeltaTime)
{
	for (size_t i = 0; i < Effects.size(); i++)
	{
		UEffect* EffectPtr = Effects[i].get();
		if (false == EffectPtr->IsActive())
		{
			continue;
		}

		EffectPtr->Update(_DeltaTime);
		EffectPtr->Effect(shared_from_this());
	}
}