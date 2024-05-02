#pragma once

// Ό³Έν :
class BossStageMode
{
public:
	// constrcuter destructer
	BossStageMode();
	~BossStageMode();

	// delete Function
	BossStageMode(const BossStageMode& _Other) = delete;
	BossStageMode(BossStageMode&& _Other) noexcept = delete;
	BossStageMode& operator=(const BossStageMode& _Other) = delete;
	BossStageMode& operator=(BossStageMode&& _Other) noexcept = delete;

protected:

private:

};

