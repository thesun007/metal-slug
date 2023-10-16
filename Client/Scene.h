#pragma once

#include "Defines.h"

class CScene
{
public:
	virtual HRESULT OnInit()PURE;
	virtual int OnUpdate()PURE;
	virtual void OnRender()PURE;
	virtual void OnRelease()PURE;
public:
	CScene(void);
	virtual ~CScene(void);
};

