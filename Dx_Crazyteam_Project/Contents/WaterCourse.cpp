#include "PreCompile.h"
#include "WaterCourse.h"
#include <EngineCore/DefaultSceneComponent.h>
#include "BaseMap.h"
#include "CAGameMode.h"

AWaterCourse::AWaterCourse()
{
	WaterCourseRender = CreateDefaultSubObject<USpriteRenderer>("Render");
	WaterCourseRender->SetupAttachment(Root);
}

AWaterCourse::~AWaterCourse()
{
}

void AWaterCourse::BeginPlay()
{
	Super::BeginPlay();

	StateInit();
	CreateAnimation();

	WaterCourseRender->SetAutoSize(1.0f, true);
	WaterCourseRender->SetOrder(ERenderOrder::Player);
	WaterCourseRender->SetActive(false);
}

void AWaterCourse::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	State.Update(_DeltaTime);

	if (true == CreateStart)
	{
		CreateWaterStream(_DeltaTime);
	}
}

void AWaterCourse::StateInit()
{
	State.CreateState("None");

	State.CreateState("CreateCenter"); // �߰� ���ٱ�.
	State.CreateState("CreateStream"); // �� �ٱ�.
	State.CreateState("CreateEndStem");// �� �ٱ� ��.

	State.CreateState("Delete"); // �����.

	State.SetStartFunction("None", std::bind(&AWaterCourse::NoneBegin, this));
	State.SetUpdateFunction("None", std::bind(&AWaterCourse::NoneTick, this, std::placeholders::_1));


	State.SetFunction("CreateCenter",
		std::bind(&AWaterCourse::CreateCenterBegin, this),
		std::bind(&AWaterCourse::CreateCenterTick, this, std::placeholders::_1),
		std::bind(&AWaterCourse::CreateCenterExit, this));
	State.SetFunction("CreateStream",
		std::bind(&AWaterCourse::CreateStreamBegin, this),
		std::bind(&AWaterCourse::CreateStreamTick, this, std::placeholders::_1),
		std::bind(&AWaterCourse::CreateStreamExit, this));
	State.SetFunction("CreateEndStem",
		std::bind(&AWaterCourse::CreateEndStemBegin, this),
		std::bind(&AWaterCourse::CreateEndStemTick, this, std::placeholders::_1),
		std::bind(&AWaterCourse::CreateEndStemExit, this));

	State.SetFunction("Delete",
		std::bind(&AWaterCourse::DeleteBegin, this),
		std::bind(&AWaterCourse::DeleteTick, this, std::placeholders::_1),
		std::bind(&AWaterCourse::DeleteExit, this));

	State.ChangeState("None");
}


