#include "stdafx.h"
#include "M2.h"
#include "Include.h"

CM2::CM2()
	:m_iNumber(0),m_fTime(0.f), m_bSelect(false)
{
}


CM2::~CM2()
{
}

void CM2::SetSelect()
{
	m_fTime = 0.f;
	m_bSelect = true;
}

HRESULT CM2::OnInit()
{
	m_tKey.szRenderKey = L"M2";
	m_tKey.szSecondKey = L"";
	m_tFrame.iFrame = 0;
	m_eLayer = LAYER_OBJECT;
	return S_OK;
}

int CM2::OnUpdate()
{
	if (!m_bSelect)
	{
		m_fTime += DeltaTime;
		if (m_iNumber == 0)
		{
			if (m_fTime > 1.5)
			{
				if (m_tInfo.vPos.y > -11)
					m_tInfo.vPos.y -= DeltaTime * 268;
			}
		}
		else if (m_iNumber == 1)
		{
			if (m_fTime > 1.7)
			{
				if (m_tInfo.vPos.y > -11)
					m_tInfo.vPos.y -= DeltaTime * 268;
			}
		}
		else if (m_iNumber == 2)
		{
			if (m_fTime > 1.8)
			{
				if (m_tInfo.vPos.y > -11)
					m_tInfo.vPos.y -= DeltaTime * 268;
			}
		}
		else if (m_iNumber == 3)
		{
			if (m_fTime > 1.95)
			{
				if (m_tInfo.vPos.y > -11)
					m_tInfo.vPos.y -= DeltaTime * 268;
			}
		}
	}
	else
	{

		m_fTime += DeltaTime;
		if (m_fTime > 0.25)
		{
			if(m_tInfo.vPos.y < 123)
				m_tInfo.vPos.y += DeltaTime * 370;
		}
	}
	D3DXMATRIX matTrans;
	D3DXMatrixTranslation(&matTrans,
		m_tInfo.vPos.x,
		m_tInfo.vPos.y,
		m_tInfo.vPos.z);

	m_tInfo.matWorld = matTrans;

	return RESULT_NONE;
}

void CM2::OnRender()
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

void CM2::OnRelease()
{
}

