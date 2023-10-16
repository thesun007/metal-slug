#include "stdafx.h"
#include "Item.h"
#include "Include.h"

CItem::CItem(D3DXVECTOR3 _pos, wstring _renderkey)
	:Landing(false)
{
	m_tInfo.vPos = _pos;
	m_tKey.szRenderKey = _renderkey;
}


CItem::~CItem()
{
}

HRESULT CItem::OnInit()
{
	m_tFrame.iFrame = 0;
	m_tFrame.fFrameTime = 0.15f;
	m_tFrame.fFrameTimeNow = 0;
	m_tKey.szSecondKey = L"";
	m_eLayer = LAYER_BULLET;
	m_tInfo.vCenter = D3DXVECTOR3(25, 25, 0);
	m_tInfo.vSize = D3DXVECTOR2(20, 20);
	if(m_tKey.szRenderKey == L"Heavy")
		m_iFootposY = 10;
	else if(m_tKey.szRenderKey == L"Grenade")
		m_iFootposY = 14;

	m_byState = STATE_NONE;

	m_bJump = true;
	m_fV = 0.f;
	m_fTime = 0.f;
	return S_OK;
}

int CItem::OnUpdate()
{
	if ((m_byState &STATE_DIE) == 0)
	{
		if (!SINGLE(CObjMgr)->GetObjectList(L"1.Tarma")->empty())
		{
			//ºÎµúÃÆ´Ù¸é
			if (!m_bJump&&SINGLE(CCollisionMgr)->ColRect(GetRect().front(),
				SINGLE(CObjMgr)->GetObjectList(L"1.Tarma")->front()))
			{
				((CPlayer*)SINGLE(CObjMgr)->GetObjectList(L"1.Tarma")->front())->SetEquip(m_tKey.szRenderKey);
				ChangeAnimation(L"Death");
				m_byState = STATE_DIE;
			}
		}
	}
	else
	{
		++m_iDeathCount;
		if (m_iDeathCount > 20)
			return RESULT_OBJECT_DELETE;
	}

	FrameMove();

	if (m_bJump)
		Jump();
	
	Landing = LineCol();

	D3DXMATRIX matTrans;
	D3DXMatrixTranslation(&matTrans,
		m_tInfo.vPos.x - SINGLE(CCamMgr)->GetCamPos().x,
		m_tInfo.vPos.y - SINGLE(CCamMgr)->GetCamPos().y,
		m_tInfo.vPos.z);
	m_tInfo.matWorld = matTrans;
	
	return RESULT_NONE;
}

void CItem::OnRender()
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

void CItem::OnRelease()
{
}

