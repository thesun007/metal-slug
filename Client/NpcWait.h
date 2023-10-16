#pragma once
#include "Ai.h"
class CNpcWait :
	public CAi
{
public:
	virtual CAi* OnUpdate(CObj* pObj);
public:
	CNpcWait();
	~CNpcWait();
};
