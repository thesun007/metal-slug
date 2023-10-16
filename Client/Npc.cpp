#include "stdafx.h"
#include "Npc.h"
#include "Include.h"
#include "NpcGive.h"

CNpc::CNpc()
	:FrameEnd(false), FrameOne(false), FrameReverse(false), Landing(false)
	, DownTime(true), JumpTime(0), FreeTime(true)
{
	m_tKey.eDir = DIRECTION_LEFT;
}


CNpc::~CNpc()
{
	OnRelease();
}

void CNpc::Motion()
{
	if (m_tKey.szSecondKey != L"TurnR" ||
		((m_tKey.szSecondKey == L"TurnR") && FrameEnd))
		m_pAI = m_pAI->OnUpdate(this);

	if (m_tKey.szSecondKey == L"Free2" && m_tFrame.iFrame==1)
	{
		if (FreeTime)
		{
			CObj* effect = new CEffect(LAYER_GROUND2);
			effect->SetPos(D3DXVECTOR3(m_tInfo.vPos.x, m_tInfo.vPos.y, 0));
			effect->SetRenderKey(L"Wood");
			effect->GetKey().eDir = m_tKey.eDir;
			SINGLE(CObjMgr)->PushObject(L"2.Effect", effect);
			FreeTime = false;
		}
	}
}

void CNpc::Action()
{
	if (m_tKey.szSecondKey == L"Wait1")		// 앉아서 묶인상태
	{
		if (DownTime)
		{
			m_tInfo.vPos.y += 10;
			m_iFootposY -= 10;
			DownTime = false;
		}
	}
	else if (m_tKey.szSecondKey == L"Free1"&& FrameEnd&&		//풀리고나서
		!DownTime)		
	{
		m_tInfo.vPos.y -= 10;
		m_iFootposY += 10;
		DownTime = true;
	}

	if (m_tKey.szSecondKey == L"Jump")		//점프일때
	{
		if (!m_bJump)
		{
			m_fTime = 0.f;
			m_fTimeNow = 0.f;
			m_fV = 0.7f;
			m_bJump = true;
		}
	}
	if (m_tKey.szSecondKey == L"Move")	//걷기
	{
		if (m_tKey.eDir == DIRECTION_LEFT)
		{
			m_tInfo.vPos.x -= DeltaTime * 30;
		}
		else
		{
			m_tInfo.vPos.x += DeltaTime * 30;
		}
	}
	if (m_tKey.szSecondKey == L"Run")	//달리기
	{
		if (m_tKey.eDir == DIRECTION_LEFT)
		{
			m_tInfo.vPos.x -= DeltaTime * 140;
		}
	}
}

void CNpc::Give()
{
	int d;
	if (m_tKey.eDir == DIRECTION_LEFT)
		d = -1;
	else
		d = 1;

	if (m_tKey.szSecondKey == L"Give")
	{
		if (((CNpcGive*)m_pAI)->GetFrameStack() == 1 &&
			m_tFrame.iFrame == 3 && m_bGive)
		{
			if (m_iGift == 0)
				CreateItem(D3DXVECTOR3(m_tInfo.vPos.x+15*d, m_tInfo.vPos.y+5, 0), L"Heavy");
			else if(m_iGift == 1)
				CreateItem(D3DXVECTOR3(m_tInfo.vPos.x+15*d, m_tInfo.vPos.y+5, 0), L"Grenade");
			m_bGive = false;
		}
	}
}

void CNpc::CreateItem(D3DXVECTOR3 pos, wstring name)
{
	CObj* item = new CItem(pos, name);
	item->SetLine(m_plistLine);
	SINGLE(CObjMgr)->PushObject(L"0.Bullet", item);
}

HRESULT CNpc::OnInit()
{
	m_tFrame.iFrame = 0;
	m_tFrame.fFrameTime = 0.1f;
	m_tFrame.fFrameTimeNow = 0;
	m_tKey.szRenderKey = L"Npc";
	m_tKey.Option = L"";

	m_bMove = false;
	m_byState = STATE_NONE;
	m_eLayer = LAYER_OBJECT;

	m_tInfo.vCenter = D3DXVECTOR3(60, 50, 0);
	m_tInfo.vSize = D3DXVECTOR2(20, 30);
	m_iFootposY = 23;
	m_iHp = 1;

	m_pAI = new CNpcWait;

	m_bJump = false;
	m_fV = 0.f;
	m_fTime = 0.f;

	m_bGive = true;
	return S_OK;
}

int CNpc::OnUpdate()
{
	if (m_iHp <= 0)
		m_byState = STATE_DIE;	//죽은게 아니고 포박에서 풀려남

	if (m_tInfo.vPos.x < SINGLE(CCamMgr)->GetCamPos().x - 40)
		return RESULT_OBJECT_DELETE;

	Motion();
	Action();
	Give();

	//프레임
	if (!FrameReverse)
	{
		if (FrameOne)
			FrameEnd = FrameMoveone();
		else
			FrameEnd = FrameMove();
	}
	else
	{
		FrameEnd = FrameMoveReverse();
	}
	//-----------------------------------------------------------------

	if (m_bJump)
		Jump();

	if (m_tKey.szSecondKey == L"Jump")
	{
		JumpTime += DeltaTime;
		if (JumpTime >= 0.5f)
		{
			Landing = LineCol();
		}
	}
	else
	{
		Landing = LineCol();
		JumpTime = 0;
	}
	

	D3DXMATRIX matTrans, matScale;
	if (m_tKey.eDir == DIRECTION_RIGHT)
		D3DXMatrixScaling(&matScale, 1, 1, 1);
	else
		D3DXMatrixScaling(&matScale, -1, 1, 1);
	D3DXMatrixTranslation(&matTrans,
		m_tInfo.vPos.x - SINGLE(CCamMgr)->GetCamPos().x,
		m_tInfo.vPos.y - SINGLE(CCamMgr)->GetCamPos().y,
		m_tInfo.vPos.z);

	m_tInfo.matWorld = matScale * matTrans;

	return RESULT_NONE;
}

void CNpc::OnRender()
{
	const TEXINFO* pTex = SINGLE(CTextureMgr)->GetTexture(
		m_tKey.Option + m_tKey.szRenderKey, m_tKey.szSecondKey, m_tFrame.iFrame);
	if (pTex == 0)
		return;
	SINGLE(CDevice)->GetSprite()->SetTransform(&m_tInfo.matWorld);
	SINGLE(CDevice)->GetSprite()->Draw(
		pTex->pTexture, NULL, &m_tInfo.vCenter, 0,
		D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CNpc::OnRelease()
{
}
