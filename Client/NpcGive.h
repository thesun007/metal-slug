#pragma once
#include "Ai.h"
class CNpcGive :
	public CAi
{
private:
	float m_fWaitTime;
	float m_fNowTime;
	int FrameStack;		// 선물주는 장면 2회 반복
public:
	int GetFrameStack() { return FrameStack; }
public:
	virtual CAi* OnUpdate(CObj* pObj);
public:
	CNpcGive();
	~CNpcGive();
};

