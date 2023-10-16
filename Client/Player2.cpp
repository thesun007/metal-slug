#include "stdafx.h"
#include "Player2.h"
#include "Include.h"

CPlayer2::CPlayer2()
	:MoveTime(true)
{
}


CPlayer2::~CPlayer2()
{
}

HRESULT CPlayer2::OnInit()
{
	m_tFrame.iFrame = 0;
	m_tFrame.fFrameTime = 0.05f;
	m_tFrame.fFrameTimeNow = 0;
	m_tKey.szRenderKey = L"TarmaLeg";
	m_tKey.szSecondKey = L"Jump";
	m_tKey.eDir = DIRECTION_RIGHT;
	m_tKey.Option = L"";
	m_eLayer = LAYER_OBJECT2;
	m_tInfo.vPos = D3DXVECTOR3(0, 7, 0);
	m_tInfo.vCenter = D3DXVECTOR3(45,60, 0);

	m_byState = STATE_NONE;
	m_bJump = true; 
	m_bMove = false;
	return S_OK;
}

int CPlayer2::OnUpdate()
{
	//상체 DIE 상태 일때, 삭제
	if (SINGLE(CObjMgr)->GetObjectList(L"1.Tarma")->front()->GetState() & STATE_DIE)
		return RESULT_OBJECT_DELETE;

	// 모션 결정 (투명, walk, stand)
	if (!m_bJump)
	{
		if (PUSHKEY(DIK_DOWNARROW) && UPKEY(DIK_UPARROW))
		{
			ChangeAnimation(L"");
			FrameOne = true;
			m_byState |= STATE_DOWN;
		}
		else if (UPKEY(DIK_DOWNARROW) && (m_byState & STATE_DOWN))
		{
			ChangeAnimation(L"");
			FrameOne = true;
			m_byState ^= STATE_DOWN;
		}

		if (PUSHKEY(DIK_DOWNARROW) && PUSHKEY(DIK_UPARROW) ||
			UPKEY(DIK_DOWNARROW) && UPKEY(DIK_UPARROW))
		{
			if (m_byState & STATE_DOWN)
			{
				ChangeAnimation(L"");
				FrameOne = true;
				m_byState ^= STATE_DOWN;	
			}
		}

		if ((PUSHKEY(DIK_LEFTARROW) && UPKEY(DIK_RIGHTARROW)) ||
			(PUSHKEY(DIK_RIGHTARROW) && UPKEY(DIK_LEFTARROW)))
		{
			if ((m_byState & STATE_DOWN) == 0)
			{
				if (SINGLE(CObjMgr)->GetObjectList(L"1.Tarma")->front()->GetKey().szSecondKey != L"TurnR")
				{
					ChangeAnimation(L"Walk");
					m_tFrame.fFrameTime = 0.048f;
					FrameOne = false;
				}
				else
				{
					ChangeAnimation(L"");
					FrameOne = true;
				}
			}
			m_bMove = true;
		}
		else
		{
			if ((m_byState & STATE_DOWN) == 0)
			{
				if (SINGLE(CObjMgr)->GetObjectList(L"1.Tarma")->front()->GetKey().szSecondKey != L"Stop")
				{
					ChangeAnimation(L"Stand");
					FrameOne = false;
				}
				else
				{
					ChangeAnimation(L"");
					FrameOne = true;
				}
			}
			m_bMove = false;
		}
	}

	//점프 모션 결정 (점프, 대각 점프)
	if (((CPlayer*)SINGLE(CObjMgr)->GetObjectList(L"1.Tarma")->front())
		->GetJump() == true)
	{
		if (!m_bJump)
		{
			if (!m_bMove)
			{
				ChangeAnimation(L"Jump");
				m_tFrame.fFrameTime = 0.06f;
				FrameOne = true;
			}
			else
			{
				ChangeAnimation(L"FrontJump");
				m_tFrame.fFrameTime = 0.1f;
				FrameOne = true;
			}

			if (!MoveTime)
			{
				m_tInfo.vPos.y -= 2;
				MoveTime = true;
			}
			m_bJump = true;
		}
	}
	else
		m_bJump = false;

	//위치 보정
	if (!m_bJump)
	{
		if ((PUSHKEY(DIK_LEFTARROW) && (UPKEY(DIK_RIGHTARROW))) ||
			(PUSHKEY(DIK_RIGHTARROW) && UPKEY(DIK_LEFTARROW)))
		{
			if (MoveTime && SINGLE(CObjMgr)->GetObjectList(L"1.Tarma")->front()->GetKey().szSecondKey != L"TurnR" 
				&& ((m_byState & STATE_DOWN) == 0))
			{
				m_tInfo.vPos.y += 2;
				MoveTime = false;
			}
		}
		if ((PUSHKEY(DIK_LEFTARROW) && (PUSHKEY(DIK_RIGHTARROW))) ||
			(UPKEY(DIK_RIGHTARROW) && UPKEY(DIK_LEFTARROW)))
		{
			if (!MoveTime)
			{
				m_tInfo.vPos.y -= 2;
				MoveTime = true;
			}
		}
	}
	
	//텍스쳐 프레임 진행
	if (FrameOne)
		FrameEnd = FrameMoveone();
	else
		FrameEnd = FrameMove();
	
	//----------------------------객체 이동 적용----------------------
	D3DXMATRIX matTrans;
	D3DXMatrixTranslation(&matTrans,
		m_tInfo.vPos.x,
		m_tInfo.vPos.y,
		m_tInfo.vPos.z);
	//상체 행렬을 부모로 적용
	m_tInfo.matWorld =  matTrans * (*m_pParentWorld);
	return RESULT_NONE;
}

void CPlayer2::OnRender()
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

void CPlayer2::OnRelease()
{
}
