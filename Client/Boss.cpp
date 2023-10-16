#include "stdafx.h"
#include "Boss.h"
#include "Include.h"
#include "BossReady.h"

CBoss::CBoss()
	:FrameEnd(false), FrameOne(false), FrameReverse(false), Landing(false), MoveTimeNow(0.f),
	death(false), dontmove(false)
{
}


CBoss::~CBoss()
{
	OnRelease();
}

vector<RECT> CBoss::GetRect()
{
	vector<RECT> vecRect;
	RECT	rt =
	{
		int(m_tInfo.vPos.x - m_tInfo.vSize.x / 2.f),
		int(m_tInfo.vPos.y - m_tInfo.vSize.y / 2.f),
		int(m_tInfo.vPos.x + m_tInfo.vSize.x / 2.f),
		int(m_tInfo.vPos.y + m_tInfo.vSize.y / 2.f)
	};
	vecRect.push_back(rt);
	rt =
	{
		int((m_tInfo.vPos.x-95) - 45),
		int(m_tInfo.vPos.y - 20),
		int((m_tInfo.vPos.x-95) + 45),
		int(m_tInfo.vPos.y + 20)
	};
	vecRect.push_back(rt);
	rt =
	{
		int((m_tInfo.vPos.x + 95) - 45),
		int(m_tInfo.vPos.y - 20),
		int((m_tInfo.vPos.x + 95) + 45),
		int(m_tInfo.vPos.y + 20)
	};
	vecRect.push_back(rt);
	return vecRect;
}

void CBoss::CreateBullet()
{
	m_pBooster1 = new CBBullet(D3DXVECTOR3(-89, 39, 0), L"Booster", DIRECTION_LEFT);
	m_pBooster1->SetLine(m_plistLine);
	((CBBullet*)m_pBooster1)->SetParent(this);
	SINGLE(CObjMgr)->PushObject(L"0.BossBullet", m_pBooster1);

	m_pBooster2 = new CBBullet(D3DXVECTOR3(88, 39, 0), L"Booster", DIRECTION_RIGHT);
	m_pBooster2->SetLine(m_plistLine);
	((CBBullet*)m_pBooster2)->SetParent(this);
	SINGLE(CObjMgr)->PushObject(L"0.BossBullet", m_pBooster2);

	m_pDoor = new CBBullet(D3DXVECTOR3(0,-62,0),L"Door",DIRECTION_RIGHT);
	m_pDoor->SetLine(m_plistLine);
	((CBBullet*)m_pDoor)->SetParent(this);
	SINGLE(CObjMgr)->PushObject(L"0.BossBullet", m_pDoor);

	
}

void CBoss::CreateLine()
{
	POINTFLOAT pos;
	m_pline[0] = new LINE;
	pos = { m_tInfo.vPos.x-135,m_tInfo.vPos.y-11 };
	m_pline[0]->tLPoint = pos;
	pos = { m_tInfo.vPos.x - 90,m_tInfo.vPos.y - 12 };
	m_pline[0]->tRPoint = pos;
	m_plistLine->push_back(m_pline[0]);

	m_pline[1] = new LINE;
	m_pline[1]->tLPoint = pos;
	pos.x =  m_tInfo.vPos.x - 35;
	pos.y =  m_tInfo.vPos.y - 25;
	m_pline[1]->tRPoint = pos;
	m_plistLine->push_back(m_pline[1]);

	m_pline[2] = new LINE;
	m_pline[2]->tLPoint = pos;
	pos.x = m_tInfo.vPos.x + 35;
	pos.y = m_tInfo.vPos.y - 25;
	m_pline[2]->tRPoint = pos;
	m_plistLine->push_back(m_pline[2]);

	m_pline[3] = new LINE;
	m_pline[3]->tLPoint = pos;
	pos = { m_tInfo.vPos.x + 90,m_tInfo.vPos.y - 12 };
	m_pline[3]->tRPoint = pos;
	m_plistLine->push_back(m_pline[3]);

	m_pline[4] = new LINE;
	m_pline[4]->tLPoint = pos;
	pos = { m_tInfo.vPos.x + 135,m_tInfo.vPos.y - 11 };
	m_pline[4]->tRPoint = pos;
	m_plistLine->push_back(m_pline[4]);
}

void CBoss::CreateBoom()
{
	if (rand() % 100 < 5)
	{
		CObj* effect = new CEffect(LAYER_EFFECT);
		effect->SetPos(D3DXVECTOR3(m_tInfo.vPos.x-140 + rand()%280, m_tInfo.vPos.y-67 + rand()%135, 0));
		effect->SetCenter(D3DXVECTOR3(30, 40, 0));
		effect->SetRenderKey(L"MediumBoom");
		effect->GetKey().eDir = m_tKey.eDir;
		SINGLE(CObjMgr)->PushObject(L"2.Effect", effect);
	}
}

