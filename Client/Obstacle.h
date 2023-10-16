#pragma once

#include "ObjStatic.h"

class CObstacle : public CObjStatic
{
private:
	
public:
	
public:
	virtual HRESULT OnInit();
	virtual int OnUpdate();
	virtual void OnRender();
	virtual void OnRelease();
public:
	CObstacle(void);
	virtual ~CObstacle(void);
};

