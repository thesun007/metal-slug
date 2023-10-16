#include "stdafx.h"
#include "NpcGive.h"
#include "Include.h"
#include "NpcRun.h"

CNpcGive::CNpcGive()
	:m_fWaitTime(0.2f), m_fNowTime(0),FrameStack(0)
{
}


CNpcGive::~CNpcGive()
{
}

CAi * CNpcGive::OnUpdate(CObj* pObj)
{
	//������ �̵��� Giving ���
	if (pObj->GetKey().szSecondKey == L"Move")
	{
		m_fNowTime += DeltaTime;
		if (m_fNowTime < m_fWaitTime)
		{
			pObj->GetInfo().vPos.x += DeltaTime * 220;
			return this;
		}
		else
		{
			pObj->ChangeAnimation(L"Giving");
			((CNpc*)pObj)->SetFrame(false, true);
			m_fNowTime = 0;
			return this;
		}
	}

	//Givng ��� ���� �� ��ǰ���
	if (pObj->GetKey().szSecondKey == L"Giving" && ((CNpc*)pObj)->GetFrameEnd()
		&&FrameStack == 0)
	{
		pObj->ChangeAnimation(L"Give");
		((CNpc*)pObj)->SetFrame(false, false);
	}
	else if (pObj->GetKey().szSecondKey == L"Giving" && ((CNpc*)pObj)->GetFrameEnd()
		&&FrameStack == 2)
	{
		if (!SINGLE(CObjMgr)->GetObjectList(L"1.Tarma")->empty())
		{
			if (SINGLE(CObjMgr)->GetObjectList(L"1.Tarma")->front()->GetInfo().vPos.x
				< pObj->GetInfo().vPos.x)
			{
				if (pObj->GetKey().eDir == DIRECTION_LEFT)
				{
					pObj->ChangeAnimation(L"Salute");
					((CNpc*)pObj)->SetFrame(false, true);
					return this;
				}
				else
				{
					pObj->GetKey().eDir = DIRECTION_LEFT;
					return this;
				}
			}
			else if (SINGLE(CObjMgr)->GetObjectList(L"1.Tarma")->front()->GetInfo().vPos.x
				> pObj->GetInfo().vPos.x)
			{
				if (pObj->GetKey().eDir == DIRECTION_RIGHT)
				{
					pObj->ChangeAnimation(L"Salute");
					((CNpc*)pObj)->SetFrame(false, true);
					return this;
				}
				else
				{
					pObj->GetKey().eDir = DIRECTION_RIGHT;
					return this;
				}
			}
		}
		else
		{
			pObj->ChangeAnimation(L"Salute");
			((CNpc*)pObj)->SetFrame(false, true);
			return this;
		}
	}

	// �����ֱ� ��� �� �Ųٷ�giving ���
	if (pObj->GetKey().szSecondKey == L"Give" && ((CNpc*)pObj)->GetFrameEnd())
	{
		++FrameStack;
		if (FrameStack == 2)
		{
			pObj->ChangeAnimationR(L"Giving");
			((CNpc*)pObj)->SetFrame(true, true);
			return this;
		}
	}

	//��� ��
	if (pObj->GetKey().szSecondKey == L"Salute" && ((CNpc*)pObj)->GetFrameEnd())
	{
		delete this;
		return new CNpcRun;
	}

	return this;
}
