#include "stdafx.h"
#include "Ready.h"
#include "Include.h"
#include "Move.h"
#include "Jump.h"
#include "Attack.h"

CReady::CReady()
	:m_fWaitTime(1.0f), m_fNowTime(0)
{
}


CReady::~CReady()
{
}

CAi * CReady::OnUpdate(CObj* pObj)
{
	//플레이어가 가까이 있을시
	if (!SINGLE(CObjMgr)->GetObjectList(L"1.Tarma")->empty())
	{
		D3DXVECTOR3 vgap = pObj->GetInfo().vPos - ((CArabian*)pObj)->GetParentObj()->GetInfo().vPos;
		float gap = sqrtf(vgap.x*vgap.x + vgap.y*vgap.y);
		if (gap < 40)
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
				pObj->ChangeAnimation(L"Shuffle");
				delete this;
				return new CJump;
			}

		}
	}

	//준비모션이 정해졌으면 일정시간까지 유지
	if (pObj->GetKey().szSecondKey == L"Shuffle" ||
		pObj->GetKey().szSecondKey == L"Prepare")
	{
		m_fNowTime += DeltaTime;
		if (m_fNowTime < m_fWaitTime)
		{
			return this;
		}
	}

	//플레이어 죽었을시
	if (SINGLE(CObjMgr)->GetObjectList(L"1.Tarma")->empty())
	{
		if (rand() % 2 == 0)
		{
			((CArabian*)pObj)->SetParentObj(NULL);
			pObj->ChangeAnimation(L"Shuffle");
			((CArabian*)pObj)->SetFrame(false, false);
			m_fNowTime = 0;
			return this;
		}
		else
		{
			((CArabian*)pObj)->SetParentObj(NULL);
			pObj->ChangeAnimation(L"Prepare");
			((CArabian*)pObj)->SetFrame(false, false);
			m_fNowTime = 0;
			return this;
		}
	}
	else //다시 살았을시
	{
		((CArabian*)pObj)->SetParentObj(SINGLE(CObjMgr)->GetObjectList(L"1.Tarma")->front());
	}

	// 공중 지역에 있었을시
	if (pObj->GetLine() != NULL)
	{
		bool line = false;
		float fWidth = pObj->GetLine()->tRPoint.x - pObj->GetLine()->tLPoint.x;
		float fHeight = pObj->GetLine()->tRPoint.y - pObj->GetLine()->tLPoint.y;
		float fy = (fHeight / fWidth)*(pObj->GetInfo().vPos.x - pObj->GetLine()->tLPoint.x) +
			pObj->GetLine()->tLPoint.y;

		auto iter = pObj->GetListLine()->begin();
		for (; iter != pObj->GetListLine()->end(); ++iter)
		{
			if ((*iter)->tLPoint.x <= pObj->GetInfo().vPos.x &&
				(*iter)->tRPoint.x >= pObj->GetInfo().vPos.x)
			{
				float fWidth = (*iter)->tRPoint.x - (*iter)->tLPoint.x;
				float fHeight = (*iter)->tRPoint.y - (*iter)->tLPoint.y;
				float y = (fHeight / fWidth)*(pObj->GetInfo().vPos.x - (*iter)->tLPoint.x) +
					(*iter)->tLPoint.y;
				if (y > fy)
				{
					line = true;
					break;
				}
			}
		}
		if (line)
		{
			if (rand() % 100 < 35)
			{
				delete this;
				return new CJump;
			}
		}
	}
	//준비 모션
	float length;
	length = fabs(pObj->GetInfo().vPos.x - ((CArabian*)pObj)->GetParentObj()->GetInfo().vPos.x);
	if (length > 160)
	{
		if (rand() % 100 < 5)
		{
			delete this;
			return new CAttack;
		}
		else
		{
			int random = rand() % 10;
			if (random <3)
			{
				pObj->ChangeAnimation(L"Prepare");
				((CArabian*)pObj)->SetFrame(false, false);
				m_fNowTime = 0;
				return this;
			}
			else if (random<6)
			{
				pObj->ChangeAnimation(L"Shuffle");
				((CArabian*)pObj)->SetFrame(false, false);
				m_fNowTime = 0;
				return this;
			}
			else
			{
				delete this;
				return new CMove;
			}
		}
	}
	if (120<length &&length <= 160)
	{
		if (rand()% 100 < 10)
		{
			delete this;
			return new CAttack;
		}
		else
		{
			int random=rand() % 10;
			if (random <3)
			{
				pObj->ChangeAnimation(L"Prepare");
				((CArabian*)pObj)->SetFrame(false, false);
				m_fNowTime = 0;
				return this;
			}
			else if(random<6)
			{
				pObj->ChangeAnimation(L"Shuffle");
				((CArabian*)pObj)->SetFrame(false, false);
				m_fNowTime = 0;
				return this;
			}
			else
			{
				delete this;
				return new CMove;
			}
		}
	}
	else if (length <= 120)
	{
		if (rand() % 100 < 20)
		{
			delete this;
			return new CAttack;
		}
		else
		{
			if (rand() % 10 < 7)
			{
				pObj->ChangeAnimation(L"Prepare");
				((CArabian*)pObj)->SetFrame(false, false);
				m_fNowTime = 0;
				return this;
			}
			else
			{
				pObj->ChangeAnimation(L"Shuffle");
				((CArabian*)pObj)->SetFrame(false, false);
				m_fNowTime = 0;
				return this;
			}
		}
	}
	return this;
}