void CBoss::CreateBigBoom()
{
	CObj* effect = new CEffect(LAYER_EFFECT);
	effect->SetPos(D3DXVECTOR3(m_tInfo.vPos.x-100  , m_tInfo.vPos.y-23 , 0));
	effect->SetCenter(D3DXVECTOR3(50, 70, 0));
	effect->SetRenderKey(L"BigBoom");
	effect->GetKey().eDir = DIRECTION_RIGHT;
	SINGLE(CObjMgr)->PushObject(L"2.Effect", effect);

	effect = new CEffect(LAYER_EFFECT);
	effect->SetPos(D3DXVECTOR3(m_tInfo.vPos.x - 40, m_tInfo.vPos.y + 33, 0));
	effect->SetCenter(D3DXVECTOR3(50, 70, 0));
	effect->SetRenderKey(L"BigBoom");
	effect->GetKey().eDir = DIRECTION_RIGHT;
	SINGLE(CObjMgr)->PushObject(L"2.Effect", effect);

	effect = new CEffect(LAYER_EFFECT);
	effect->SetPos(D3DXVECTOR3(m_tInfo.vPos.x +10, m_tInfo.vPos.y +1, 0));
	effect->SetCenter(D3DXVECTOR3(50, 70, 0));
	effect->SetRenderKey(L"BigBoom");
	effect->GetKey().eDir = DIRECTION_RIGHT;
	SINGLE(CObjMgr)->PushObject(L"2.Effect", effect);

	effect = new CEffect(LAYER_EFFECT);
	effect->SetPos(D3DXVECTOR3(m_tInfo.vPos.x +60, m_tInfo.vPos.y +53, 0));
	effect->SetCenter(D3DXVECTOR3(50, 70, 0));
	effect->SetRenderKey(L"BigBoom");
	effect->GetKey().eDir = DIRECTION_RIGHT;
	SINGLE(CObjMgr)->PushObject(L"2.Effect", effect);

	effect = new CEffect(LAYER_EFFECT);
	effect->SetPos(D3DXVECTOR3(m_tInfo.vPos.x + 120, m_tInfo.vPos.y - 10, 0));
	effect->SetCenter(D3DXVECTOR3(50, 70, 0));
	effect->SetRenderKey(L"BigBoom");
	effect->GetKey().eDir = DIRECTION_RIGHT;
	SINGLE(CObjMgr)->PushObject(L"2.Effect", effect);
}

bool CBoss::Move()
{
	MoveTimeNow += DeltaTime;
	if (MoveTimeNow < MoveTime)
	{
		m_tInfo.vPos.y += DeltaTime * MaxSpeed ;
		Speed = MaxSpeed;
		if (MaxSpeed > 0)
			F = -1;
		else
			F = 1;
	}
	else
	{
		Speed += F;
		m_tInfo.vPos.y += DeltaTime*Speed;
		if (Speed == 0)
		{
			if (m_byState & STATE_UP)
			{
				m_byState ^= STATE_UP;
				m_byState |= STATE_DOWN;
			}
			else if (m_byState & STATE_DOWN)
			{
				m_byState ^= STATE_DOWN;
				m_byState |= STATE_UP;
			}
			if ((m_byState & STATE_ATTACK) == 0)
				MoveTime = 1.4f;
			else if (m_iLevel == 1)
				MoveTime = 1.2f;
			else if(m_iLevel == 2)
				MoveTime = 0.2f;
			MoveTimeNow = 0.f;
		}
	}
	return false;
}

void CBoss::Motion()
{
	m_pAI = m_pAI->OnUpdate(this);

	float hp = (float)m_iHp / m_iMaxHp * 100;
	if (hp < 10)
		m_tFrame.iFrame = 6;
	else if (hp < 20)
		m_tFrame.iFrame = 5;
	else if (hp < 30)
		m_tFrame.iFrame = 4;
	else if(hp < 40)
		m_tFrame.iFrame = 3;
	else if(hp < 50)
		m_tFrame.iFrame = 2;
	else if(hp < 75)
		m_tFrame.iFrame = 1;

	//위,아래 이동 결정
	if ((m_byState & STATE_ATTACK) == 0)
	{
		if(m_byState & STATE_DOWN)
			MaxSpeed = 20;
		else if(m_byState &STATE_UP)
			MaxSpeed = -20;
	}
	else if (m_iLevel == 1)
	{
		if (m_byState & STATE_DOWN)
			MaxSpeed = 10;
		else if (m_byState &STATE_UP)
			MaxSpeed = -10;
	}
	else if (m_iLevel == 2)
	{
		if (m_byState & STATE_DOWN)
			MaxSpeed = 40;
		else if (m_byState &STATE_UP)
			MaxSpeed = -40;
	}
}

void CBoss::Action()
{
	if(m_iLevel !=0 && !dontmove)
		Move();

	if (m_pBooster1->GetKey().szSecondKey == L"Attack"||
		m_pBooster1->GetKey().szSecondKey == L"Ready3")
	{
		if (m_tKey.eDir == DIRECTION_RIGHT)
		{
			if (m_tInfo.vPos.x <= 3745)
			{
				m_tInfo.vPos.x += DeltaTime * 60;
				/*for (int i = 0; i < 5; ++i)
				{
					m_pline[i]->tLPoint.x += DeltaTime * 60;
					m_pline[i]->tRPoint.x += DeltaTime * 60;
				}*/
			}
			else
				m_tKey.eDir = DIRECTION_LEFT;
		}
		else
		{
			if (m_tInfo.vPos.x >= 3568)
			{
				m_tInfo.vPos.x -= DeltaTime * 60;
				/*for (int i = 0; i < 5; ++i)
				{
					m_pline[i]->tLPoint.x -= DeltaTime * 60;
					m_pline[i]->tRPoint.x -= DeltaTime * 60;
				}*/
			}
			else
				m_tKey.eDir = DIRECTION_RIGHT;
		}
	}
}

