#include "stdafx.h"
#include "Boss2.h"
#include "Include.h"

HRESULT CBoss2::OnInit()
{
	m_tFrame.iFrame = 0;
	m_tFrame.fFrameTime = 0.05f;
	m_tFrame.fFrameTimeNow = 0;

	m_tKey.szSecondKey = L"Normal";
	m_tKey.eDir = DIRECTION_RIGHT;
	m_tKey.Option = L"";
	
	m_tInfo.vCenter = D3DXVECTOR3(50, 50, 0);

	return S_OK;
}

int CBoss2::OnUpdate()
{
	
	if (m_tKey.szRenderKey == L"BoosterL" || m_tKey.szRenderKey == L"BoosterR")
	{
		if (m_tKey.szRenderKey == L"BoosterL" && m_pParent->GetFrame().iFrame == 3)
		{
			ChangeAnimation(L"Break");
		}
		else if (m_tKey.szRenderKey == L"BoosterR" && m_pParent->GetFrame().iFrame == 2)
		{
			ChangeAnimation(L"Break");
		}

		if (m_pParent->GetKey().szSecondKey == L"Death")
			return RESULT_OBJECT_DELETE;
	}
	else if (m_tKey.szRenderKey == L"EngineL" || m_tKey.szRenderKey == L"EngineR")
	{
		if (m_pParent->GetState() &STATE_ATTACK && ((CBoss*)m_pParent)->GetLevel() == 2)
		{
			if (SINGLE(CObjMgr)->GetObjectList(L"0.BossBullet")->front()->GetKey().szSecondKey == L"Ready3"
				|| SINGLE(CObjMgr)->GetObjectList(L"0.BossBullet")->front()->GetKey().szSecondKey == L"Attack")
			{
				ChangeAnimation(L"Attack");
			}
		}
		else
			ChangeAnimation(L"Normal");

		if (m_tKey.szRenderKey == L"EngineL" && m_pParent->GetFrame().iFrame == 3)
		{
			CObj* effect = new CEffect(LAYER_EFFECT);
			effect->SetPos(D3DXVECTOR3(m_tInfo.vPos.x+m_pParent->GetInfo().vPos.x, m_tInfo.vPos.y+m_pParent->GetInfo().vPos.y, 0));
			effect->SetCenter(D3DXVECTOR3(50, 70, 0));
			effect->SetRenderKey(L"BigBoom");
			effect->GetKey().eDir = m_tKey.eDir;
			SINGLE(CObjMgr)->PushObject(L"2.Effect", effect);

			return RESULT_OBJECT_DELETE;
		}
		else if (m_tKey.szRenderKey == L"EngineR" && m_pParent->GetFrame().iFrame == 2)
		{
			CObj* effect = new CEffect(LAYER_EFFECT);
			effect->SetPos(D3DXVECTOR3(m_tInfo.vPos.x + m_pParent->GetInfo().vPos.x, m_tInfo.vPos.y + m_pParent->GetInfo().vPos.y, 0));
			effect->SetCenter(D3DXVECTOR3(50, 70, 0));
			effect->SetRenderKey(L"BigBoom");
			effect->GetKey().eDir = m_tKey.eDir;
			SINGLE(CObjMgr)->PushObject(L"2.Effect", effect);
			return RESULT_OBJECT_DELETE;
		}
		
	}
	FrameEnd = FrameMove();

	D3DXMATRIX matTrans;
	D3DXMatrixTranslation(&matTrans,
		m_tInfo.vPos.x,
		m_tInfo.vPos.y,
		m_tInfo.vPos.z);

	m_tInfo.matWorld = matTrans * (m_pParent->GetInfo().matWorld);
	return RESULT_NONE;
}

void CBoss2::OnRender()
{
	const TEXINFO* pTex = SINGLE(CTextureMgr)->GetTexture(
		m_tKey.szRenderKey, m_tKey.szSecondKey, m_tFrame.iFrame);
	if (pTex == 0)
		return;
	SINGLE(CDevice)->GetSprite()->SetTransform(&m_tInfo.matWorld);
	SINGLE(CDevice)->GetSprite()->Draw(
		pTex->pTexture, NULL, &m_tInfo.vCenter, 0,
		D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CBoss2::OnRelease()
{
}

CBoss2::CBoss2()
{
}


CBoss2::~CBoss2()
{
}
