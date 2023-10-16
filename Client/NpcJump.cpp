#include "stdafx.h"
#include "NpcJump.h"
#include "Include.h"
#include "NpcMove.h"

CNpcJump::CNpcJump()
{
}


CNpcJump::~CNpcJump()
{
}


CAi * CNpcJump::OnUpdate(CObj* pObj)
{
	if (pObj->GetKey().szSecondKey != L"Jump")
	{
		pObj->ChangeAnimation(L"Jump");
		((CNpc*)pObj)->SetFrame(false, false);
		return this;
	}
	else
	{
		if (((CNpc*)pObj)->GetLanding())
		{
			pObj->ChangeAnimation(L"Move");
			((CNpc*)pObj)->SetFrame(false, false);
			delete this;
			return new CNpcMove;
		}
	}
	return this;
}
