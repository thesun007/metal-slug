#pragma once

#include "Defines.h"
#include "ObjDynamic.h"

class CM2Ani :
	public CObjDynamic
{
private:
	D3DXMATRIX* m_pParentWorld;
public:
	void SetParentWorld(D3DXMATRIX* pParentWorld)
	{
		m_pParentWorld = pParentWorld;
	}
public:
	virtual HRESULT OnInit();
	virtual int OnUpdate();
	virtual void OnRender();
	virtual void OnRelease();
public:
	CM2Ani();
	~CM2Ani();
};

