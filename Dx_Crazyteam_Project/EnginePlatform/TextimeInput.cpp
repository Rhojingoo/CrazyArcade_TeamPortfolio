#include "PreCompile.h"
#include "TextimeInput.h"

#include <EnginePlatform/EngineInput.h>

#pragma warning(disable:4996) 

char UTextimeInput::Text[255]="";
char UTextimeInput::Cstr[10]="";
bool UTextimeInput::OnOff = false;
HWND UTextimeInput::hwnd;
HIMC UTextimeInput::himc;


std::string UTextimeInput::GetReadText()
{
	char Text1[255];
	memset(Text1, 0, 255);

	strcpy(Text1, Text);

	if (Cstr[0] != 0)
	{
		strcpy(Text1 + strlen(Text), Cstr);
	}

	strcpy(Text1 + strlen(Text1), "_");

	return Text1;
}

void UTextimeInput::On()
{
	OnOff = true;
}

void UTextimeInput::Off()
{
	OnOff = false;
	memset(Text, 0, 255);
	memset(Cstr, 0, 10);
}



void UTextimeInput::SetIme(HWND _hWnd,UINT _msg, WPARAM _wparam, LPARAM _lParam)
{

	if (false == OnOff)
	{
		return;
	}

	hwnd = _hWnd;
	himc = ImmGetContext(_hWnd);

	int len = 0;
	switch (_msg)
	{
	case WM_IME_COMPOSITION:
		if (_lParam & GCS_COMPSTR) // ������ ���� 
		{
			len = ImmGetCompositionString(himc, GCS_COMPSTR, NULL, 0);
			ImmGetCompositionString(himc, GCS_COMPSTR, Cstr, len);
			Cstr[len] = 0;
			
		}else if(_lParam & GCS_RESULTSTR) // �ϼ��� ����
		{
			len = ImmGetCompositionString(himc, GCS_RESULTSTR, NULL, 0);
		
			if (len > 0)
			{
				ImmGetCompositionString(himc, GCS_RESULTSTR, Cstr, len);
				Cstr[len] = 0;
				strcpy(Text + strlen(Text), Cstr);
				memset(Cstr, 0, 10);
			}
			
		}
		ImmReleaseContext(hwnd, himc); 
		break;
	case WM_CHAR: // ����� ���� ó��
		if (_wparam == 8)
		{
			if (strlen(Text) > 0) // �ѱ� ���ﶧ 
			{
				
				if (Text[strlen(Text) - 1] == ' ')
				{
					Text[strlen(Text) - 1] = 0;
					memset(Cstr, 0, 10);
					return;
				}

				if (Text[strlen(Text) - 1] >= 33 && Text[strlen(Text) - 1] <= 126) // �ƽ�Ű �ڵ� ��� ����� Ư�����ڵ� ����
				{
					Text[strlen(Text) - 1] = 0;
					memset(Cstr, 0, 10);
					return;
				}


				Text[strlen(Text) - 1] = 0;

				if (strlen(Text) > 0)
				{
					Text[strlen(Text) - 1] = 0;
				}

				memset(Cstr, 0, 10);
			}
		}
		else
		{
			if (_wparam == VK_RETURN)
			{
				break;
			}
			//len = static_cast<int>(strlen(Text));
			Text[strlen(Text)] = _wparam & 0xff;
			Text[strlen(Text)] = 0;
		}
		break;
	case WM_KEYDOWN:
		break;
	default:
		break;
	}
}




