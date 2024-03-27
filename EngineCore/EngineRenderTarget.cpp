#include "PreCompile.h"
#include "EngineRenderTarget.h"

UEngineRenderTarget::UEngineRenderTarget() 
{
}

UEngineRenderTarget::~UEngineRenderTarget() 
{
}


void UEngineRenderTarget::AddNewTexture(std::shared_ptr<UEngineTexture> _Texture)
{
	Textures.push_back(_Texture);
}
