#include "stdafx.h"
#include "BBullet.h"
#include "Include.h"

CBBullet::CBBullet(D3DXVECTOR3 _pos,  wstring _renderkey, DIRECTION _dir)
	:FrameEnd(false), FrameOne(false),FrameReverse(false), FrameStack(0)
{
	m_vPos = _pos;
	m_tKey.szRenderKey = _renderkey;
	m_tKey.eDir = _dir;
}


CBBullet::~CBBullet()
{
}

void CBBullet::CreateBlast()
{
	CObj* blast = new CStomEffect(m_tKey.eDir);
	((CStomEffect*)blast)->SetParentObj(this);
	blast->SetLine(m_plistLine);
	SINGLE(CObjMgr)->PushObject(L"2.Effect", blast);
}

HRESULT CBBullet::OnInit()
{
	m_tFrame.iFrame = 0;
	m_tFrame.fFrameTime = 0.07f;
	m_tFrame.fFrameTimeNow = 0;
	m_tKey.szSecondKey = L"Normal";
	m_eLayer = LAYER_BULLET;

	if (m_tKey.szRenderKey == L"Door")
		m_tInfo.vCenter = D3DXVECTOR3(50, 50, 0);
	else if (m_tKey.szRenderKey == L"Booster")
	{
		m_tInfo.vCenter = D3DXVECTOR3(40, 4, 0);
		CreateBlast();
	}
	m_tInfo.vSize = D3DXVECTOR2(0, 0);

	m_byState = STATE_NONE;

	AttackTimeNow = 0.f;
	AttackTime = 7.5f;
	GenTimeNow = 0.f;
	GenTime = 2.f;
	return S_OK;
}

