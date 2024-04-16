#pragma once
#include "TileMapLevel.h"

// ���� :
class ACreateMapMode : public ATileMapLevel
{
	GENERATED_BODY(ATileMapLevel)

public:
	// constrcuter destructer
	ACreateMapMode();
	~ACreateMapMode();

	// delete Function
	ACreateMapMode(const ACreateMapMode& _Other) = delete;
	ACreateMapMode(ACreateMapMode&& _Other) noexcept = delete;
	ACreateMapMode& operator=(const ACreateMapMode& _Other) = delete;
	ACreateMapMode& operator=(ACreateMapMode&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:

};

