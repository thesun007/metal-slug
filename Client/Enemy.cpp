#include "stdafx.h"
#include "Enemy.h"


vector<RECT> CEnemy::GetRect(void)
{
	vector<RECT> vecRect;
	RECT	rt =
	{
		int(m_tInfo.vPos.x - m_tInfo.vSize.x / 2.f),
		int(m_tInfo.vPos.y - m_tInfo.vSize.y / 2.f),
		int(m_tInfo.vPos.x + m_tInfo.vSize.x / 2.f),
		int(m_tInfo.vPos.y + m_tInfo.vSize.y / 2.f)
	};
	vecRect.push_back(rt);
	return vecRect;
}

CEnemy::CEnemy()
	:m_pPlayer(NULL)
{
}


CEnemy::~CEnemy()
{
}
