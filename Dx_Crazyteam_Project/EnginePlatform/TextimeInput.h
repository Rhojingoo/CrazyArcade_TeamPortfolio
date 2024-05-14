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
	char Text[255];
	char Cstr[10];
	char CanText[200];
	int CNumber = 0;
	int CanMax = 0;

};

