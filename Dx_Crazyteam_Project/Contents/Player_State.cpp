#include "PreCompile.h"
#include "Player.h"

void APlayer::StateInit()
{
	//���⼭ ������ CreateAnimation �� �������.

	InputOn();


	// ������Ʈ �����
	State.CreateState("Die");
	State.CreateState("Idle");
	State.CreateState("Move");
	State.CreateState("Attack");

	

	State.SetStartFunction("Idle", [this]()
		{
			
		});

	State.SetUpdateFunction("Idle", [=](float _Delta)
		{

		});

	// ü����
	State.ChangeState("Idle");
}


void  APlayer::Idle()
{

}

