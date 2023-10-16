#include "stdafx.h"
#include "Bullet.h"
#include "Include.h"

CBullet::CBullet(float _angle, D3DXVECTOR3 _pos,float _angle2)
{
	int d;
	if (SINGLE(CObjMgr)->GetObjectList(L"1.Tarma")->front()->GetKey().eDir == DIRECTION_LEFT)
		d = -1;
	else
		d = 1;
	m_fAngle = _angle;
	m_tInfo.vPos = _pos;
	m_vDir = D3DXVECTOR3(cosf(D3DXToRadian(m_fAngle+_angle2))*d, -sinf(D3DXToRadian(m_fAngle + _angle2)), 0);
}


CBullet::~CBullet()
{
	OnRelease();
}

HRESULT CBullet::OnInit()
{
	m_tFrame.iFrame = 0;
	m_tFrame.fFrameTime = 0.045f;
	m_tFrame.fFrameTimeNow = 0;
	m_tKey.szRenderKey = L"Bullet";
	if (SINGLE(CObjMgr)->GetObjectList(L"1.Tarma")->front()->GetKey().Option == L"H")
		m_tKey.szSecondKey = L"Heavy";
	else
		m_tKey.szSecondKey = L"Pistol";

	if (SINGLE(CObjMgr)->GetObjectList(L"1.Tarma")->front()->GetKey().eDir==DIRECTION_LEFT)
		m_tKey.eDir = DIRECTION_LEFT;
	else
		m_tKey.eDir = DIRECTION_RIGHT;
	m_eLayer = LAYER_BULLET;

	m_tInfo.vCenter = D3DXVECTOR3(50, 50, 0);
	m_tInfo.vSize = D3DXVECTOR2(5, 5);

	m_byState = STATE_NONE;
	return S_OK;
}

int CBullet::OnUpdate()
{
	if ((m_byState & STATE_DIE) == 0)
	{
		m_tInfo.vPos += DeltaTime * m_vDir * 450;

		if (m_tInfo.vPos.x < SINGLE(CCamMgr)->GetCamPos().x-10 ||
			m_tInfo.vPos.x > SINGLE(CCamMgr)->GetCamPos().x + 320||
			m_tInfo.vPos.y < SINGLE(CCamMgr)->GetCamPos().y-20)
			m_byState = STATE_DIE;

		if (SINGLE(CCollisionMgr)->ColLine(*m_plistLine, m_tInfo.vPos))
		{
			m_byState = STATE_DIE;
			ChangeAnimation(L"HitGround");
			m_fAngle = 0.f;
		}

		//적 맞췄을때 추가
		if (SINGLE(CObjMgr)->GetObjectList(L"1.Enemy") != NULL)
		{
			for (auto iter = (*SINGLE(CObjMgr)->GetObjectList(L"1.Enemy")).begin();
				iter != SINGLE(CObjMgr)->GetObjectList(L"1.Enemy")->end(); ++iter)
			{
				if (SINGLE(CCollisionMgr)->ColRect(GetRect()[0], *iter))
				{
					if (m_tKey.szSecondKey == L"Pistol")
					{
						(*iter)->SetHp(-2);
						m_byState = STATE_DIE;
						ChangeAnimation(L"HitEnemy");
						m_fAngle = 0.f;
					}
					else
					{
						(*iter)->SetHp(-1);
						m_byState = STATE_DIE;
						ChangeAnimation(L"HitEnemy");
						m_fAngle = 0.f;
					}
				}
			}
		}
	}

	FrameEnd = FrameMove();

	if (m_byState & STATE_DIE)
	{
		if (FrameEnd)
			return RESULT_OBJECT_DELETE;
	}

	D3DXMATRIX matTrans, matScale, matRot;

	if (m_tKey.eDir == DIRECTION_RIGHT)
	{
		D3DXMatrixRotationZ(&matRot, D3DXToRadian(-m_fAngle));
		D3DXMatrixScaling(&matScale, 1, 1, 1);
	}
	else
	{
		D3DXMatrixRotationZ(&matRot, D3DXToRadian(m_fAngle));
		D3DXMatrixScaling(&matScale, -1, 1, 1);
	}

	D3DXMatrixTranslation(&matTrans,
		m_tInfo.vPos.x - SINGLE(CCamMgr)->GetCamPos().x,
		m_tInfo.vPos.y - SINGLE(CCamMgr)->GetCamPos().y,
		m_tInfo.vPos.z);

	m_tInfo.matWorld = matScale * matRot * matTrans;

	return RESULT_NONE;
}

void CBullet::OnRender()
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

void CBullet::OnRelease()
{
}
