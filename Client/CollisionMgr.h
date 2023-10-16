#pragma once
#include "Defines.h"
#include "Include.h"

class CCollisionMgr
{
	SINGLETON(CCollisionMgr);
public:
	bool ColLine(list<LINE*> line, D3DXVECTOR3 &pos);
	bool ColRect(RECT rect, CObj* pObj);
public:
	CCollisionMgr();
	~CCollisionMgr();
};