void AWaterCourse::CreateAnimation()
{
	// �� �ٱ� ����
	WaterCourseRender->CreateAnimation("Water_Center", "Center11.png", 0.0625f, true, 0, 1);
	WaterCourseRender->CreateAnimation("Water_Center_End", "Center11.png", 0.0625f, false);

	{
		// ���ٱ� ���� ���� �� ����� �ִϸ��̼�
		WaterCourseRender->CreateAnimation("CreateUp", "up12.png", 0.125f, true, 0, 0);
		WaterCourseRender->CreateAnimation("CreateDown", "down12.png", 0.125f, true, 0, 0);
		WaterCourseRender->CreateAnimation("CreateLeft", "left12.png", 0.125f, true, 0, 0);
		WaterCourseRender->CreateAnimation("CreateRight", "right12.png", 0.125f, true, 0, 0);
	}

	{
		// �� ��. -> Tick���� ����� �ִϸ��̼�.
		WaterCourseRender->CreateAnimation("EndStemUp", "up12.png", 0.125f, true, 0, 1);
		WaterCourseRender->CreateAnimation("EndStemDown", "down12.png", 0.125f, true, 0, 1);
		WaterCourseRender->CreateAnimation("EndStemLeft", "left12.png", 0.125f, true, 0, 1);
		WaterCourseRender->CreateAnimation("EndStemRight", "right12.png", 0.125f, true, 0, 1);

		// �� �ٱ� �߰� -> Tick���� ����� �ִϸ��̼�.
		WaterCourseRender->CreateAnimation("StreamUp", "up22.png", 0.125f, true, 0, 2);
		WaterCourseRender->CreateAnimation("StreamDown", "down22.png", 0.0625f, true, 0, 2);
		WaterCourseRender->CreateAnimation("StreamLeft", "left22.png", 0.125f, true, 0, 2);
		WaterCourseRender->CreateAnimation("StreamRight", "right22.png", 0.125f, true, 0, 2);
	}

	{
		// �� �� �����.
		WaterCourseRender->CreateAnimation("D_EndStemUp", "up12.png", 0.125f, true, 1, 10);
		WaterCourseRender->CreateAnimation("D_EndStemDown", "down12.png", 0.125f, true, 1, 10);
		WaterCourseRender->CreateAnimation("D_EndStemLeft", "left12.png", 0.125f, true, 1, 10);
		WaterCourseRender->CreateAnimation("D_EndStemRight", "right12.png", 0.125f, true, 1, 10);

		// �� �ٱ� �����.
		WaterCourseRender->CreateAnimation("D_StreamUp", "up22.png", 0.125f, true, 1, 10);
		WaterCourseRender->CreateAnimation("D_StreamDown", "down22.png", 0.125f, true, 1, 10);
		WaterCourseRender->CreateAnimation("D_StreamLeft", "left22.png", 0.125f, true, 1, 10);
		WaterCourseRender->CreateAnimation("D_StreamRight", "right22.png", 0.125f, true, 1, 10);
	}

	WaterCourseRender->ChangeAnimation("Water_Center");
}

#pragma region None
void AWaterCourse::NoneBegin()
{
}

void AWaterCourse::NoneTick(float _DeltaTime)
{
}
#pragma endregion

#pragma region Center
void AWaterCourse::CreateCenterBegin()
{
	CenterLifeTime = 0.0f;
	CreateStart = true; // ���ٱ� ������.
	WaterCourseRender->ChangeAnimation("Water_Center");
	PreAniName = "Water_Center";
	WaterCourseRender->SetActive(true);
}
void AWaterCourse::CreateCenterTick(float _DeltaTime)
{
	CenterLifeTime += _DeltaTime;
	if (LifeTime <= CenterLifeTime)
	{
		State.ChangeState("Delete");
		return;
	}
}
void AWaterCourse::CreateCenterExit()
{
	CenterLifeTime = 0.0f;
}
#pragma endregion

#pragma region CreateStream // ���ٱ�
void AWaterCourse::CreateStreamBegin()
{
	switch (WaterCourseDir)
	{
	case EEngineDir::Up:
	{
		WaterCourseRender->ChangeAnimation("StreamUp");
		PreAniName = "StreamUp";
		break;
	}
	case EEngineDir::Down :
	{
		WaterCourseRender->ChangeAnimation("StreamDown");
		PreAniName = "StreamDown";
		break;
	}
	case EEngineDir::Left:
	{
		WaterCourseRender->ChangeAnimation("StreamLeft");
		PreAniName = "StreamLeft";
		break;
	}
	case EEngineDir::Right:
	{
		WaterCourseRender->ChangeAnimation("StreamRight");
		PreAniName = "StreamRight";
		break;
	}
	default :
		break;
	}

	WaterCourseRender->SetActive(true);
}

void AWaterCourse::CreateStreamTick(float _DeltaTime)
{
	CenterLifeTime += _DeltaTime;

	if (2.0f <= CenterLifeTime)
	{
		State.ChangeState("Delete");
		return;
	}
}
void AWaterCourse::CreateStreamExit()
{
	CenterLifeTime = 0.0f;
}
#pragma endregion

#pragma region CreateEndStem  TODO
void AWaterCourse::CreateEndStemBegin()
{
}
void AWaterCourse::CreateEndStemTick(float _DeltaTime)
{
}
void AWaterCourse::CreateEndStemExit()
{
}
#pragma endregion



