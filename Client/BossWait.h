#pragma once
#include "Ai.h"
class CBossWait :
	public CAi
{
public:
	virtual CAi* OnUpdate(CObj* pObj);
public:
	CBossWait();
	~CBossWait();
};

