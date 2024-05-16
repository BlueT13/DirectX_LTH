#pragma once
// #include <chrono> 최신 시간 재는 헤더 std.
#include <Windows.h>

// 설명 :
class UEngineTime
{
public:
	// constrcuter destructer
	UEngineTime();
	~UEngineTime();

	// delete Function
	UEngineTime(const UEngineTime& _Other) = delete;
	UEngineTime(UEngineTime&& _Other) noexcept = delete;
	UEngineTime& operator=(const UEngineTime& _Other) = delete;
	UEngineTime& operator=(UEngineTime&& _Other) noexcept = delete;

	// 시간측정을 시작하겠다.
	void TimeCheckStart();

	// 지금까지 얼마 지났어?
	float TimeCheck();

	double GetDeltaTime()
	{
		return DeltaTime;
	}

protected:

private:
	__int64 Count64;
	LARGE_INTEGER Count;
	LARGE_INTEGER PrevTime;
	LARGE_INTEGER CurTime;
	double dCount;
	double DeltaTime;

	// 기본적으로 CPU하드 웨어 적으로 내부에 Count를 하는 부분이 존재합니다.
	// 쉽게 설명하자면 컴퓨터는 켜는 순간 CPU가 동작하면서 0 1 2 3 4 5 6
	// 초당 오차가 거의 없을 정도로 일정하게 센다.
};

