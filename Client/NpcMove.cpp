#include "stdafx.h"
#include "NpcMove.h"
#include "Include.h"
#include "NpcGive.h"
#include "NpcJump.h"

CNpcMove::CNpcMove()
	:m_fWaitTime(1.f), m_fNowTime(0)
{
}


CNpcMove::~CNpcMove()
{
}

CAi * CNpcMove::OnUpdate(CObj* pObj)
{
	// 플레이어가 존재한다면
	if (!SINGLE(CObjMgr)->GetObjectList(L"1.Tarma")->empty())
	{
		//부딪쳤다면
		if (SINGLE(CCollisionMgr)->ColRect(pObj->GetRect().front(),
			SINGLE(CObjMgr)->GetObjectList(L"1.Tarma")->front()) &&
			pObj->GetKey().szSecondKey == L"Move")
		{
			pObj->GetKey().eDir = DIRECTION_LEFT;
			delete this;
			return new CNpcGive;
		}
	}

	// 공중 지역
	if (pObj->GetLine() != NULL)
	{
		bool line = false;
		// 왼쪽 끝자락에 있었을 시
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
			if (!line && (pObj->GetKey().eDir == DIRECTION_LEFT))
			{
				if (((CNpc*)pObj)->GetLevel() == 0)
				{
					pObj->GetKey().eDir = DIRECTION_RIGHT;
					pObj->ChangeAnimation(L"TurnR");
					((CNpc*)pObj)->SetFrame(false, true);
					m_fWaitTime = 2.f;
					m_fNowTime = 0;
					return this;
				}
				else if (((CNpc*)pObj)->GetLevel() == 1)
				{
					delete this;
					return new CNpcJump;
				}
			}
		}

		//오른쪽 끝자락에 있었을 시
		else if (pObj->GetLine()->tRPoint.x - 5<= pObj->GetInfo().vPos.x)
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
			if (!line && (pObj->GetKey().eDir == DIRECTION_RIGHT))
			{
				if (((CNpc*)pObj)->GetLevel() == 0)
				{
					pObj->GetKey().eDir = DIRECTION_LEFT;
					pObj->ChangeAnimation(L"TurnR");
					((CNpc*)pObj)->SetFrame(false, true);
					m_fWaitTime = 2.f;
					m_fNowTime = 0;
					return this;
				}
				else if (((CNpc*)pObj)->GetLevel() == 1)
				{
					delete this;
					return new CNpcJump;
				}
			}
		}

		//공중지역 중간에 있었을 시
		line = false;
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
			if (((CNpc*)pObj)->GetLevel()==1)
			{
				m_fNowTime += DeltaTime;
				if (m_fNowTime >= 0.6)
				{
					delete this;
					return new CNpcJump;
				}
				pObj->ChangeAnimation(L"Move");
				((CNpc*)pObj)->SetFrame(false, false);
				return this;
			}
		}
	}

	if (pObj->GetKey().szSecondKey == L"Move")
	{
		m_fNowTime += DeltaTime;
		if (m_fNowTime >= m_fWaitTime)
		{
			m_fNowTime -= m_fWaitTime;
			if (pObj->GetKey().eDir == DIRECTION_LEFT)
			{
				pObj->GetKey().eDir = DIRECTION_RIGHT;
				pObj->ChangeAnimation(L"TurnR");
				((CNpc*)pObj)->SetFrame(false, true);
				m_fWaitTime = 2.f;
			}
			else
			{
				pObj->GetKey().eDir = DIRECTION_LEFT;
				pObj->ChangeAnimation(L"TurnR");
				((CNpc*)pObj)->SetFrame(false, true);
				m_fWaitTime = 2.f;
			}
			return this;
		}
	}

	pObj->ChangeAnimation(L"Move");
	((CNpc*)pObj)->SetFrame(false, false);

	return this;
}
