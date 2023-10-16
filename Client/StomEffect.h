#pragma once
#include "ObjDynamic.h"
class CStomEffect :
	public CObjDynamic
{
private:
	CObj* m_pParentObj;

	D3DXVECTOR3 m_vPos;
	bool FrameEnd;
	bool FrameOne;
public:
	void SetParentObj(CObj* pParent) { m_pParentObj = pParent; }
public:
	virtual HRESULT OnInit();
	virtual int OnUpdate();
	virtual void OnRender();
	virtual void OnRelease();
public:
	CStomEffect( DIRECTION _dir);
	~CStomEffect();
};

