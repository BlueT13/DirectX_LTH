#pragma once
#include <EngineCore/EngineCore.h>

// Ό³Έν :
class UDungreedCore : public UserCore
{
public:
	// constrcuter destructer
	UDungreedCore();
	~UDungreedCore();

	// delete Function
	UDungreedCore(const UDungreedCore& _Other) = delete;
	UDungreedCore(UDungreedCore&& _Other) noexcept = delete;
	UDungreedCore& operator=(const UDungreedCore& _Other) = delete;
	UDungreedCore& operator=(UDungreedCore&& _Other) noexcept = delete;

protected:
	void Initialize() override;

private:

};

