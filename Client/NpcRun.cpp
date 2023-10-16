#include "stdafx.h"
#include "NpcRun.h"
#include "Include.h"

CNpcRun::CNpcRun()
{
}


CNpcRun::~CNpcRun()
{
}

CAi * CNpcRun::OnUpdate(CObj* pObj)
{
	pObj->GetKey().eDir = DIRECTION_LEFT;
	pObj->ChangeAnimation(L"Run");
	((CNpc*)pObj)->SetFrame(false, false);
	return this;
}


