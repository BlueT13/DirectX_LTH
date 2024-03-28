#pragma once

#define GENERATED_BODY(Parent) \
	typedef Parent Super;

// Ό³Έν :
class UTickObject
{
public:
	// constrcuter destructer
	UTickObject();
	~UTickObject();

	// delete Function
	UTickObject(const UTickObject& _Other) = delete;
	UTickObject(UTickObject&& _Other) noexcept = delete;
	UTickObject& operator=(const UTickObject& _Other) = delete;
	UTickObject& operator=(UTickObject&& _Other) noexcept = delete;

	virtual void BeginPlay();
	virtual void Tick(float _DeltaTime);

	int GetOrder()
	{
		return Order;
	}

	void SetOrder(int _Order)
	{
		Order = _Order;
	}

protected:

private:
	int Order = 0;

};

