#include "PreCompile.h"
#include "EngineShader.h"

UEngineShader::UEngineShader() 
{
}

UEngineShader::~UEngineShader() 
{
	if (nullptr != ErrorCodeBlob)
	{
		ErrorCodeBlob->Release();
	}

	if (nullptr != ShaderCodeBlob)
	{
		ShaderCodeBlob->Release();
	}
}

