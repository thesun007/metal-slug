#include "stdafx.h"
#include "Special.h"
#include "Include.h"
#include "Wait.h"

CSpecial::CSpecial()
	:m_fWaitTime(0.8f), m_fNowTime(0.f)
{
}


CSpecial::~CSpecial()
{
}

CAi * CSpecial::OnUpdate(CObj * pObj)
{
	m_fNowTime += DeltaTime;

	if (pObj->GetKey().szSecondKey != L"Jump"&&
		pObj->GetKey().szSecondKey != L"Landing")
	{
		if (m_fNowTime < m_fWaitTime)
		{
			pObj->ChangeAnimation(L"Run");
			((CArabian*)pObj)->SetFrame(false, false);
			return this;
		}
		else
		{
			pObj->ChangeAnimation(L"Jump");
			((CArabian*)pObj)->SetFrame(false, true);
			m_fNowTime = 0;
			return this;
		}
	}
	else
	{
		if (pObj->GetKey().szSecondKey == L"Jump")
		{
			if (pObj->GetKey().eDir == DIRECTION_LEFT && pObj->GetFrame().iFrame>3)
				pObj->GetInfo().vPos.x -= DeltaTime *40;
			else if(pObj->GetKey().eDir == DIRECTION_RIGHT&& pObj->GetFrame().iFrame>2)
				pObj->GetInfo().vPos.x += DeltaTime * 25;
		}

		if (((CArabian*)pObj)->GetLanding())
		{
			pObj->ChangeAnimation(L"Landing");
			((CArabian*)pObj)->SetFrame(false, true);
			return this;
		}
		else if (pObj->GetKey().szSecondKey == L"Landing" &&
			((CArabian*)pObj)->GetFrameEnd())
		{
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
					if (pObj->GetKey().eDir == DIRECTION_LEFT)
					{
						pObj->GetKey().eDir = DIRECTION_RIGHT;
						pObj->ChangeAnimation(L"Jump");
						((CArabian*)pObj)->SetFrame(false, true);
						pObj->GetFrame().iFrame = 3;
						m_fNowTime = 0;
						return this;
					}
					else
					{
						pObj->GetKey().eDir = DIRECTION_LEFT;
						pObj->ChangeAnimation(L"Jump");
						((CArabian*)pObj)->SetFrame(false, true);
						pObj->GetFrame().iFrame = 4;
						m_fNowTime = 0;
						return this;
					}
				}
				else
				{
					delete this;
					return new CWait;
				}
			}
		}
	}
	return this;
}
