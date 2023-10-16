#pragma once
#include "Ai.h"
class CSpecial :
	public CAi
{
private:
	float m_fWaitTime;
	float m_fNowTime;
public:
	virtual CAi* OnUpdate(CObj* pObj);
public:
	CSpecial();
	~CSpecial();
};

