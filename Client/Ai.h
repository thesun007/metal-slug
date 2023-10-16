#pragma once
#include "Defines.h"

class CObj;

class CAi
{
public:
	virtual CAi* OnUpdate(CObj* pObj) =0;
public:
	CAi();
	~CAi();
};

