#pragma once
#include "Ai.h"
class CWait :
	public CAi
{
public:
	virtual CAi* OnUpdate(CObj* pObj);
public:
	CWait();
	~CWait();
};

