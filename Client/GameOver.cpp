#include "stdafx.h"
#include "GameOver.h"
#include "Include.h"

HRESULT CGameOver::OnInit()
{
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Over/background_gameover.png", L"GameOver")))
		return E_FAIL;

	m_fTime = 255;
	m_fWaitTime = 0;
	return S_OK;
}

int CGameOver::OnUpdate()
{
	if (5<=m_fTime && m_fWaitTime<=2)
	{
		m_fTime -= 0.25f;
	}
	else
	{
		m_fWaitTime += DeltaTime;
		if (m_fWaitTime > 2.0f)
		{
			m_fTime += 0.7f;
			if(m_fTime>250)
				return RESULT_SCENE_SELECT;
		}
	}
	return 0;
}

void CGameOver::OnRender()
{

	const TEXINFO* pTex = SINGLE(CTextureMgr)->GetTexture(
		L"GameOver");
	D3DXMATRIX matTrans;
	D3DXMatrixTranslation(&matTrans,
		0.f,
		0.f,
		0.f);
	SINGLE(CDevice)->GetSprite()->SetTransform(&matTrans);
	SINGLE(CDevice)->GetSprite()->Draw(
		pTex->pTexture, NULL, NULL, 0,
		D3DCOLOR_ARGB(255, 255, 255, 255));

	const TEXINFO* pTex2 = SINGLE(CTextureMgr)->GetTexture(
		L"Scenechange");
	D3DXMatrixTranslation(&matTrans,
		0.f,
		0.f,
		0.f);
	SINGLE(CDevice)->GetSprite()->SetTransform(&matTrans);
	SINGLE(CDevice)->GetSprite()->Draw(
		pTex2->pTexture, NULL, NULL, 0,
		D3DCOLOR_ARGB((int)m_fTime, 255, 255, 255));
}

void CGameOver::OnRelease()
{
}

CGameOver::CGameOver()
{
}


CGameOver::~CGameOver()
{
	CObjMgr::Destroy();
}
