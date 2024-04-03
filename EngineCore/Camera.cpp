#include "PreCompile.h"
#include "Camera.h"
#include "EngineCore.h"

UCamera::UCamera() 
{
}

UCamera::~UCamera() 
{
}

void UCamera::CameraTransformUpdate()
{
	// ºäÇà·Ä ¸¸µé¾îÁü
	View.View(GetActorLocation(), GetActorForwardVector(), GetActorUpVector());

	FVector Scale = GEngine->GetWindowScale();

	switch (ProjectionType)
	{
	case ECameraType::NONE:
		break;
	case ECameraType::Perspective:
		Projection.PerspectiveFovDeg(FOV, Scale.X, Scale.Y, Near, Far);
		break;
	case ECameraType::Orthographic:
		Projection.OrthographicLH(Scale.X, Scale.Y, Near, Far);
		break;
	default:
		break;
	}

}
