#pragma once
#include "Ai.h"
class CAttack :
	public CAi
{
public:
	virtual CAi* OnUpdate(CObj* pObj);
public:
	CAttack();
	~CAttack();
};

