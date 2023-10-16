#include "stdafx.h"
#include "Move.h"
#include "Include.h"
#include "Ready.h"
#include "Jump.h"
#include "Attack.h"

CMove::CMove()
	:m_fWaitTime(0.5f), m_fNowTime(0)
{
}


CMove::~CMove()
{
}

CAi * CMove::OnUpdate(CObj* pObj)
{
	//플레이어 죽었을시
	if (SINGLE(CObjMgr)->GetObjectList(L"1.Tarma")->empty())
	{
		delete this;
		return new CReady;
	}

	//플레이어가 가까이 있을시
	D3DXVECTOR3 vgap = pObj->GetInfo().vPos - ((CArabian*)pObj)->GetParentObj()->GetInfo().vPos;
	float gap =sqrtf(vgap.x*vgap.x + vgap.y*vgap.y);
	if (gap < 50)
	{
		if (((CArabian*)pObj)->GetLevel() == 1 && rand() % 100 < 25)
		{
			delete this;
			return new CAttack;
		}
		else if (((CArabian*)pObj)->GetLevel() == 2 && rand() % 100 < 50)
		{
			delete this;
			return new CAttack;
		}
		else if (((CArabian*)pObj)->GetLevel() == 3)
		{
			delete this;
			return new CAttack;
		}
		else
		{
			delete this;
			return new CJump;
		}
	}

	// 공중 지역의 끝에 있었을시
	if (pObj->GetLine() != NULL)
	{
		bool line = false;
		if (pObj->GetLine()->tLPoint.x + 5 >= pObj->GetInfo().vPos.x)
		{
			auto iter = pObj->GetListLine()->begin();
			for (; iter != pObj->GetListLine()->end(); ++iter)
			{
				if ((*iter)->tRPoint.x == pObj->GetLine()->tLPoint.x &&
					(*iter)->tRPoint.y == pObj->GetLine()->tLPoint.y)
				{
					line = true;
					break;
				}
			}
			if (!line)
			{
				delete this;
				return new CReady;
			}
		}
		else if (pObj->GetLine()->tRPoint.x - 5 <= pObj->GetInfo().vPos.x)
		{
			auto iter = pObj->GetListLine()->begin();
			for (; iter != pObj->GetListLine()->end(); ++iter)
			{
				if ((*iter)->tLPoint.x == pObj->GetLine()->tRPoint.x &&
					(*iter)->tLPoint.y == pObj->GetLine()->tRPoint.y)
				{
					line = true;
					break;
				}
			}
			if (!line)
			{
				delete this;
				return new CReady;
			}
		}
	}
	//이동모션
	float length;
	length = fabs(pObj->GetInfo().vPos.x - ((CArabian*)pObj)->GetParentObj()->GetInfo().vPos.x);
	
	if (length > 160)
	{
		if (((CArabian*)pObj)->GetLevel() == 0)
		{
			delete this;
			return new CReady;
		}
		pObj->ChangeAnimation(L"Run");
		((CArabian*)pObj)->SetFrame(false, false);
		return this;
	}
	else if (120 < length && length <= 160)
	{
		if (pObj->GetKey().szSecondKey == L"Run")
		{
			m_fNowTime += DeltaTime;
			if (m_fNowTime < m_fWaitTime)
			{
				return this;
			}
		}
		
		if (((CArabian*)pObj)->GetLevel()==1 && rand() % 100 <= 20)
		{
			pObj->ChangeAnimation(L"Run");
			((CArabian*)pObj)->SetFrame(false, false);
			m_fNowTime = 0;
			return this;
		}
		else if (((CArabian*)pObj)->GetLevel() == 2 && rand() % 100 <= 50)
		{
			pObj->ChangeAnimation(L"Run");
			((CArabian*)pObj)->SetFrame(false, false);
			m_fNowTime = 0;
			return this;
		}
		else
		{
			delete this;
			return new CReady;
		}
	}
	else if (length <= 120)
	{
		if (pObj->GetKey().szSecondKey == L"Run")
		{
			m_fNowTime += DeltaTime;
			if (m_fNowTime < m_fWaitTime)
			{
				return this;
			}
		}

		if (rand() % 100 <= 2)
		{
			pObj->ChangeAnimation(L"Run");
			((CArabian*)pObj)->SetFrame(false, false);
			m_fNowTime = 0;
			return this;
		}
		else
		{
			delete this;
			return new CReady;
		}
	}
	return this;
}
