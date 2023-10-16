#include "stdafx.h"
#include "Wait.h"
#include "Include.h"
#include "Move.h"

CAi * CWait::OnUpdate(CObj* pObj)
{
	if (!SINGLE(CObjMgr)->GetObjectList(L"1.Tarma")->empty())
	{
		float length;
		length = fabs(pObj->GetInfo().vPos.x - SINGLE(CObjMgr)->GetObjectList(L"1.Tarma")->front()->GetInfo().vPos.x);

		if (length < 210 && pObj->GetLine() !=NULL)
		{
			((CArabian*)pObj)->SetParentObj(SINGLE(CObjMgr)->GetObjectList(L"1.Tarma")->front());
			delete this;
			return new CMove;
		}
	}
	pObj->ChangeAnimation(L"Prepare");
		((CArabian*)pObj)->SetFrame(false, false);
		return this;
	
}

CWait::CWait()
{
}


CWait::~CWait()
{
}
