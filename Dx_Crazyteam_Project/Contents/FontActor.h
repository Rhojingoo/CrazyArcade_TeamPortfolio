#pragma once
#include <Enginecore/Actor.h>

class UTextWidget;

class AFontActor : public AActor
{
	GENERATED_BODY(AActor)
public:
	// constrcuter destructer
	AFontActor(); // ����Ʈ ������
	~AFontActor(); // ����Ʈ �Ҹ���

	// delete Function
	AFontActor(const AFontActor& _Other) = delete; // ����Ʈ ���� ������
	AFontActor(AFontActor&& _Other) noexcept = delete; 
	AFontActor& operator=(const AFontActor& _Other) = delete; // ����Ʈ ���� ������
	AFontActor& operator=(AFontActor&& _Other) noexcept = delete;

	UTextWidget* GetShowText()
	{
		return ShowText;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:

	UTextWidget* ShowText = nullptr;
};

