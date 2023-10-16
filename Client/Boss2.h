#pragma once
#include "ObjDynamic.h"
class CBoss2 :
	public CObjDynamic
{
private:
	bool FrameEnd;

	CObj* m_pParent;
public:
	void SetParent(CObj* pParent)
	{
		m_pParent = pParent;
	}
public:
	virtual HRESULT OnInit();
	virtual int OnUpdate();
	virtual void OnRender();
	virtual void OnRelease();
public:
	CBoss2();
	~CBoss2();
};

