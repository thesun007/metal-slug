#pragma once
#include "Ai.h"
class CNpcGive :
	public CAi
{
private:
	float m_fWaitTime;
	float m_fNowTime;
	int FrameStack;		// �����ִ� ��� 2ȸ �ݺ�
public:
	int GetFrameStack() { return FrameStack; }
public:
	virtual CAi* OnUpdate(CObj* pObj);
public:
	CNpcGive();
	~CNpcGive();
};

