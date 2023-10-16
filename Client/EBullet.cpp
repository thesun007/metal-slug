#include "stdafx.h"
#include "EBullet.h"
#include "Include.h"

CEBullet::CEBullet( D3DXVECTOR3 _pos, wstring _secondkey, DIRECTION _dir)
{
	m_tInfo.vPos = _pos;
	m_tKey.eDir = _dir;
	m_tKey.szSecondKey = _secondkey;
}


CEBullet::~CEBullet()
{
}

HRESULT CEBullet::OnInit()
{
	m_tFrame.iFrame = 0;
	m_tFrame.fFrameTime = 0.05f;
	m_tFrame.fFrameTimeNow = 0;
	m_tKey.szRenderKey = L"Sword";
	m_eLayer = LAYER_BULLET;

	m_tInfo.vCenter = D3DXVECTOR3(50, 50, 0);
	m_tInfo.vSize = D3DXVECTOR2(20, 20);

	m_fTime = 0.f;

	m_byState = STATE_NONE;
	return S_OK;
}

int CEBullet::OnUpdate()
{
	//적 맞췄을때 추가
	if ((m_byState & STATE_DIE) == 0)
	{
		if (!SINGLE(CObjMgr)->GetObjectList(L"1.Tarma")->empty())
		{
			if (SINGLE(CCollisionMgr)->ColRect(GetRect().front(),
				SINGLE(CObjMgr)->GetObjectList(L"1.Tarma")->front()))
			{
				SINGLE(CObjMgr)->GetObjectList(L"1.Tarma")->front()->SetHp(-1);
				return RESULT_OBJECT_DELETE;
			}
		}
	}

	if (m_tKey.szSecondKey == L"Sword" || m_tKey.szSecondKey == L"Landing")
	{
		if ((m_byState & STATE_DIE) == 0)
		{
			m_fTimeNow += DeltaTime;
			if (m_fTimeNow >= 0.015f)
			{
				m_fTime += 0.1f;
				m_tInfo.vPos.y += -sinf(90 * PI / 180) * 2.5f + (0.98f * m_fTime) / 2;
				m_fTimeNow -= 0.015f;
			}

			if (m_tKey.eDir == DIRECTION_LEFT)
			{
				if(rand()%2 ==0)
					m_tInfo.vPos.x -= DeltaTime * 45;
				else
					m_tInfo.vPos.x -= DeltaTime * 35;
			}
			else
			{
				if (rand() % 2 == 0)
				m_tInfo.vPos.x += DeltaTime * 45;
				else
					m_tInfo.vPos.x += DeltaTime * 35;
			}
			
			if (SINGLE(CCollisionMgr)->ColLine(*m_plistLine, m_tInfo.vPos))
			{
				m_byState = STATE_DIE;
				ChangeAnimation(L"Landing");
			}
		}

		FrameEnd = FrameMove();

		if (m_byState & STATE_DIE)
		{
				++m_iDeathCount;
				if ((m_iDeathCount / 10) % 2 == 0)
					m_iAlpha = 1;
				else
					m_iAlpha = 2;
				if(m_iDeathCount >200)
					return RESULT_OBJECT_DELETE;
			
		}

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

	return RESULT_OBJECT_DELETE;
}

void CEBullet::OnRender()
{
	const TEXINFO* pTex = SINGLE(CTextureMgr)->GetTexture(
		m_tKey.szRenderKey, m_tKey.szSecondKey, m_tFrame.iFrame);
	if (pTex == 0)
		return;
	SINGLE(CDevice)->GetSprite()->SetTransform(&m_tInfo.matWorld);
	SINGLE(CDevice)->GetSprite()->Draw(
		pTex->pTexture, NULL, &m_tInfo.vCenter, 0,
		D3DCOLOR_ARGB(255/m_iAlpha, 255, 255, 255));
}

void CEBullet::OnRelease()
{
}

