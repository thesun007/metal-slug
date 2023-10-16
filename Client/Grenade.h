#pragma once
#include "ObjDynamic.h"
class CGrenade :
	public CObjDynamic
{
private:
	float m_fAngle;
	int m_iBounce;
	bool FrameEnd;
public:
	virtual HRESULT OnInit();
	virtual int OnUpdate();
	virtual void OnRender();
	virtual void OnRelease();
public:
	CGrenade(D3DXVECTOR3 pos);
	~CGrenade();
};

