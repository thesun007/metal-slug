#pragma once
#include "ObjDynamic.h"
class CEBullet :
	public CObjDynamic
{
private:
	bool FrameEnd;
public:
	virtual HRESULT OnInit();
	virtual int OnUpdate();
	virtual void OnRender();
	virtual void OnRelease();
public:
	CEBullet(D3DXVECTOR3 _pos,wstring _secondkey,DIRECTION _dir);
	~CEBullet();
};

