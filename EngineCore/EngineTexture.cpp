#include "PreCompile.h"
#include "EngineTexture.h"

UEngineTexture::UEngineTexture() 
{
}

UEngineTexture::~UEngineTexture() 
{
	if (nullptr != Texture)
	{
		Texture->Release();
	}
}

