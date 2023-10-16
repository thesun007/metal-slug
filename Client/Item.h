#pragma once
#include "Defines.h"
#include "ObjDynamic.h"
class CItem :
	public CObjDynamic
{
private:
	bool Landing;
public:
	virtual HRESULT OnInit();
	virtual int OnUpdate();
	virtual void OnRender();
	virtual void OnRelease();
public:
	CItem(D3DXVECTOR3 _pos, wstring _renderkey);
	~CItem();
};

