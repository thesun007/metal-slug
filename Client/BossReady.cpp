#include "stdafx.h"
#include "BossReady.h"
#include "Include.h"
#include "BossAttack.h"


CBossReady::CBossReady()
	: m_fWaitTime(1.f), m_fNowTime(0.f)
{
}


CBossReady::~CBossReady()
{
}


CAi * CBossReady::OnUpdate(CObj * pObj)
{
	if ((((CBoss*)pObj)->GetLevel() == 0))
	{
		if (pObj->GetInfo().vPos.y < 77)
		{
			pObj->GetInfo().vPos.y += DeltaTime * 20;
		}
		else
		{
			((CBoss*)pObj)->SetLevel(1);
			pObj->GetState() |= STATE_UP;
			((CBoss*)pObj)->SetMove(0.6f);
			delete this;
			return new CBossAttack;
		}
	}
	else if (((CBoss*)pObj)->GetLevel() !=0)
	{
		if (pObj->GetState()&STATE_ATTACK)
			pObj->GetState() ^= STATE_ATTACK;

		if (((CBoss*)pObj)->GetLevel() == 1)
		{
			if (pObj->GetInfo().vPos.y > 52)
			{
				((CBoss*)pObj)->SetDonMove(true);
				//pObj->GetState() |= STATE_ATTACK;
				pObj->GetInfo().vPos.y -= DeltaTime * 30;
			}
			else
			{
				((CBoss*)pObj)->SetDonMove(false);
				/*pObj->GetInfo().vPos.y = 52;*/
				((CBoss*)pObj)->SetLevel(2);
				pObj->GetState() |= STATE_UP;
				((CBoss*)pObj)->SetMove(0.1f);
				delete this;
				return new CBossAttack;
			}
		}
		else if (((CBoss*)pObj)->GetLevel() == 2)
		{
			m_fNowTime += DeltaTime;
			if (m_fNowTime >= m_fWaitTime)		//일정 쿨타임 뒤 공격 다시 시작
			{
				if (pObj->GetInfo().vPos.y > 52)
				{
					((CBoss*)pObj)->SetDonMove(true);
					pObj->GetInfo().vPos.y -= DeltaTime * 30;
				}
				else
				{
					((CBoss*)pObj)->SetDonMove(false);
					pObj->GetState() |= STATE_UP;
					((CBoss*)pObj)->SetMove(0.1f);
					delete this;
					return new CBossAttack;
				}
			}
		}
	}
	return this;
}
