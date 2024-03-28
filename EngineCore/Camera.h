#pragma once
#include <EngineBase/TransformObject.h>

// Ό³Έν :
class UCamera : public UTransformObject
{
public:
	// constrcuter destructer
	UCamera();
	~UCamera();

	// delete Function
	UCamera(const UCamera& _Other) = delete;
	UCamera(UCamera&& _Other) noexcept = delete;
	UCamera& operator=(const UCamera& _Other) = delete;
	UCamera& operator=(UCamera&& _Other) noexcept = delete;

protected:

private:
};

