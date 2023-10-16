#pragma once

#include "Defines.h"
#include "ObjStatic.h"
class CCharacter :
	public CObjStatic
{
	int cnt;
public:
	void SetFrame(int id) { m_tFrame.iFrame = id; }
public:
	virtual HRESULT OnInit();
	virtual int OnUpdate();
	virtual void OnRender();
	virtual void OnRelease();
public:
	CCharacter();
	~CCharacter();
};

