#pragma once
#include <EnginePlatform/EngineResources.h>

class UEngineMaterial;
// Ό³Έν :
class UEngineDepthStencil : public UEngineResources<UEngineDepthStencil>
{
	friend UEngineMaterial;

public:
	// constrcuter destructer
	UEngineDepthStencil();
	~UEngineDepthStencil();

	// delete Function
	UEngineDepthStencil(const UEngineDepthStencil& _Other) = delete;
	UEngineDepthStencil(UEngineDepthStencil&& _Other) noexcept = delete;
	UEngineDepthStencil& operator=(const UEngineDepthStencil& _Other) = delete;
	UEngineDepthStencil& operator=(UEngineDepthStencil&& _Other) noexcept = delete;

	static std::shared_ptr<UEngineDepthStencil> Create(std::string_view _Name, const D3D11_DEPTH_STENCIL_DESC& _Info)
	{
		std::shared_ptr<UEngineDepthStencil> Res = CreateResName(_Name);
		Res->ResCreate(_Info);
		return Res;
	}

protected:
	

private:
	ID3D11DepthStencilState* State = nullptr;

	void ResCreate(const D3D11_DEPTH_STENCIL_DESC& _Info);
	void Setting();
};