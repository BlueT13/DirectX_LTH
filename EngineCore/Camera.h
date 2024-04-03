#pragma once
#include <EngineBase/TransformObject.h>
#include "Actor.h"
#include "EngineEnums.h"

// Ό³Έν :
class ULevel;
class UCamera : public AActor
{
	friend ULevel;
	friend URenderer;

public:
	// constrcuter destructer
	UCamera();
	~UCamera();

	// delete Function
	UCamera(const UCamera& _Other) = delete;
	UCamera(UCamera&& _Other) noexcept = delete;
	UCamera& operator=(const UCamera& _Other) = delete;
	UCamera& operator=(UCamera&& _Other) noexcept = delete;

	inline void SetNear(float _Value)
	{
		Near = _Value;
	}

	inline void SetFar(float _Value)
	{
		Far = _Value;
	}

	inline FMatrix GetView()
	{
		return View;
	}
	inline FMatrix GetProjection()
	{
		return Projection;
	}


protected:

private:
	float Near = 1.0f;
	float Far = 10000.0f;

	ECameraType ProjectionType = ECameraType::Orthographic;
	float FOV = 60.0f;

	FMatrix View;
	FMatrix Projection;

	void CameraTransformUpdate();
};

