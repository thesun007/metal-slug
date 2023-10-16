#pragma once
#include "Ai.h"
class CNpcJump :
	public CAi
{
public:
	virtual CAi* OnUpdate(CObj* pObj);
public:
	CNpcJump();
	~CNpcJump();
};

