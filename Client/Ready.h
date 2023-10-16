#pragma once
#include "Ai.h"

class CReady :
	public CAi
{
private:
	float m_fWaitTime;
	float m_fNowTime;
public:
	virtual CAi* OnUpdate(CObj* pObj);
public:
	CReady();
	~CReady();
};

