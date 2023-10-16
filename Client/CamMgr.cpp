#include "StdAfx.h"
#include "CamMgr.h"
#include "Obj.h"
#include "Include.h"

CCamMgr::CCamMgr(void)
{}

CCamMgr::~CCamMgr(void)
{}

HRESULT CCamMgr::OnInit()
{
	m_tPos = D3DXVECTOR2(0,48);		//156
	m_fMinY = 156.f;
	m_fMinX = 0.f;
	m_OffSetPos = { 120, m_fMinY };
	
	m_pFollowObject = NULL;
	m_bLock = false;
	return S_OK;
}

void CCamMgr::OnUpdate()
{
	if (!m_bLock)
	{
		if (m_pFollowObject == NULL)
			return;
		if (m_pFollowObject->GetInfo().vPos.x > 960)		//맵중간에 y축 변경시작 
			m_fMinY = 140.f;
		if (m_tPos.x >= 3519)
			m_fMinY = 118.f;
		//--------------------------------------------------------------
		if (m_pFollowObject->GetInfo().vPos.x > m_OffSetPos.x)
			m_OffSetPos.x = m_pFollowObject->GetInfo().vPos.x;

		else if (m_pFollowObject->GetInfo().vPos.x <  m_OffSetPos.x)
			m_OffSetPos.x = m_pFollowObject->GetInfo().vPos.x;

		//x 이동
		if (m_pFollowObject->GetInfo().vPos.x-120 >m_tPos.x)
		{
			if (m_OffSetPos.x - 120 > m_tPos.x)
				m_tPos.x += DeltaTime * 80.f;
			if (m_OffSetPos.x - 120 < m_tPos.x)
				m_tPos.x = m_OffSetPos.x - 120;
			if(m_tPos.x <=3520)
				m_fMinX = m_tPos.x;
			if(m_tPos.x > 3470)
				m_fMinX = 3470;
		}
		else
		{
			if (m_OffSetPos.x - 120 < m_tPos.x)
				m_tPos.x -= DeltaTime * 80.f;
			if (m_OffSetPos.x - 120 > m_tPos.x)
				m_tPos.x = m_OffSetPos.x - 120;
		}

		if (m_fMinY < m_OffSetPos.y)
		{
			m_OffSetPos.y = m_fMinY;
		}

		//y 이동
		if (m_fMinY == 140)
		{
			if (m_OffSetPos.y - 108 < m_tPos.y)
				m_tPos.y -= DeltaTime * 38;
		}
		else
		{
			if (m_OffSetPos.y - 108 < m_tPos.y)
				m_tPos.y -= DeltaTime * 15;
		}
		if (m_OffSetPos.y - 108 > m_tPos.y)
			m_tPos.y = m_OffSetPos.y - 108;

		/*m_tPos.y = m_pFollowObject->GetInfo().vPos.y - WINSIZEY / 2;*/

		if (m_tPos.x < m_fMinX)
			m_tPos.x = m_fMinX;
		if (m_tPos.x > 3520)
			m_tPos.x = 3520;
		if (m_tPos.y < 10)
			m_tPos.y = 10;
		if (m_tPos.y > 48)
			m_tPos.y = 48;
	}
}

void CCamMgr::SetCamObject(CObj* pObj)
{
	m_pFollowObject = pObj;
}
