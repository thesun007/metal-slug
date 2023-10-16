#include "stdafx.h"
#include "Character.h"
#include "Include.h"

CCharacter::CCharacter()
{
}


CCharacter::~CCharacter()
{
	OnRelease();
}

HRESULT CCharacter::OnInit()
{
	m_tKey.szRenderKey = L"Character";
	m_tFrame.iFrame = 0;
	m_eLayer = LAYER_GROUND;
	cnt = 0;
	return S_OK;
}

int CCharacter::OnUpdate()
{
	if(m_tFrame.iFrame !=2)
		m_tFrame.iFrame = 0;

	D3DXMATRIX matTrans;
	D3DXMatrixTranslation(&matTrans,
		m_tInfo.vPos.x ,
		m_tInfo.vPos.y ,
		m_tInfo.vPos.z);

	m_tInfo.matWorld =  matTrans;
	return RESULT_NONE;
}

void CCharacter::OnRender()
{
	const TEXINFO* pTex = SINGLE(CTextureMgr)->GetTexture(
		m_tKey.szRenderKey, m_tKey.szSecondKey, m_tFrame.iFrame);
	if (pTex == 0)
		return;
	SINGLE(CDevice)->GetSprite()->SetTransform(&m_tInfo.matWorld);
	SINGLE(CDevice)->GetSprite()->Draw(
		pTex->pTexture, NULL, &m_tInfo.vCenter, 0,
		D3DCOLOR_ARGB(255, 255, 255, 255));
	if (m_tFrame.iFrame == 2 && cnt < 18)
	{
		cnt++;
		wstring secondkey = m_tKey.szSecondKey + L"S";
		const TEXINFO* pTex2 = SINGLE(CTextureMgr)->GetTexture(
			m_tKey.szRenderKey, secondkey, 0);
		if (pTex2 == 0)
			return;
		SINGLE(CDevice)->GetSprite()->SetTransform(&m_tInfo.matWorld);
		SINGLE(CDevice)->GetSprite()->Draw(
			pTex2->pTexture, NULL, &m_tInfo.vCenter, 0,
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}

}

void CCharacter::OnRelease()
{
	
}
