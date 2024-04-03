#pragma once
#include "EngineEnums.h"
#include "EngineConstantBuffer.h"

class USetterBase
{
public:
	EShaderType Type = EShaderType::NONE;
	int Slot = -1; // b0, b1, b2
};

// setter라는 녀석을 들고 있을 겁니다.
class UEngineConstantBufferSetter : public USetterBase
{
public:
	std::shared_ptr<class UEngineConstantBuffer> Res;
	// 각 액터마다 가지고 있는 데이터를 세팅할 녀석
	const void* CPUData = nullptr;
	UINT BufferSize = 0;

	void Setting();
};

// 설명 :
class URenderer;
class UEngineShader;
class UEngineShaderResources
{
	friend UEngineShader;
	friend URenderer;

public:
	template<typename Value>
	void SettingConstantBuffer(std::string_view _Name, Value& _Data)
	{
		SettingConstantBuffer(_Name, &_Data, static_cast<UINT>(sizeof(Value)));
	}

	void SettingConstantBuffer(std::string_view _Name, const void* _Data, UINT _Size);

	bool IsConstantBuffer(std::string_view _Name);

	void SettingAllShaderResources();

protected:

private:
	void ShaderResourcesCheck(EShaderType _Type, std::string_view _EntryName, ID3DBlob* _ShaderCode);

	// 픽셀쉐이더랑 
	// 버텍스 쉐이더 
	std::map<EShaderType, std::map<std::string, UEngineConstantBufferSetter>> ConstantBuffers;

};

