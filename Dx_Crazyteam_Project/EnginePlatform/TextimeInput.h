#pragma once
class UTextimeInput
{
public:
	// constrcuter destructer
	UTextimeInput(); // ����Ʈ ������
	~UTextimeInput(); // ����Ʈ �Ҹ���

	// delete Function
	UTextimeInput(const UTextimeInput& _Other) = delete; // ����Ʈ ���� ������
	UTextimeInput(UTextimeInput&& _Other) noexcept = delete; 
	UTextimeInput& operator=(const UTextimeInput& _Other) = delete; // ����Ʈ ���� ������
	UTextimeInput& operator=(UTextimeInput&& _Other) noexcept = delete;
	static std::function<int(HWND, UINT, WPARAM, LPARAM)> SetTextIme;
protected:

private:
};

