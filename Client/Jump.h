#pragma once
#include "Ai.h"
class CJump :
	public CAi
{
public:
	virtual CAi* OnUpdate(CObj* pObj);
public:
	CJump();
	~CJump();
};

