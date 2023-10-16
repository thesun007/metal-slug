#pragma once

#include "Defines.h"
#include "ObjDynamic.h"
class CM2 :
	public CObjDynamic
{
private:
	int m_iNumber;
	float m_fTime;
	bool m_bSelect;
public:
	void SetNumber(int num) { m_iNumber = num; }
	void SetSelect();
public:
	virtual HRESULT OnInit();
	virtual int OnUpdate();
	virtual void OnRender();
	virtual void OnRelease();
public:
	CM2();
	~CM2();
};

