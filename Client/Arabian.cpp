#include "stdafx.h"
#include "Arabian.h"
#include "Include.h"

CArabian::CArabian()
	:FrameEnd(false), FrameOne(false), FrameReverse(false), Landing(false)
{ 
	m_pAI = new CWait;
	m_tKey.eDir = DIRECTION_LEFT;
}


CArabian::~CArabian()
{
	OnRelease();
}

void CArabian::CreateBullet(D3DXVECTOR3 pos, wstring name)
{
	CObj* bullet = new CEBullet(pos, name, m_tKey.eDir);
	bullet->SetLine(m_plistLine);
	SINGLE(CObjMgr)->PushObject(L"0.Bullet", bullet);
}

void CArabian::EJump()
{
	m_fTimeNow += DeltaTime;
	if (m_fTimeNow >= 0.009f)
	{
		m_fTime += 0.1f;
		m_tInfo.vPos.y += -sinf(90 * PI / 180) * m_fV + (0.98f * m_fTime) / 2;
		m_fTimeNow -= 0.009f;
	}

	if (m_tKey.eDir == DIRECTION_LEFT)
	{
		if(m_tKey.szSecondKey == L"Jump")
			m_tInfo.vPos.x -= DeltaTime *5;
		else if(m_tKey.szSecondKey == L"BackStep")
			m_tInfo.vPos.x += DeltaTime * 110;
	}
	else
	{
		if (m_tKey.szSecondKey == L"Jump")
			m_tInfo.vPos.x += DeltaTime * 5;
		else if(m_tKey.szSecondKey == L"BackStep")
			m_tInfo.vPos.x -= DeltaTime * 110;
	}
}

void CArabian::Motion()
{
	if (!m_bJump && (m_byState & STATE_ATTACK) == 0 &&m_pPlayer !=NULL)
	{
		if (m_pPlayer->GetInfo().vPos.x < m_tInfo.vPos.x)
		{
			if (m_tKey.eDir == DIRECTION_RIGHT)
			{
				m_tKey.eDir = DIRECTION_LEFT;
				ChangeAnimationR(L"TurnR");
				FrameReverse = true;
				FrameOne = true;
			}
		}
		else
		{
			if (m_tKey.eDir == DIRECTION_LEFT)
			{
				m_tKey.eDir = DIRECTION_RIGHT;
				ChangeAnimation(L"TurnR");
				FrameReverse = false;
				FrameOne = true;
			}
		}
	}

	//모션 AI
	if (m_tKey.szSecondKey != L"TurnR" ||
		((m_tKey.szSecondKey == L"TurnR") && FrameEnd))
		m_pAI = m_pAI->OnUpdate(this);
	 

	if (m_tKey.szSecondKey == L"Attack" || m_tKey.szSecondKey == L"Throwing")
		m_byState |= STATE_ATTACK;
	else if ((m_byState & STATE_ATTACK) &&
		(m_tKey.szSecondKey != L"Attack" && m_tKey.szSecondKey != L"Throwing"))
		m_byState ^= STATE_ATTACK;
}

void CArabian::Action()
{
	if (m_tKey.szSecondKey == L"Jump" && m_tFrame.iFrame==6)		//점프일때
	{
		if (!m_bJump)
		{
			m_fTime = 0.f;
			m_fTimeNow = 0.f;
			m_fV = 0.8f;
			m_bJump = true;
		}
	}

	if (m_tKey.szSecondKey == L"BackStep")	//백스탭일때
	{
		if (!m_bJump)
		{
			m_fTime = 0.f;
			m_fTimeNow = 0.f;
			m_fV = 1.5f;
			m_bJump = true;
		}
	}

	if (m_tKey.szSecondKey == L"Shuffle")	//셔플일때
	{
		if (shuffle == 0)
		{
			if (rand() % 2 == 0)
			{
				m_tInfo.vPos.x -= DeltaTime * 8;
				shuffle = 1;
			}
			else
			{
				m_tInfo.vPos.x += DeltaTime * 8;
				shuffle = 2;
			}
		}
		else if (shuffle == 1)
		{
			m_fNowTime += DeltaTime;
			if (m_fNowTime < m_fWaitTime)
			{
				m_tInfo.vPos.x -= DeltaTime * 8;
			}
			else
			{
				shuffle = 2;
				m_fNowTime = 0.f;
			}
		}
		else if (shuffle == 2)
		{
			m_fNowTime += DeltaTime;
			if (m_fNowTime < m_fWaitTime)
			{
				m_tInfo.vPos.x += DeltaTime * 8;
			}
			else
			{
				shuffle = 1;
				m_fNowTime = 0.f;
			}
		}
	}
	else if (m_tKey.szSecondKey != L"Shuffle" && shuffle != 0)
	{
		shuffle = 0;
		m_fNowTime = 0.f;
	}

	if (m_tKey.szSecondKey == L"Run")	//달리기
	{
		if (m_tKey.eDir == DIRECTION_LEFT)
		{
			m_tInfo.vPos.x -= DeltaTime * 120;
		}
		else
		{
			m_tInfo.vPos.x += DeltaTime * 120;
		}
	}
}

