#include "stdafx.h"
#include "NpcWait.h"
#include "Include.h"
#include "NpcMove.h"

CNpcWait::CNpcWait()
{
}


CNpcWait::~CNpcWait()
{
}

CAi * CNpcWait::OnUpdate(CObj* pObj)
{
	if (pObj->GetState() & STATE_DIE)
	{
		if (pObj->GetKey().szSecondKey == L"Wait1")
		{
			pObj->ChangeAnimation(L"Free1");
			((CNpc*)pObj)->SetFrame(false, true);
			return this;
		}
		else if (pObj->GetKey().szSecondKey == L"Wait2")
		{
			pObj->ChangeAnimation(L"Free2");
			((CNpc*)pObj)->SetFrame(false, true);
			return this;
		}

		if (((CNpc*)pObj)->GetFrameEnd())
		{
			delete this;
			return new CNpcMove;
		}
	}
	else
	{
		((CNpc*)pObj)->SetFrame(false, false);
	}
	return this;
}
