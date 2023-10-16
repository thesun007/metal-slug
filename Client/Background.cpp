#include "stdafx.h"
#include "Background.h"
#include "Include.h"

CBackground::CBackground()
{
}


CBackground::~CBackground()
{
	OnRelease();
}


HRESULT CBackground::OnInit()
{
	m_tFrame.iFrame = 0;
	m_tFrame.fFrameTime = 0.15f;
	m_tFrame.fFrameTimeNow = 0;
	m_tKey.szRenderKey = L"Background";
	m_eLayer = LAYER_GROUND;
	m_tInfo.vPos = D3DXVECTOR3(0, 0, 0);
	m_tInfo.vCenter = D3DXVECTOR3(0, 0, 0);
	return S_OK;
}

int CBackground::OnUpdate()
{
	D3DXMATRIX matTrans;
	if (m_tKey.szSecondKey == L"Sky")
	{
		D3DXMatrixTranslation(&matTrans,
			m_tInfo.vPos.x - SINGLE(CCamMgr)->GetCamPos().x/18,
			m_tInfo.vPos.y - SINGLE(CCamMgr)->GetCamPos().y/2,
			m_tInfo.vPos.z);
	}
	else if (m_tKey.szSecondKey == L"Desert")
	{
		D3DXMatrixTranslation(&matTrans,
			m_tInfo.vPos.x - SINGLE(CCamMgr)->GetCamPos().x/6,
			m_tInfo.vPos.y - SINGLE(CCamMgr)->GetCamPos().y/2,
			m_tInfo.vPos.z);
	}
	else if (m_tKey.szSecondKey == L"Map")
	{
		D3DXMatrixTranslation(&matTrans,
			m_tInfo.vPos.x - SINGLE(CCamMgr)->GetCamPos().x,
			m_tInfo.vPos.y - SINGLE(CCamMgr)->GetCamPos().y,
			m_tInfo.vPos.z);
	}
	m_tInfo.matWorld =  matTrans;
	return RESULT_NONE;
}

void CBackground::OnRender()
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

void CBackground::OnRelease()
{
}
