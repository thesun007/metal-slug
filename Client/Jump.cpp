#include "stdafx.h"
#include "Jump.h"
#include "Include.h"
#include "Ready.h"

CJump::CJump()
{
}


CJump::~CJump()
{
}

CAi * CJump::OnUpdate(CObj* pObj)
{
	if (pObj->GetKey().szSecondKey != L"BackStep" &&
		pObj->GetKey().szSecondKey != L"Jump"&&pObj->GetKey().szSecondKey != L"Landing")
	{
		D3DXVECTOR3 vgap = pObj->GetInfo().vPos - ((CArabian*)pObj)->GetParentObj()->GetInfo().vPos;
		float gap = sqrtf(vgap.x*vgap.x + vgap.y*vgap.y);
		if (gap < 50)
		{
			pObj->ChangeAnimation(L"BackStep");
			((CArabian*)pObj)->SetFrame(false, true);
			return this;
		}
		else
		{
			pObj->ChangeAnimation(L"Jump");
			((CArabian*)pObj)->SetFrame(false, true);
			return this;
		}
	}
	else
	{
		if (((CArabian*)pObj)->GetLanding())
		{
			pObj->ChangeAnimation(L"Landing");
			((CArabian*)pObj)->SetFrame(false, true);
			return this;
		}
		else if (pObj->GetKey().szSecondKey ==L"Landing"&&
			((CArabian*)pObj)->GetFrameEnd())
		{
			delete this;
			return new CReady;
		}
	}
	return this;
}


