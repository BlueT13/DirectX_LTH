#pragma once
// #include <chrono> �ֽ� �ð� ��� ��� std.
#include <Windows.h>

// ���� :
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

	// �ð������� �����ϰڴ�.
	void TimeCheckStart();

	// ���ݱ��� �� ������?
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

	// �⺻������ CPU�ϵ� ���� ������ ���ο� Count�� �ϴ� �κ��� �����մϴ�.
	// ���� �������ڸ� ��ǻ�ʹ� �Ѵ� ���� CPU�� �����ϸ鼭 0 1 2 3 4 5 6
	// �ʴ� ������ ���� ���� ������ �����ϰ� ����.
};

