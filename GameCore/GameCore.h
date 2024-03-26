#pragma once
#include <EngineCore/EngineCore.h>

// Ό³Έν :
class UGameCore : public UserCore
{
public:
	// constrcuter destructer
	UGameCore();
	~UGameCore();

	// delete Function
	UGameCore(const UGameCore& _Other) = delete;
	UGameCore(UGameCore&& _Other) noexcept = delete;
	UGameCore& operator=(const UGameCore& _Other) = delete;
	UGameCore& operator=(UGameCore&& _Other) noexcept = delete;

protected:
	void Initialize() override;

private:

};

