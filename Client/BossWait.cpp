#include "stdafx.h"
#include "BossWait.h"
#include "Include.h"
#include "BossReady.h"

CAi * CBossWait::OnUpdate(CObj * pObj)
{
	if (SINGLE(CCamMgr)->GetCamPos().x >= 3520)
	{
		delete this;
		return new CBossReady;
	}

	return this;
}

CBossWait::CBossWait()
{
}


CBossWait::~CBossWait()
{
}