HRESULT CBoss::OnInit()
{
	m_tFrame.iFrame = 0;
	m_tKey.szRenderKey = L"Boss";
	m_tKey.szSecondKey = L"";
	m_tKey.eDir = DIRECTION_RIGHT;
	m_tKey.Option = L"";

	m_bMove = false;
	m_byState = STATE_NONE;
	m_eLayer = LAYER_OBJECT;

	m_tInfo.vPos = D3DXVECTOR3(3672, -60, 0);
	m_tInfo.vCenter = D3DXVECTOR3(140, 67, 0);
	m_tInfo.vSize = D3DXVECTOR2(90, 105);
	m_iFootposY = 52;

	m_iHp =650;
	m_iMaxHp = 650;
	m_iLevel = 0;

	m_pAI = new CBossWait;

	CreateBullet();
	CreateLine();

	return S_OK;
}

int CBoss::OnUpdate()
{
	if (m_iHp >0)
	{
		Motion();

		//실제 이동
		Action();

		POINTFLOAT pos = { m_tInfo.vPos.x - 135,m_tInfo.vPos.y - 11 };
		m_pline[0]->tLPoint = pos;
		pos = { m_tInfo.vPos.x - 90,m_tInfo.vPos.y - 12 };
		m_pline[0]->tRPoint = pos;

		m_pline[1]->tLPoint = pos;
		pos.x = m_tInfo.vPos.x - 35;
		pos.y = m_tInfo.vPos.y - 25;
		m_pline[1]->tRPoint = pos;


		m_pline[2]->tLPoint = pos;
		pos.x = m_tInfo.vPos.x + 35;
		pos.y = m_tInfo.vPos.y - 25;
		m_pline[2]->tRPoint = pos;


		m_pline[3]->tLPoint = pos;
		pos = { m_tInfo.vPos.x + 90,m_tInfo.vPos.y - 12 };
		m_pline[3]->tRPoint = pos;


		m_pline[4]->tLPoint = pos;
		pos = { m_tInfo.vPos.x + 135,m_tInfo.vPos.y - 11 };
		m_pline[4]->tRPoint = pos;

	}
	else
	{
		CreateBoom();
		if (!death)
		{
			SetMove(0.1f);
			death = true;
		}

		if ((m_byState &STATE_DIE) == 0)
		{
			m_tInfo.vPos.y += DeltaTime * 20;
			MoveTimeNow += DeltaTime;
			if (MoveTimeNow < MoveTime)
			{
				m_tInfo.vPos.x += DeltaTime * 20;
			}
			else if (MoveTimeNow < MoveTime * 2)
			{
				m_tInfo.vPos.x -= DeltaTime * 20;
			}
			else
				MoveTimeNow = 0.f;
			D3DXVECTOR3 pos = D3DXVECTOR3(0, m_iFootposY, 0);
			if (SINGLE(CCollisionMgr)->ColLine(*m_plistLine, m_tInfo.vPos+pos))
			{
				m_byState = STATE_DIE;
				m_tKey.szSecondKey = L"Death";
				m_tFrame.iFrame = 0;
				CreateBigBoom();
				MoveTimeNow = 0.f;
			}
				
		}
		else if (m_byState & STATE_DIE)
		{
			CreateBoom();
			MoveTimeNow += DeltaTime;
			if (MoveTimeNow >= 5)
			{
				CreateBigBoom();
				return RESULT_OBJECT_DELETE;
			}
		}

	}

	D3DXMATRIX matTrans, matScale;

	D3DXMatrixScaling(&matScale, 1, 1, 1);

	D3DXMatrixTranslation(&matTrans,
		m_tInfo.vPos.x - SINGLE(CCamMgr)->GetCamPos().x,
		m_tInfo.vPos.y - SINGLE(CCamMgr)->GetCamPos().y,
		m_tInfo.vPos.z);

	m_tInfo.matWorld = matScale * matTrans;

	return RESULT_NONE;
}

void CBoss::OnRender()
{
	const TEXINFO* pTex = SINGLE(CTextureMgr)->GetTexture(
		m_tKey.Option + m_tKey.szRenderKey, m_tKey.szSecondKey, m_tFrame.iFrame);
	if (pTex == 0)
		return;
	SINGLE(CDevice)->GetSprite()->SetTransform(&m_tInfo.matWorld);
	SINGLE(CDevice)->GetSprite()->Draw(
		pTex->pTexture, NULL, &m_tInfo.vCenter, 0,
		D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CBoss::OnRelease()
{
}