int CBBullet::OnUpdate()
{
	m_tInfo.vPos = m_pParent->GetInfo().vPos + m_vPos;
	AttackTimeNow += DeltaTime;		//공격 지속시간 체크

	if (!SINGLE(CObjMgr)->GetObjectList(L"1.Tarma")->empty())
	{
		if (SINGLE(CCollisionMgr)->ColRect(GetRect().front(),
			SINGLE(CObjMgr)->GetObjectList(L"1.Tarma")->front()))
		{
			SINGLE(CObjMgr)->GetObjectList(L"1.Tarma")->front()->SetHp(-20);
		}
	}

	if (m_tKey.szRenderKey == L"Door" && m_pParent->GetState() &STATE_ATTACK &&
		((CBoss*)m_pParent)->GetLevel() ==1)
	{
		if (m_tKey.szSecondKey == L"Normal")
		{
			if (AttackTimeNow >= AttackTime)
			{
				m_byState = STATE_ATTACK;
				ChangeAnimation(L"Open");
				FrameReverse = false;
				FrameOne = true;
				AttackTimeNow = 0.f;
			}
		}
		else if (m_tKey.szSecondKey == L"Open" && !FrameReverse)
		{
			if (AttackTimeNow >= AttackTime*2)
			{
				m_byState = STATE_NONE;
				ChangeAnimationR(L"Open");
				FrameReverse = true;
				FrameOne = true;
				GenTimeNow = 0.f;
			}
			else
			{
				GenTimeNow += DeltaTime;
				if (GenTimeNow >= GenTime)
				{
					GenTimeNow -= GenTime;
					if (rand() % 2 == 0)
					{
						CObj* enemy = new CArabian;
						enemy->SetLine(m_plistLine);
						enemy->SetPos(D3DXVECTOR3(m_tInfo.vPos.x-17, m_tInfo.vPos.y+6, 0));
						((CArabian*)enemy)->SetLevel(rand() % 3 + 1);
						enemy->GetKey().eDir = DIRECTION_LEFT;
						((CArabian*)enemy)->SetAi();
						SINGLE(CObjMgr)->PushObject(L"1.Enemy", enemy);
					}
					else
					{
						CObj* enemy = new CArabian;
						enemy->SetLine(m_plistLine);
						enemy->SetPos(D3DXVECTOR3(m_tInfo.vPos.x +20, m_tInfo.vPos.y+ 6, 0));
						((CArabian*)enemy)->SetLevel(rand() % 3 + 1);
						enemy->GetKey().eDir = DIRECTION_RIGHT;
						((CArabian*)enemy)->SetAi();
						SINGLE(CObjMgr)->PushObject(L"1.Enemy", enemy);
					}
				}
			}
		}
		else if (m_tKey.szSecondKey == L"Open" && FrameReverse)
		{
			if (FrameEnd)
			{
				AttackTimeNow = 0.f;
				ChangeAnimation(L"Normal");
			}
		}
	}
	else if (m_tKey.szRenderKey == L"Door" && ((CBoss*)m_pParent)->GetLevel() == 2)
	{
		m_byState = STATE_NONE;
		ChangeAnimationR(L"Open");
		FrameReverse = true;
		FrameOne = true;
		GenTimeNow = 0.f;
		if (FrameEnd)
			return RESULT_OBJECT_DELETE;
	}

	else if (m_tKey.szRenderKey == L"Booster" &&
		((CBoss*)m_pParent)->GetLevel() == 2)
	{
		if (((CBoss*)m_pParent)->GetHp() < 0)
			return RESULT_OBJECT_DELETE;

		if ((m_pParent->GetState() &STATE_ATTACK) == 0)
		{
			if (m_tKey.szSecondKey == L"Attack")
			{
				ChangeAnimation(L"Normal");
				m_tInfo.vSize = D3DXVECTOR2(0, 0);
				CObj* effect = new CEffect(LAYER_EFFECT2);
				effect->SetPos(D3DXVECTOR3(m_tInfo.vPos.x, m_tInfo.vPos.y, 0));
				effect->SetRenderKey(L"Booster");
				effect->SetCenter(D3DXVECTOR3(40, 4, 0));
				effect->GetKey().eDir = m_tKey.eDir;
				SINGLE(CObjMgr)->PushObject(L"2.Effect", effect);
				m_byState = STATE_NONE;
			}
		}
		else
		{
			if (m_tKey.szSecondKey == L"Normal")
			{
				ChangeAnimation(L"Ready1");
				FrameReverse = false;
				FrameOne = true;
			}
			else if (m_tKey.szSecondKey == L"Ready1" &&FrameEnd)
			{
				ChangeAnimation(L"Ready2");
				FrameReverse = false;
				FrameOne = false;
			}
			else if (m_tKey.szSecondKey == L"Ready2")
			{
				if (FrameEnd)
					++FrameStack;
				if (FrameStack > 7 && !SINGLE(CObjMgr)->GetObjectList(L"1.Tarma")->empty())
				{
					FrameStack = 0;
					ChangeAnimation(L"Ready3");
					FrameReverse = false;
					FrameOne = true;
				}
			}
			else if (m_tKey.szSecondKey == L"Ready3" &&FrameEnd)
			{
				m_byState = STATE_ATTACK;
				ChangeAnimation(L"Attack");
				FrameReverse = false;
				FrameOne = false;
				m_tInfo.vSize = D3DXVECTOR2(20, 250);
			}
			else if (m_tKey.szSecondKey == L"Attack")
			{
				if (SINGLE(CObjMgr)->GetObjectList(L"1.Tarma")->empty())
				{
					ChangeAnimation(L"Normal");
					m_tInfo.vSize = D3DXVECTOR2(0, 0);
					CObj* effect = new CEffect(LAYER_EFFECT2);
					effect->SetPos(D3DXVECTOR3(m_tInfo.vPos.x, m_tInfo.vPos.y, 0));
					effect->SetCenter(D3DXVECTOR3(40, 4, 0));
					effect->SetRenderKey(L"Booster");
					effect->GetKey().eDir = m_tKey.eDir;
					SINGLE(CObjMgr)->PushObject(L"2.Effect", effect);
				}
			}
		}
	}

	//프레임
	if (!FrameReverse)
	{
		if (FrameOne)
			FrameEnd = FrameMoveone();
		else
			FrameEnd = FrameMove();
	}
	else
	{
		FrameEnd = FrameMoveReverse();
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

void CBBullet::OnRender()
{
	const TEXINFO* pTex = SINGLE(CTextureMgr)->GetTexture(
		m_tKey.szRenderKey, m_tKey.szSecondKey, m_tFrame.iFrame);
	if (pTex == 0)
		return;
	SINGLE(CDevice)->GetSprite()->SetTransform(&m_tInfo.matWorld);
	SINGLE(CDevice)->GetSprite()->Draw(
		pTex->pTexture, NULL, &m_tInfo.vCenter, 0,
		D3DCOLOR_ARGB(255 / m_iAlpha, 255, 255, 255));
}

void CBBullet::OnRelease()
{
}
