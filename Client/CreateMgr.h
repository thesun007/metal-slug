#pragma once
#include "Defines.h"
#include "Include.h"

class CCreateMgr
{
	SINGLETON(CCreateMgr);
private:
	int Enemy;
	float m_fWaitTime;
	float m_fNowTime;	
public:
	void CreateEnemy(list<LINE*>* listLine);
public:
	CCreateMgr();
	~CCreateMgr();
};

