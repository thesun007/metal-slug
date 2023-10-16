#include "stdafx.h"
#include "SecondBack.h"
#include "Include.h"

CSecondBack::CSecondBack()
{
}


CSecondBack::~CSecondBack()
{
	OnRelease();
}

HRESULT CSecondBack::OnInit()
{
	m_tFrame.iFrame = 0;
	m_tFrame.fFrameTime = 0.15f;
	m_tFrame.fFrameTimeNow = 0;
	m_tKey.szRenderKey = L"SecondBack";
	m_eLayer = LAYER_GROUND2;
	m_tInfo.vCenter = D3DXVECTOR3(0, 0, 0);
	return S_OK;
}

int CSecondBack::OnUpdate()
{
	D3DXMATRIX matTrans;
	D3DXMatrixTranslation(&matTrans,
		m_tInfo.vPos.x - SINGLE(CCamMgr)->GetCamPos().x,
		m_tInfo.vPos.y - SINGLE(CCamMgr)->GetCamPos().y,
		m_tInfo.vPos.z);
	m_tInfo.matWorld = matTrans;
	FrameMove();
	return RESULT_NONE;
}

void CSecondBack::OnRender()
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

void CSecondBack::OnRelease()
{
}

