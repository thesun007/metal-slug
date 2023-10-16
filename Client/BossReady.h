#pragma once
#include "Ai.h"
class CBossReady :
	public CAi
{
private:
	float m_fWaitTime;
	float m_fNowTime;
public:
	virtual CAi* OnUpdate(CObj* pObj);
public:
	CBossReady();
	~CBossReady();
};

