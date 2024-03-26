#pragma once
#include <Windows.h>
#include <EnginePlatform/EngineWindow.h>

#pragma comment (lib, "EngineBase.lib")
#pragma comment (lib, "EnginePlatform.lib")

class UserCore
{
public:
	virtual void Initialize() = 0;
};

// Ό³Έν :
class UEngineCore
{
public:
	// constrcuter destructer
	UEngineCore();
	~UEngineCore();

	// delete Function
	UEngineCore(const UEngineCore& _Other) = delete;
	UEngineCore(UEngineCore&& _Other) noexcept = delete;
	UEngineCore& operator=(const UEngineCore& _Other) = delete;
	UEngineCore& operator=(UEngineCore&& _Other) noexcept = delete;

	template<typename UserCoreType>
	static void Start(HINSTANCE _Inst)
	{
		UEngineCore Core;
		UserCoreType UserCore;
		Core.UserCorePtr = &UserCore;
		Core.EngineStart(_Inst);
	}

	void SetWindowScale(FVector _Scale)
	{
		EngineWindow.SetWindowScale(_Scale);
	}

protected:

private:
	UEngineWindow EngineWindow;
	UserCore* UserCorePtr;

	void EngineStart(HINSTANCE _Inst);
};

extern UEngineCore* GEngine;