#include "stdafx.h"
#include "M2Ani.h"
#include "Include.h"

CM2Ani::CM2Ani()
{
}


CM2Ani::~CM2Ani()
{
	OnRelease();
}


HRESULT CM2Ani::OnInit()
{
	m_tFrame.iFrame = 0;
	m_tFrame.fFrameTime = 0.15f;
	m_tFrame.fFrameTimeNow = 0;
	m_tKey.szRenderKey = L"Ani";
	m_eLayer = LAYER_EFFECT;
	m_tInfo.vPos = D3DXVECTOR3(0, 10, 0);
	m_tInfo.vCenter = D3DXVECTOR3(16, 19, 0);
	return S_OK;
}

int CM2Ani::OnUpdate()
{
	FrameMove();
	D3DXMATRIX matTrans;
	D3DXMatrixTranslation(&matTrans,
			m_tInfo.vPos.x,
			m_tInfo.vPos.y,
			m_tInfo.vPos.z);
	
	m_tInfo.matWorld =  matTrans * (*m_pParentWorld);
	
	return RESULT_NONE;
}

void CM2Ani::OnRender()
{
	const TEXINFO* pTex = SINGLE(CTextureMgr)->GetTexture(
		L"M2select", L"",0);
	SINGLE(CDevice)->GetSprite()->SetTransform(&m_tInfo.matWorld);
	SINGLE(CDevice)->GetSprite()->Draw(
		pTex->pTexture, NULL, &D3DXVECTOR3(24,26,0), 0,
		D3DCOLOR_ARGB(255, 255, 255, 255));

	const TEXINFO* pTex1 = SINGLE(CTextureMgr)->GetTexture(
		m_tKey.szRenderKey,m_tKey.szSecondKey, m_tFrame.iFrame);
	if (pTex1 == 0)
		return;
	SINGLE(CDevice)->GetSprite()->SetTransform(&m_tInfo.matWorld);
	SINGLE(CDevice)->GetSprite()->Draw(
		pTex1->pTexture, NULL, &m_tInfo.vCenter, 0,
		D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CM2Ani::OnRelease()
{
}


