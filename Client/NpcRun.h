#pragma once
#include "Ai.h"
class CNpcRun :
	public CAi
{
public:
	virtual CAi* OnUpdate(CObj* pObj);
public:
	CNpcRun();
	~CNpcRun();
};

