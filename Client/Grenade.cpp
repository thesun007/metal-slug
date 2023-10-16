#include "stdafx.h"
#include "Grenade.h"
#include "Include.h"


CGrenade::CGrenade(D3DXVECTOR3 pos)
{
	if (SINGLE(CObjMgr)->GetObjectList(L"1.Tarma")->front()->GetKey().eDir == DIRECTION_LEFT)
		m_fAngle = 135.f;
	else
		m_fAngle = 45.f;
	m_tInfo.vPos = pos;
}

CGrenade::~CGrenade()
{
	OnRelease();
}

HRESULT CGrenade::OnInit()
{
	m_tFrame.iFrame = 0;
	m_tFrame.fFrameTime = 0.015f;
	m_tFrame.fFrameTimeNow = 0;
	m_tKey.szRenderKey = L"Grenade";
	m_tKey.szSecondKey = L"Grenade";

	if (SINGLE(CObjMgr)->GetObjectList(L"1.Tarma")->front()->GetKey().eDir == DIRECTION_LEFT)
		m_tKey.eDir = DIRECTION_LEFT;
	else
		m_tKey.eDir = DIRECTION_RIGHT;
	m_eLayer = LAYER_BULLET;

	m_tInfo.vCenter = D3DXVECTOR3(20, 20, 0);
	m_tInfo.vSize = D3DXVECTOR2(10, 10);

	m_fV = 1.7f;
	m_fTime = 0;
	m_iBounce = 0;

	m_byState = STATE_NONE;
	return S_OK;
}

int CGrenade::OnUpdate()
{
	if ((m_byState & STATE_ATTACK) == 0 && (m_byState & STATE_DIE) == 0)
	{
		m_fTimeNow += DeltaTime;
		if (m_fTimeNow >= 0.009f)
		{
			m_fTime += 0.1f;
			m_tInfo.vPos.x += cosf(D3DXToRadian(m_fAngle))*1.6f;
			m_tInfo.vPos.y += -sinf(m_fAngle * PI / 180) * m_fV + (0.98f * m_fTime) / 2;
			m_fTimeNow -= 0.009f;
		}

		if (m_tInfo.vPos.x < SINGLE(CCamMgr)->GetCamPos().x ||
			m_tInfo.vPos.x > SINGLE(CCamMgr)->GetCamPos().x + 310 ||
			m_tInfo.vPos.y < SINGLE(CCamMgr)->GetCamPos().y - 10)
			m_byState = STATE_DIE;

		if (SINGLE(CCollisionMgr)->ColLine(*m_plistLine, m_tInfo.vPos))	//땅에 닿을 경우
		{
			++m_iBounce;
			m_fV = 2.2f;		// 낮은 높이로 한번 더 튀어오름
			m_fTime = 0;
			m_tFrame.fFrameTime = 0.05f;	//회전 속도 감소

			if (m_iBounce == 2)		// 두번째 닿았을 경우 폭파
			{
				m_byState = STATE_ATTACK;
				ChangeAnimation(L"GrenadeEffect");
				m_tFrame.fFrameTime = 0.025f;
				m_tInfo.vPos.y -= 47.5f;
				m_tInfo.vCenter = D3DXVECTOR3(50, 60, 0);
			}
		}

		// 적 맞췄을때 추가
		if (SINGLE(CObjMgr)->GetObjectList(L"1.Enemy") != NULL)
		{
			for (auto iter = (*SINGLE(CObjMgr)->GetObjectList(L"1.Enemy")).begin();
				iter != SINGLE(CObjMgr)->GetObjectList(L"1.Enemy")->end(); ++iter)
			{
				if (SINGLE(CCollisionMgr)->ColRect(GetRect()[0], *iter))
				{
					m_byState = STATE_ATTACK;
					ChangeAnimation(L"GrenadeEffect");
					m_tFrame.fFrameTime = 0.025f;
					m_tInfo.vPos.y -= 47.5f;
					m_tInfo.vCenter = D3DXVECTOR3(50, 60, 0);
					break;
					
				}
			}
		}
	}
	else if((m_byState & STATE_DIE) == 0)
	{
		if (m_tKey.szSecondKey == L"GrenadeEffect" && m_tFrame.iFrame == 6)
		{
			m_tInfo.vSize = D3DXVECTOR2(40, 120);
		}

		if (m_tKey.szSecondKey == L"GrenadeEffect" && m_tFrame.iFrame > 16)
		{
			m_byState = STATE_DIE;
		}

		// 폭발상태에서 적 맞췄을 때
		if (m_tInfo.vSize == D3DXVECTOR2(40, 120))
		{
			if (SINGLE(CObjMgr)->GetObjectList(L"1.Enemy") != NULL)
			{
				for (auto iter = (*SINGLE(CObjMgr)->GetObjectList(L"1.Enemy")).begin();
					iter != SINGLE(CObjMgr)->GetObjectList(L"1.Enemy")->end(); ++iter)
				{
					if (SINGLE(CCollisionMgr)->ColRect(GetRect()[0], *iter))
					{
						(*iter)->SetHp(-20);
						m_byState = STATE_DIE;
					}
				}
			}
		}
	}

	FrameEnd = FrameMove();
	if (FrameEnd)
	{
		if (m_tKey.eDir == DIRECTION_RIGHT)
			m_tKey.eDir = DIRECTION_LEFT;

		else
			m_tKey.eDir = DIRECTION_RIGHT;
	}

	if (m_byState & STATE_DIE)
	{
		if (FrameEnd)
			return RESULT_OBJECT_DELETE;
	}

	D3DXMATRIX matTrans, matScale;

	if (m_tKey.eDir == DIRECTION_RIGHT)
		D3DXMatrixScaling(&matScale, 1, 1, 1);
	else if(m_tKey.eDir == DIRECTION_LEFT && m_tKey.szSecondKey == L"Grenade")
		D3DXMatrixScaling(&matScale, -1, -1, 1);
	else
		D3DXMatrixScaling(&matScale, -1, 1, 1);

	D3DXMatrixTranslation(&matTrans,
		m_tInfo.vPos.x - SINGLE(CCamMgr)->GetCamPos().x,
		m_tInfo.vPos.y - SINGLE(CCamMgr)->GetCamPos().y,
		m_tInfo.vPos.z);

	m_tInfo.matWorld = matScale * matTrans;
	return RESULT_NONE;
}

void CGrenade::OnRender()
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

void CGrenade::OnRelease()
{
}

