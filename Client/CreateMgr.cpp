#include "stdafx.h"
#include "CreateMgr.h"


void CCreateMgr::CreateEnemy(list<LINE*>* listLine)
{
	Enemy = 0;
	if (SINGLE(CCamMgr)->GetCamPos().x +304<3550
		&&SINGLE(CCamMgr)->GetCamPos().x + 304 > 650)
	{
		//화면에 적이 없는지 확인
		auto iter = SINGLE(CObjMgr)->GetObjectList(L"1.Enemy")->begin();
		for (; iter != SINGLE(CObjMgr)->GetObjectList(L"1.Enemy")->end(); ++iter)
		{
			if (SINGLE(CCamMgr)->GetCamPos().x <= (*iter)->GetInfo().vPos.x &&
				(*iter)->GetInfo().vPos.x <= SINGLE(CCamMgr)->GetCamPos().x + 331&&
				(*iter)->GetKey().szRenderKey !=L"Npc")
			{
				++Enemy;
				if(Enemy>1)
					break;
			}
		}

		if (Enemy<2)
		{
			m_fNowTime += DeltaTime;
			if (m_fNowTime < m_fWaitTime)		//일정시간 전까지 기다림
			{
				return;
			}
			m_fNowTime -= m_fWaitTime;
			float x = SINGLE(CCamMgr)->GetCamPos().x + 329;

			auto iter = listLine->begin();
			for (; iter != listLine->end(); ++iter)
			{
				if ((*iter)->tLPoint.x <= x && x <= (*iter)->tRPoint.x)
				{
					float fWidth = (*iter)->tRPoint.x - (*iter)->tLPoint.x;
					float fHeight = (*iter)->tRPoint.y - (*iter)->tLPoint.y;
					float y = (fHeight / fWidth)*(x - (*iter)->tLPoint.x) +(*iter)->tLPoint.y;

					if (rand() % 100 < 50)
					{
						CObj* enemy1 = new CArabian;
						enemy1->SetLine(listLine);
						enemy1->SetPos(D3DXVECTOR3(x, y-25, 0));
						((CArabian*)enemy1)->SetLevel(rand()%3 +1);
						SINGLE(CObjMgr)->PushObject(L"1.Enemy", enemy1);
					}

				}
			}
		}
	}
}

CCreateMgr::CCreateMgr()
	:Enemy(0), m_fWaitTime(0.5f), m_fNowTime(0.f)
{
}


CCreateMgr::~CCreateMgr()
{
}
