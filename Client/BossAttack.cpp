#include "stdafx.h"
#include "BossAttack.h"
#include "Boss.h"
#include "Include.h"
#include "BossReady.h"

CBossAttack::CBossAttack()
	: m_fWaitTime(12.f), m_fNowTime(0)
{

}


CBossAttack::~CBossAttack()
{
}


CAi * CBossAttack::OnUpdate(CObj * pObj)
{
	pObj->GetState() |= STATE_ATTACK;

	m_fNowTime += DeltaTime;
	if(SINGLE(CObjMgr)->GetObjectList(L"1.Tarma")->empty())
		m_fNowTime = 2.f;

	if (m_fNowTime >= m_fWaitTime)	//일정시간 공격뒤 쿨타임단계로 이동
	{
		if (((CBoss*)pObj)->GetLevel() == 1 && ((CBoss*)pObj)->GetFrame().iFrame == 2)
		{
			delete this;
			return new CBossReady;
		}
		else if (((CBoss*)pObj)->GetLevel() == 2)
		{
			if (!SINGLE(CObjMgr)->GetObjectList(L"1.Tarma")->empty())
			{
				pObj->GetState() = STATE_DOWN;
				((CBoss*)pObj)->SetMove(0.6f);
				delete this;
				return new CBossReady;
			}
		}
	}
	return this;
}

