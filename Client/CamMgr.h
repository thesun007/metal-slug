#pragma once

#include "Defines.h"

class CObj;
class CCamMgr
{
	SINGLETON(CCamMgr);
private:
	CObj*       m_pFollowObject;
	D3DXVECTOR2 m_tPos;
	POINTFLOAT	m_OffSetPos;
	float		m_fMinY;
	float		m_fMinX;
	bool		m_bLock;
public:
	const D3DXVECTOR2& GetCamPos() const {return m_tPos;}
	void SetCamObject(CObj* pObj);
	void SetLock(bool lock) { m_bLock = lock; }
public:
	HRESULT OnInit();
	void OnUpdate();
public:
	CCamMgr(void);
	~CCamMgr(void);
};

