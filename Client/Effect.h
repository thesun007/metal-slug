#pragma once

#include "ObjDynamic.h"

class CEffect : public CObjDynamic
{
public:
	virtual HRESULT OnInit();
	virtual int OnUpdate();
	virtual void OnRender();
	virtual void OnRelease();
public:
	CEffect(LAYER layer);
	virtual ~CEffect(void);
};