void CArabian::Attack()
{
	int d;
	if (m_tKey.eDir == DIRECTION_LEFT)
		d = -1;
	else
		d = 1;

	if (m_tKey.szSecondKey == L"Throwing")
	{
		if (m_tFrame.iFrame == 0)
			m_bShot = true;
		else if (m_tFrame.iFrame == 7)
		{
			if (m_bShot)
			{
				CreateBullet(D3DXVECTOR3(m_tInfo.vPos.x + 10 * d, m_tInfo.vPos.y - 20, 0),L"Sword");
				m_bShot = false;
			}
		}
	}
	else if (m_tKey.szSecondKey == L"Attack")
	{
		if (m_tFrame.iFrame == 0)
			m_bShot = true;
		else if (m_tFrame.iFrame == 10)
		{
			if (m_bShot)
			{
				CreateBullet(D3DXVECTOR3(m_tInfo.vPos.x + 42 * d, m_tInfo.vPos.y , 0),L"");
				m_bShot = false;
			}
		}
	}
}

HRESULT CArabian::OnInit()
{
	m_tFrame.iFrame = 0;
	m_tFrame.fFrameTime = 0.085f;
	m_tFrame.fFrameTimeNow = 0;
	m_tKey.szRenderKey = L"Arabian";
	m_tKey.szSecondKey = L"Prepare";
	m_tKey.Option = L"";

	m_bMove = false;
	m_byState = STATE_NONE;
	m_eLayer = LAYER_OBJECT;

	m_tInfo.vCenter = D3DXVECTOR3(60, 50, 0);
	m_tInfo.vSize = D3DXVECTOR2(10, 30);
	m_iFootposY = 23;
	m_iHp = 1;

	m_bJump = false;
	m_fV = 0.f;
	m_fTime = 0.f;

	shuffle = 0;
	m_fNowTime = 0.f;
	m_fWaitTime = 1.f;

	return S_OK;
}

int CArabian::OnUpdate()
{
	//평소
	if (m_iHp >0)
	{
		//모션 결정
		Motion();

		//실제 이동
		Action();

		//공격
		Attack();
	}
	//죽음 모션 적용
	else
	{
		if ((m_byState & STATE_DIE)==0)
		{
			if (m_bJump || m_iHp<-15 || rand() % 2 == 0)
			{
				ChangeAnimation(L"Death2");
				SetFrame(false, true);
			}
			else
			{
				ChangeAnimation(L"Death1");
				SetFrame(false, true);
			}
			m_byState = STATE_DIE;
		}
	}

	//텍스쳐 프레임 진행
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

	//죽은 상태일 때, 깜박거림 후  삭제
	if (m_byState & STATE_DIE)
	{
		if (m_tKey.szSecondKey == L"Death1" && m_tFrame.iFrame > 15)
		{
			++m_iDeathCount;
			if ((m_iDeathCount / 10) % 2 == 0)
				m_iAlpha = 1;
			else
				m_iAlpha = 2;
			if (m_iDeathCount > 200)
				return RESULT_OBJECT_DELETE;
		}
		else if (m_tKey.szSecondKey == L"Death2" &&FrameEnd)
			return RESULT_OBJECT_DELETE;
	}

	//--------------------점프, 라인충돌(바닥)--------------------------
	if ((m_byState & STATE_DIE) == 0)
	{
		if (m_bJump)
			EJump();

		if (!(m_tKey.szSecondKey == L"Jump" && m_tFrame.iFrame < 10))
			Landing = LineCol();
	}

	//------------------객체 이동 적용---------------------------------
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

void CArabian::OnRender()
{
	const TEXINFO* pTex = SINGLE(CTextureMgr)->GetTexture(
		m_tKey.Option + m_tKey.szRenderKey, m_tKey.szSecondKey, m_tFrame.iFrame);
	if (pTex == 0)
		return;
	SINGLE(CDevice)->GetSprite()->SetTransform(&m_tInfo.matWorld);
	SINGLE(CDevice)->GetSprite()->Draw(
		pTex->pTexture, NULL, &m_tInfo.vCenter, 0,
		D3DCOLOR_ARGB(255/m_iAlpha, 255, 255, 255));
}

void CArabian::OnRelease()
{
}