#pragma region Delete
void AWaterCourse::DeleteBegin()
{
	//WaterCourseRender->ChangeAnimation(PreAniName);

	if (PreAniName == "Water_Center")
	{
		WaterCourseRender->ChangeAnimation("Water_Center_End");
		PreAniName = "Water_Center_End";
	}
	else if (PreAniName == "EndStemUp")
	{
		WaterCourseRender->ChangeAnimation("D_EndStemUp");
		PreAniName = "D_EndStemUp";
	}
	else if (PreAniName == "EndStemDown")
	{
		WaterCourseRender->ChangeAnimation("D_EndStemDown");
		PreAniName = "D_EndStemDown";
	}
	else if (PreAniName == "EndStemLeft")
	{
		WaterCourseRender->ChangeAnimation("D_EndStemLeft");
		PreAniName = "D_EndStemLeft";
	}
	else if (PreAniName == "EndStemRight")
	{
		WaterCourseRender->ChangeAnimation("D_EndStemRight");
		PreAniName = "D_EndStemRight";
	}
	else if (PreAniName == "StreamUp")
	{
		WaterCourseRender->ChangeAnimation("D_StreamUp");
		PreAniName = "D_StreamUp";
	}
	else if (PreAniName == "StreamDown")
	{
		WaterCourseRender->ChangeAnimation("D_StreamDown");
		PreAniName = "D_StreamDown";
	}
	else if (PreAniName == "StreamLeft")
	{
		WaterCourseRender->ChangeAnimation("D_StreamLeft");
		PreAniName = "D_StreamLeft";
	}
	else if (PreAniName == "StreamRight")
	{
		WaterCourseRender->ChangeAnimation("D_StreamRight");
		PreAniName = "D_StreamRight";
	}
}

void AWaterCourse::DeleteTick(float _DeltaTime)
{
	// Animation Final Frame callback
	WaterCourseRender->SetLastFrameCallback(PreAniName, [=]()
		{
			GetGameMode()->GetCurMap()->DestroyMapObject(CurPos.y, CurPos.x);
		}
	);
}

void AWaterCourse::DeleteExit()
{
}
#pragma endregion

// ������ ����.
void AWaterCourse::CreateWaterStream(float _DeltaTime)
{
	CreateDeltaTime += _DeltaTime;

	POINT WaterBombPoint = CurPos;



	if (0 <= CurPos.y - 1)
	{
		// ����� �� ���� ���� ����?
		std::shared_ptr<AMapObject> NextMapObject = GetGameMode()->GetCurMap()->GetMapObject(CurPos.y - 1, CurPos.x);
		EMapObjectType type = NextMapObject->GetType();
		if (type == EMapObjectType::None)
		{
			GetGameMode()->GetCurMap()->AddWaterCourse(CurPos.y - 1, CurPos.x, false, EEngineDir::Up);
		}
	}

	if (13 != CurPos.y + 1)
	{
		std::shared_ptr<AMapObject> NextMapObject = GetGameMode()->GetCurMap()->GetMapObject(CurPos.y + 1, CurPos.x);
		EMapObjectType type = NextMapObject->GetType();
		if (type == EMapObjectType::None)
		{
			GetGameMode()->GetCurMap()->AddWaterCourse(CurPos.y + 1, CurPos.x, false, EEngineDir::Down);
		}
	}

	if (0 <= CurPos.x - 1)
	{
		std::shared_ptr<AMapObject> NextMapObject = GetGameMode()->GetCurMap()->GetMapObject(CurPos.y, CurPos.x-1);
		EMapObjectType type = NextMapObject->GetType();
		if (type == EMapObjectType::None)
		{
			GetGameMode()->GetCurMap()->AddWaterCourse(CurPos.y, CurPos.x-1, false, EEngineDir::Left);
		}
	}

	if(15 != CurPos.x + 1)
	{
		std::shared_ptr<AMapObject> NextMapObject = GetGameMode()->GetCurMap()->GetMapObject(CurPos.y, CurPos.x+1);
		EMapObjectType type = NextMapObject->GetType();
		if (type == EMapObjectType::None)
		{
			GetGameMode()->GetCurMap()->AddWaterCourse(CurPos.y, CurPos.x+1, false, EEngineDir::Right);
		}
	}

	



	
	CreateStart = false; // Tick Control

	//NextMapObject->WaterInteract();
}