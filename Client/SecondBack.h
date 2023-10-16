#pragma once

#include "Defines.h"
#include "ObjStatic.h"

class CSecondBack :
	public CObjStatic
{
public:
	virtual HRESULT OnInit();
	virtual int OnUpdate();
	virtual void OnRender();
	virtual void OnRelease();
public:
	CSecondBack();
	~CSecondBack();
};

