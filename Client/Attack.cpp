#include "stdafx.h"
#include "Attack.h"
#include "Include.h"
#include "Ready.h"

CAttack::CAttack()
{
}


CAttack::~CAttack()
{
}

CAi * CAttack::OnUpdate(CObj* pObj)
{
	//플레이어 죽었을시
	if (SINGLE(CObjMgr)->GetObjectList(L"1.Tarma")->empty())
	{
		if ((pObj->GetKey().szSecondKey == L"Attack" ||
			pObj->GetKey().szSecondKey == L"Throwing") &&
			((CArabian*)pObj)->GetFrameEnd())
		{
			delete this;
			return new CReady;
		}
		else if(pObj->GetKey().szSecondKey != L"Attack" &&
			pObj->GetKey().szSecondKey != L"Throwing")
		{
			delete this;
			return new CReady;
		}
	}

	if (pObj->GetKey().szSecondKey != L"Attack" &&
		pObj->GetKey().szSecondKey != L"Throwing")
	{
		D3DXVECTOR3 vgap = pObj->GetInfo().vPos - ((CArabian*)pObj)->GetParentObj()->GetInfo().vPos;
		float gap = sqrtf(vgap.x*vgap.x + vgap.y*vgap.y);
		if (gap < 50)
		{
			pObj->ChangeAnimation(L"Attack");
			((CArabian*)pObj)->SetFrame(false, true);
			return this;
		}
		else
		{
			pObj->ChangeAnimation(L"Throwing");
			((CArabian*)pObj)->SetFrame(false, true);
			return this;
		}
	}

	else
	{
		if (((CArabian*)pObj)->GetFrameEnd())
		{
			delete this;
			return new CReady;
		}
	}
	return this;
}