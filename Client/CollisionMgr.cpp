#include "stdafx.h"
#include "CollisionMgr.h"
#include "Include.h"

bool CCollisionMgr::ColLine(list<LINE*> line, D3DXVECTOR3 &pos)
{
	float fy=0;

	for (auto iter = line.begin(); iter != line.end(); ++iter)
	{
		if (pos.x >= (*iter)->tLPoint.x &&
			pos.x <= (*iter)->tRPoint.x)
		{
			float fWidth = (*iter)->tRPoint.x - (*iter)->tLPoint.x;
			float fHeight = (*iter)->tRPoint.y - (*iter)->tLPoint.y;
			float y = (fHeight / fWidth)*(pos.x - (*iter)->tLPoint.x) + (*iter)->tLPoint.y;
			fy = y;
			break;
		}
	}

	if (pos.y > fy)
	{
		pos.y = fy;
		return true;
	}

	return false;
}

bool CCollisionMgr::ColRect(RECT rect, CObj * pObj)
{
	RECT rc;
	vector<RECT> vec = pObj->GetRect();
	for(auto iter =vec.begin(); iter != vec.end(); ++iter)
	{
		if (IntersectRect(&rc, &rect, &(*iter)) &&
			(pObj->GetState()&STATE_DIE) == 0)
		{
			return true;
		}
	}
	
	return false;
}

CCollisionMgr::CCollisionMgr()
{
}


CCollisionMgr::~CCollisionMgr()
{
}
