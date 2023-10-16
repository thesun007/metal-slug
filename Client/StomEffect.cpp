#include "stdafx.h"
#include "StomEffect.h"
#include "Include.h"

CStomEffect::CStomEffect( DIRECTION _dir)
	:FrameEnd(false), FrameOne(false)
{
	m_tKey.eDir = _dir;
}


CStomEffect::~CStomEffect()
{
}


HRESULT CStomEffect::OnInit()
{
	m_tFrame.iFrame = 0;
	m_tFrame.fFrameTime = 0.06f;
	m_tFrame.fFrameTimeNow = 0;
	m_tKey.szRenderKey = L"Blast";
	m_tKey.szSecondKey = L"Normal";
	m_eLayer = LAYER_EFFECT3;
	m_vPos = D3DXVECTOR3(0, 135, 0);
	m_tInfo.vCenter = D3DXVECTOR3(50, 50, 0);

	m_tInfo.vSize = D3DXVECTOR2(0, 0);
	return S_OK;
}

int CStomEffect::OnUpdate()
{
	if (m_pParentObj == NULL)
		return RESULT_OBJECT_DELETE;

	m_tInfo.vPos = m_pParentObj->GetInfo().vPos + m_vPos;

	if (!SINGLE(CCollisionMgr)->ColLine(*m_plistLine, m_tInfo.vPos))
	{
		m_tKey.szSecondKey = L"";
	}
	else
	{
		m_tInfo.vPos.y =m_tInfo.vPos.y + 2;
		if (m_pParentObj->GetKey().szSecondKey == L"Normal")
		{
			if (m_tKey.szSecondKey == L"Attack")
			{
				ChangeAnimation(L"AttackEnd");
				FrameOne = true;
			}
			else if(FrameEnd)
			{
				ChangeAnimation(L"Normal");
				FrameOne = false;
			}
		}
		else if (m_pParentObj->GetKey().szSecondKey == L"Ready2")
		{
			ChangeAnimation(L"Ready");
			FrameOne = false;
		}
		else if (m_pParentObj->GetKey().szSecondKey == L"Ready3" ||
			m_pParentObj->GetKey().szSecondKey == L"Attack")
		{
			ChangeAnimation(L"Attack");
			FrameOne = false;
		}

	}
	//ÇÁ·¹ÀÓ
	if (FrameOne)
		FrameEnd = FrameMoveone();
	else
		FrameEnd = FrameMove();

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

void CStomEffect::OnRender()
{
	const TEXINFO* pTex = SINGLE(CTextureMgr)->GetTexture(
		m_tKey.szRenderKey, m_tKey.szSecondKey, m_tFrame.iFrame);
	if (pTex == 0)
		return;
	SINGLE(CDevice)->GetSprite()->SetTransform(&m_tInfo.matWorld);
	SINGLE(CDevice)->GetSprite()->Draw(
		pTex->pTexture, NULL, &m_tInfo.vCenter, 0,
		D3DCOLOR_ARGB(255 / m_iAlpha, 255, 255, 255));
}

void CStomEffect::OnRelease()
{

}