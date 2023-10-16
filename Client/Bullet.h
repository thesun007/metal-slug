#pragma once
#include "ObjDynamic.h"
class CBullet :
	public CObjDynamic
{
private:
	float m_fAngle;
	D3DXVECTOR3 m_vDir;

	bool FrameEnd;
public:
	virtual HRESULT OnInit();
	virtual int OnUpdate();
	virtual void OnRender();
	virtual void OnRelease();
public:
	CBullet(float _angle, D3DXVECTOR3 _pos,float _angle2);
	~CBullet();
};

