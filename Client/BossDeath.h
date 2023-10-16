#pragma once
#include "Ai.h"
class CBossDeath :
	public CAi
{
public:
	virtual CAi* OnUpdate(CObj* pObj);
public:
	CBossDeath();
	~CBossDeath();
};

