#pragma once

#include "Obj.h"

class CObjStatic : public CObj
{
public:
	virtual HRESULT OnInit()PURE;
	virtual int OnUpdate()PURE;
	virtual void OnRender()PURE;
	virtual void OnRelease()PURE;
public:
	CObjStatic(void);
	virtual ~CObjStatic(void);
};

