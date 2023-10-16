#include "StdAfx.h"
#include "ObjDynamic.h"
#include "Include.h"

CObjDynamic::CObjDynamic(void)
	:m_fTimeNow(0.f), m_iDeathCount(0), m_iAlpha(1)
{}

CObjDynamic::~CObjDynamic(void)
{}


vector<RECT> CObjDynamic::GetRect(void)
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

void CObjDynamic::Jump()
{
	m_fTimeNow += DeltaTime;
	if (m_fTimeNow >= 0.009f)
	{
		m_fTime += 0.1f;
		m_tInfo.vPos.y += -sinf(90 * PI / 180) * m_fV + (0.98f * m_fTime) / 2;
		m_fTimeNow -= 0.009f;
	}
}

bool CObjDynamic::LineCol()
{
	float fy;
	float length;
	float oldlength = 3;
	//라인이 존재하지만,
	if (m_pLine != NULL)
	{
		float fWidth = m_pLine->tRPoint.x - m_pLine->tLPoint.x;
		float fHeight = m_pLine->tRPoint.y - m_pLine->tLPoint.y;
		float y = (fHeight / fWidth)*(m_tInfo.vPos.x - m_pLine->tLPoint.x) + m_pLine->tLPoint.y;
		// 라인에서 벗어났으면
		if ((m_tInfo.vPos.x < m_pLine->tLPoint.x ||
			m_tInfo.vPos.x > m_pLine->tRPoint.x))
			m_pLine = NULL;
		//라인내 이지만 y가 서로 다를때
		else if ((m_tInfo.vPos.y+ m_iFootposY) != y)
		{
			if (!m_bJump)
				fy = y;
			else
				m_pLine = NULL;
		}
		//라인에 벗어나지 않았으면
		else
			fy = y;

	}

	if (m_pLine == NULL)
	{
		for (auto iter = m_plistLine->begin();
			iter != m_plistLine->end(); ++iter)
		{
			if (m_tInfo.vPos.x >= (*iter)->tLPoint.x &&
				m_tInfo.vPos.x <= (*iter)->tRPoint.x)
			{
				float fWidth = (*iter)->tRPoint.x - (*iter)->tLPoint.x;
				float fHeight = (*iter)->tRPoint.y - (*iter)->tLPoint.y;
				float y = (fHeight / fWidth)*(m_tInfo.vPos.x - (*iter)->tLPoint.x) + (*iter)->tLPoint.y;
				if (fabs(y - (m_tInfo.vPos.y+ m_iFootposY)) <= 3)
				{
					length = fabs(y - (m_tInfo.vPos.y+ m_iFootposY));
					if (length < oldlength)
					{
						fy = y;
						oldlength = length;
						m_pLine = (*iter);
					}
				}
			}
		}
	}

	if (m_pLine == NULL)
	{
		if (m_bJump)
			return false;
		else
		{
			m_bJump = true;
			/*m_bCJump = true;*/
			m_fV = 0.3f;
			m_fTime = 0.f;
			m_fTimeNow = 0.f;
			return false;
		}
	}

	if (!m_bJump)
		m_tInfo.vPos.y = fy- m_iFootposY;

	else
	{
		if ((-sinf(90 * PI / 180) * m_fV + (0.98f * m_fTime) / 2) >= 0)
		{
			m_bJump = false;
			/*m_bCJump = false;*/
			m_tInfo.vPos.y = fy- m_iFootposY;
			m_fTime = 0.f;
			return true;
		}
	}

	return false;
}

