#include "StdAfx.h"
#include "Effect.h"
#include "Include.h"

CEffect::CEffect(LAYER layer)
{
	m_eLayer = layer;
	m_tInfo.vCenter = D3DXVECTOR3(50, 50, 0);
}

CEffect::~CEffect(void)
{
	OnRelease();
}

HRESULT CEffect::OnInit()
{
	m_tFrame.iFrame = 0;
	m_tFrame.fFrameTime = 0.075f;
	if(m_tKey.szSecondKey == L"BigBoom" || m_tKey.szSecondKey == L"MediumBoom")
		m_tFrame.fFrameTime = 0.04f;
	m_tFrame.fFrameTimeNow = 0;
	m_tKey.szRenderKey = L"Effect";

	/*m_eLayer = LAYER_EFFECT;*/

	return S_OK;
}

int CEffect::OnUpdate()
{
	if(FrameMove())
		return RESULT_OBJECT_DELETE;

	D3DXMATRIX matTrans, matScale;
	if(m_tKey.eDir == DIRECTION_RIGHT)
		D3DXMatrixScaling(&matScale,  1, 1, 1);
	else
		D3DXMatrixScaling(&matScale, -1, 1, 1);
	
	
	D3DXMatrixTranslation(&matTrans,
		m_tInfo.vPos.x - SINGLE(CCamMgr)->GetCamPos().x, 
		m_tInfo.vPos.y - SINGLE(CCamMgr)->GetCamPos().y,
		m_tInfo.vPos.z);
	
	m_tInfo.matWorld = matScale * matTrans;
	return 0;
}

void CEffect::OnRender()
{
	const TEXINFO* pTex = SINGLE(CTextureMgr)->GetTexture(
		m_tKey.szRenderKey, m_tKey.szSecondKey, m_tFrame.iFrame);
	if(pTex == 0)
		return;
	SINGLE(CDevice)->GetSprite()->SetTransform(&m_tInfo.matWorld);
	SINGLE(CDevice)->GetSprite()->Draw(
		pTex->pTexture, NULL, &m_tInfo.vCenter, 0, 
		D3DCOLOR_ARGB(255,255,255,255));
}

void CEffect::OnRelease()
{

}