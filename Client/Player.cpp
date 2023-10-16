#include "StdAfx.h"
#include "Player.h"
#include "Include.h"

CPlayer::CPlayer(void)
	:Jumptime(true), Attacktime(true), Grenadetime(true), DownTime(true), MoveTime(true),
	FrameEnd(false), FrameOne(false), SitMotion(L"Sit"),
	FrameReverse(false), ShotStack(0), DeathTime(true)
{}

CPlayer::~CPlayer(void)
{
	OnRelease();
}
void CPlayer::CreateBullet(float angle, int d, D3DXVECTOR3 pos)
{
	if (m_tKey.Option == L"H")
		--m_iHBullets;

	D3DXVECTOR3 Pos = m_tInfo.vPos;
	if (m_tKey.Option == L"H" && m_tKey.szSecondKey != L"AttackLookingDown"&&
		m_tKey.szSecondKey != L"AttackLookingDownR"&& m_tKey.szSecondKey != L"AttackLookingUp"&&
		m_tKey.szSecondKey != L"AttackLookingUpR")
	{
		if (m_fHeavyAngle == 2.f)
			m_fHeavyAngle = -2.f;
		else if (m_fHeavyAngle == -2.f)
			m_fHeavyAngle = 0;
		else if (m_fHeavyAngle == 0.f)
			m_fHeavyAngle = 2.f;
	}
	else
		m_fHeavyAngle = 0.f;

	if (m_fHeavyAngle == -2.f)
		Pos.y += 4;
	else
		Pos.y += 2;

	if (pos == D3DXVECTOR3(0, 0, 0))
	{
		pos = D3DXVECTOR3(Pos.x + 30 * cosf(D3DXToRadian(angle))*d,
			Pos.y + (30 * -sinf(D3DXToRadian(angle))), 0);
	}
	CObj* bullet = new CBullet(angle, pos, m_fHeavyAngle);
	bullet->SetLine(m_plistLine);
	SINGLE(CObjMgr)->PushObject(L"0.Bullet", bullet);
}

void CPlayer::CreateGrenade(D3DXVECTOR3 pos)
{
	if (m_iGrenades == 0)
		return;
	--m_iGrenades;
	CObj* grenade = new CGrenade(pos);
	grenade->SetLine(m_plistLine);
	SINGLE(CObjMgr)->PushObject(L"0.Grenade", grenade);
}

void CPlayer::SetEquip(wstring equipment)
{
	if (equipment == L"")
	{
		if(m_byState & STATE_ATTACK)
			m_byState ^= STATE_ATTACK;
		m_tKey.Option = L"";
		m_tInfo.vCenter = D3DXVECTOR3(45, 60, 0);
		m_iHBullets = 0;
		ChangeAnimation(L"StandMotion2");
		SetFrameTime(TIME_LOOK);
		FrameReverse = false;
		FrameOne = false;
		ShotStack = 0;
	}
	if (equipment == L"Heavy")
	{
		m_tKey.Option = L"H";
		m_tInfo.vCenter = D3DXVECTOR3(50, 65, 0);
		m_iHBullets += 150;
		ChangeAnimation(L"Stand");
		SetFrameTime(TIME_STAND);
		FrameReverse = false;
		FrameOne = false;
	}
	if (equipment == L"Grenade")
	{
		m_iGrenades += 8;
	}
}

void CPlayer::Motion()
{
	//점프상태 아닐때
	if (!m_bJump)
	{
		if ((m_byState & STATE_ATTACK) == 0 || m_tKey.Option == L"H")
		{
			if (UPKEY(DIK_DOWNARROW) && PUSHKEY(DIK_UPARROW))     //업키
			{
				if ((m_byState & STATE_UP) == 0)
				{
					if ((m_byState & STATE_ATTACK) == 0)
					{
						ChangeAnimation(L"LookingUp");
						SetFrameTime(TIME_LOOK);
						FrameReverse = false;
						FrameOne = true;
					}
					else if (m_byState & STATE_ATTACK && m_tKey.szSecondKey != L"AttackGrenade"&&
						m_tKey.szSecondKey != L"AttackNife" && m_tKey.szSecondKey != L"AttackNife2")
					{
						ChangeAnimation(L"AttackLookingUp");
						SetFrameTime(TIME_LOOK / 2);
						FrameReverse = false;
						FrameOne = true;
					}
				}
				else
				{
					if (FrameEnd && (m_byState & STATE_ATTACK) == 0)
					{
						ChangeAnimation(L"LookUp");
						SetFrameTime(TIME_STAND);
						FrameReverse = false;
						FrameOne = false;
					}
				}
				m_byState |= STATE_UP;
			}
			if (UPKEY(DIK_UPARROW) && (m_byState & STATE_UP))		//업키 해제
			{
				if ((m_byState & STATE_ATTACK) == 0)
				{
					ChangeAnimationR(L"LookingUp");		//리버스
					SetFrameTime(TIME_LOOK);
					FrameReverse = true;
					FrameOne = true;
				}
				if (m_byState & STATE_ATTACK && m_tKey.szSecondKey != L"AttackGrenade"&&
					m_tKey.szSecondKey != L"AttackNife" && m_tKey.szSecondKey != L"AttackNife2")
				{
					ChangeAnimation(L"AttackLookingUpR");
					SetFrameTime(TIME_LOOK / 2);
					FrameReverse = false;
					FrameOne = true;
				}
				m_byState ^= STATE_UP;

			}
		}

		if (UPKEY(DIK_UPARROW) && PUSHKEY(DIK_DOWNARROW))		//다운키
		{
			if ((m_byState & STATE_DOWN) == 0)	//서있는 중일때
			{
				ChangeAnimation(L"Sitting");	// "앉는 중" 모션 적용
				SetFrameTime(TIME_ACTION);		// 애니메이션 빠르기
				FrameReverse = false;			// 역재생인지
				FrameOne = true;				// 한번재생인지
				SitMotion = L"Sit";				// "일반 앉기"
				if (m_byState & STATE_ATTACK)
					m_byState ^= STATE_ATTACK;
				if (m_byState & STATE_UP)	
					m_byState ^= STATE_UP;
			}
			else
			{
				if (!m_bMove)
				{
					if (m_tKey.szSecondKey == L"Sitting" || (m_byState & STATE_ATTACK)
						|| m_tKey.szSecondKey == L"TurnRSit")	// 앉는 중, 공격 중, 방향 전환 중
					{
						if (FrameEnd)	//현 애니메이션 끝나면 앉기 적용
						{
							ChangeAnimation(SitMotion);
							SetFrameTime(TIME_STAND);
							FrameReverse = false;
							FrameOne = false;
						}
					}
					else		//그 외(이동)일때, 즉시 앉기 적용
					{
						ChangeAnimation(SitMotion);
						SetFrameTime(TIME_STAND);
						FrameReverse = false;
						FrameOne = false;
					}
				}
			}
			m_byState |= STATE_DOWN;
		}
		if (UPKEY(DIK_DOWNARROW) && (m_byState & STATE_DOWN))
		{
			ChangeAnimationR(L"Sitting");		//리버스
			SetFrameTime(TIME_ACTION);
			FrameReverse = true;
			FrameOne = true;
			m_byState ^= STATE_DOWN;
			if (m_byState & STATE_ATTACK)
			{
				m_byState ^= STATE_ATTACK;
			}
		}

		if (PUSHKEY(DIK_UPARROW) && PUSHKEY(DIK_DOWNARROW))
		{
			if ((m_byState & STATE_ATTACK) == 0)
			{
				if (m_byState & STATE_UP)
				{
					ChangeAnimationR(L"LookingUp");
					SetFrameTime(TIME_LOOK);
					FrameReverse = true;
					FrameOne = true;
					m_byState ^= STATE_UP;
				}
			}
			else
			{
				if (m_byState & STATE_UP && m_tKey.Option == L"H")
				{
					ChangeAnimation(L"AttackLookingUpR");
					SetFrameTime(TIME_LOOK / 2);
					FrameReverse = false;
					FrameOne = true;
					m_byState ^= STATE_UP;
				}
			}

			if (m_byState & STATE_DOWN)
			{
				ChangeAnimationR(L"Sitting");
				SetFrameTime(TIME_ACTION);
				FrameReverse = true;
				FrameOne = true;
				m_byState ^= STATE_DOWN;
				if (m_byState & STATE_ATTACK)
				{
					m_byState ^= STATE_ATTACK;
				}
			}
		}
		//===========================================================================
		if (((m_tKey.szSecondKey == L"Sitting"&&FrameReverse == false && !FrameEnd) == false))
		{
			if (UPKEY(DIK_RIGHTARROW) && PUSHKEY(DIK_LEFTARROW))			//왼쪽누름
			{
				if (m_tKey.eDir == DIRECTION_RIGHT)
				{
					if (m_byState & STATE_UP || (m_byState & STATE_ATTACK))
						m_tKey.eDir = DIRECTION_LEFT;
					else if ((m_byState & STATE_DOWN))
					{
						SitMotion = L"Sit";
						ChangeAnimation(L"TurnRSit");
						SetFrameTime(TIME_ACTION);
						FrameReverse = false;
						FrameOne = true;
						m_tKey.eDir = DIRECTION_LEFT;
					}
					else
					{
						ChangeAnimation(L"TurnR");
						SetFrameTime(TIME_ACTION);
						FrameReverse = false;
						FrameOne = true;
						m_tKey.eDir = DIRECTION_LEFT;
					}
				}
				else if ((m_byState & STATE_ATTACK) == 0)
				{
					if (m_tKey.szSecondKey == L"TurnR" || m_tKey.szSecondKey == L"TurnRSit")
					{
						if (FrameEnd)
						{
							if (m_byState & STATE_DOWN)
							{
								SitMotion = L"Sit";
								ChangeAnimation(L"SitWalk");
								SetFrameTime(TIME_JUMP);		//예외로 느리게
								FrameReverse = false;
								FrameOne = false;
							}
							else
							{
								ChangeAnimation(L"Walk");
								SetFrameTime(TIME_WALK);
								FrameReverse = false;
								FrameOne = false;
							}
						}
					}
					else
					{
						if ((m_byState & STATE_UP) == 0 && ((m_tKey.szSecondKey == L"LookingUp" && !FrameEnd) == false))
						{
							if (m_byState & STATE_DOWN)
							{
								SitMotion = L"Sit";
								ChangeAnimation(L"SitWalk");
								SetFrameTime(TIME_JUMP);			//예외로 느리게
								FrameReverse = false;
								FrameOne = false;
							}
							else
							{
								ChangeAnimation(L"Walk");
								SetFrameTime(TIME_WALK);
								FrameReverse = false;
								FrameOne = false;
							}
						}
					}
				}
				m_bMove = true;
			}

			if (UPKEY(DIK_LEFT) && PUSHKEY(DIK_RIGHTARROW))			//오른쪽누름
			{
				if (m_tKey.eDir == DIRECTION_LEFT)
				{
					if (m_byState & STATE_UP || (m_byState & STATE_ATTACK))
						m_tKey.eDir = DIRECTION_RIGHT;
					else if (m_byState & STATE_DOWN)
					{
						SitMotion = L"Sit";
						ChangeAnimation(L"TurnRSit");
						SetFrameTime(TIME_ACTION);
						FrameReverse = false;
						FrameOne = true;
						m_tKey.eDir = DIRECTION_RIGHT;
					}
					else
					{
						ChangeAnimation(L"TurnR");
						SetFrameTime(TIME_ACTION);
						FrameReverse = false;
						FrameOne = true;
						m_tKey.eDir = DIRECTION_RIGHT;
					}
				}
				else if ((m_byState & STATE_ATTACK) == 0)
				{
					if (m_tKey.szSecondKey == L"TurnR" || m_tKey.szSecondKey == L"TurnRSit")
					{
						if (FrameEnd)
						{
							if (m_byState & STATE_DOWN)
							{
								SitMotion = L"Sit";
								ChangeAnimation(L"SitWalk");
								SetFrameTime(TIME_JUMP);
								FrameReverse = false;
								FrameOne = false;
							}
							else
							{
								ChangeAnimation(L"Walk");
								SetFrameTime(TIME_WALK);
								FrameReverse = false;
								FrameOne = false;
							}
						}
					}
					else
					{
						if ((m_byState & STATE_UP) == 0 && ((m_tKey.szSecondKey == L"LookingUp" && !FrameEnd) == false))
						{
							if (m_byState & STATE_DOWN)
							{
								SitMotion = L"Sit";
								ChangeAnimation(L"SitWalk");
								SetFrameTime(TIME_JUMP);
								FrameReverse = false;
								FrameOne = false;
							}
							else
							{
								ChangeAnimation(L"Walk");
								SetFrameTime(TIME_WALK);
								FrameReverse = false;
								FrameOne = false;
							}
						}
					}
				}
				m_bMove = true;
			}

			if ((m_byState & STATE_ATTACK) == 0)
			{
				if (((PUSHKEY(DIK_LEFTARROW) && PUSHKEY(DIK_RIGHTARROW)) ||
					(UPKEY(DIK_LEFTARROW) && UPKEY(DIK_RIGHTARROW))) &&
					(((PUSHKEY(DIK_UPARROW) && PUSHKEY(DIK_DOWNARROW)) ||
					(UPKEY(DIK_UPARROW) && UPKEY(DIK_DOWNARROW)))))
				{
					if (((m_bMove || (Landing && !(m_bMove))) && m_tKey.szSecondKey != L"TurnR") &&
						m_tKey.szSecondKey != L"LookingUp")
					{
						ChangeAnimation(L"Stop");
						SetFrameTime(TIME_ACTION2);
						FrameReverse = false;
						FrameOne = true;

					}
					else
					{
						if (m_tKey.szSecondKey == L"Stop" || m_tKey.szSecondKey == L"LookingUp"
							|| m_tKey.szSecondKey == L"Sitting" || m_tKey.szSecondKey == L"TurnR" ||
							m_tKey.szSecondKey == L"StandMotion" || m_tKey.szSecondKey == L"StandMotion2")
						{
							if (FrameEnd)
							{
								ChangeAnimation(L"Stand");
								SetFrameTime(TIME_STAND);
								FrameReverse = false;
								FrameOne = false;
							}
						}
						else
						{
							ChangeAnimation(L"Stand");
							SetFrameTime(TIME_STAND);
							FrameReverse = false;
							FrameOne = false;

							if (rand() % 5000 <=6)
							{
								ChangeAnimation(L"StandMotion");
								SetFrameTime(TIME_STAND);
								FrameReverse = false;
								FrameOne = true;
							}
							if (ShotStack > 11 && m_tKey.Option == L"")
							{
								ChangeAnimation(L"StandMotion2");
								SetFrameTime(TIME_LOOK);		//예외로 빠르게
								FrameReverse = false;
								FrameOne = true;
								ShotStack = 0;
							}
						}
					}
					m_bMove = false;
				}
			}
			if ((PUSHKEY(DIK_LEFTARROW) && PUSHKEY(DIK_RIGHTARROW)) ||
				(UPKEY(DIK_LEFTARROW) && UPKEY(DIK_RIGHTARROW)))
			{
				m_bMove = false;
			}
		}
		//---------------------------------------------------
		if (PUSHKEY(DIK_S))
		{
			if (Jumptime)
			{
				if (!m_bJump)
				{
					if (m_byState & STATE_ATTACK)
					{
						ChangeAnimation(m_tKey.szSecondKey);
						FrameReverse = false;
						FrameOne = true;
					}
					else if (m_bMove)
					{
						ChangeAnimation(L"FrontJump");
						SetFrameTime(TIME_STAND);
						FrameReverse = false;
						FrameOne = true;
					}
					else
					{
						ChangeAnimation(L"Jump");
						SetFrameTime(TIME_JUMP);
						FrameReverse = false;
						FrameOne = true;
					}
					if (m_byState & STATE_UP && (m_byState&STATE_ATTACK) == 0)
					{
						ChangeAnimationR(L"LookingUp");
						SetFrameTime(TIME_LOOK);
						FrameReverse = true;
						FrameOne = true;
						m_byState ^= STATE_UP;

					}

					if (m_byState & STATE_DOWN)
					{
						ChangeAnimation(L"LookingDown");
						SetFrameTime(TIME_LOOK);
						FrameReverse = false;
						FrameOne = true;
						if (!DownTime)
						{
							DownTime = true;
							m_tInfo.vPos.y -= 10;
							m_iFootposY += 10;
						}
					}

					if (!MoveTime)
					{
						m_tInfo.vPos.y += 2;
						m_iFootposY -= 2;
						MoveTime = true;
					}
					m_fTime = 0.f;
					m_fTimeNow = 0.f;
					m_fV = 2.45f;
					m_bJump = true;
					Jumptime = false;
				}
			}
		}
		if (UPKEY(DIK_S))
			Jumptime = true;

		if (PUSHKEY(DIK_X))
		{
			ChangeAnimation(L"Victory");
			SetFrameTime(TIME_ACTION2);
			FrameReverse = false;
			FrameOne = false;
		}

	}
	//점프상태 일때
	else
	{	//아래
		if (m_byState & STATE_ATTACK)
		{
			ChangeAnimation(m_tKey.szSecondKey);
			FrameReverse = false;
			FrameOne = true;
		}
		if (PUSHKEY(DIK_DOWNARROW) && UPKEY(DIK_UPARROW))
		{
			if ((m_byState & STATE_DOWN) == 0)
			{
				if (m_byState & STATE_ATTACK && m_tKey.Option == L"H"&& m_tKey.szSecondKey != L"AttackGrenade"&&
					m_tKey.szSecondKey != L"AttackNife" && m_tKey.szSecondKey != L"AttackNife2")
				{
					ChangeAnimation(L"AttackLookingDown");
					SetFrameTime(TIME_LOOK / 2);
					FrameReverse = false;
					FrameOne = true;
				}
				else if ((m_byState & STATE_ATTACK) == 0)
				{
					ChangeAnimation(L"LookingDown");
					SetFrameTime(TIME_LOOK);
					FrameReverse = false;
					FrameOne = true;
				}
			}
			else
			{
				if (FrameEnd)
				{
					ChangeAnimation(L"LookDown");
					SetFrameTime(TIME_STAND);
					FrameReverse = false;
					FrameOne = false;
				}
			}
			m_byState |= STATE_DOWN;
		}
		else if (UPKEY(DIK_DOWNARROW) && (m_byState & STATE_DOWN))
		{
			if (m_byState & STATE_ATTACK && m_tKey.Option == L"H" &&m_tKey.szSecondKey != L"AttackGrenade"&&
				m_tKey.szSecondKey != L"AttackNife" && m_tKey.szSecondKey != L"AttackNife2")
			{
				ChangeAnimation(L"AttackLookingDownR");
				SetFrameTime(TIME_LOOK / 2);
				FrameReverse = false;
				FrameOne = true;
			}
			if (m_tKey.szSecondKey == L"LookDown")
			{
				ChangeAnimationR(L"LookingDown");		//리버스
				SetFrameTime(TIME_LOOK);
				FrameReverse = true;
				FrameOne = true;
			}
			m_byState ^= STATE_DOWN;
		}
		//위
		if ((m_byState & STATE_ATTACK) == 0 || m_tKey.Option == L"H")
		{
			if (PUSHKEY(DIK_UPARROW) && UPKEY(DIK_DOWNARROW))
			{
				if ((m_byState & STATE_UP) == 0)
				{
					if (m_byState & STATE_ATTACK && m_tKey.szSecondKey != L"AttackGrenade"&&
						m_tKey.szSecondKey != L"AttackNife" && m_tKey.szSecondKey != L"AttackNife2")
					{
						ChangeAnimation(L"AttackLookingUp");
						SetFrameTime(TIME_LOOK / 2);
						FrameReverse = false;
						FrameOne = true;
						m_byState |= STATE_UP;
					}
				}
				else
				{
					if ((m_byState & STATE_ATTACK) == 0)
					{
						ChangeAnimationR(L"LookingUp");
						SetFrameTime(TIME_LOOK);
						FrameReverse = true;
						FrameOne = true;
						m_byState ^= STATE_UP;
					}
				}
			}
			else if (UPKEY(DIK_UPARROW) && m_byState & STATE_UP)
			{
				if (m_byState & STATE_ATTACK && m_tKey.Option == L"H" && m_tKey.szSecondKey != L"AttackGrenade"&&
					m_tKey.szSecondKey != L"AttackNife" && m_tKey.szSecondKey != L"AttackNife2")
				{
					ChangeAnimation(L"AttackLookingUpR");
					SetFrameTime(TIME_LOOK / 2);
					FrameReverse = false;
					FrameOne = true;
					m_byState ^= STATE_UP;
				}
				else
				{
					ChangeAnimationR(L"LookingUp");
					SetFrameTime(TIME_LOOK);
					FrameReverse = true;
					FrameOne = true;
				}
				m_byState ^= STATE_UP;
			}
		}

		if ((UPKEY(DIK_DOWNARROW) && UPKEY(DIK_UPARROW)) ||
			(PUSHKEY(DIK_DOWNARROW) && PUSHKEY(DIK_UPARROW)) || PUSHKEY(DIK_UPARROW))
		{
			if ((m_tKey.szSecondKey == L"Attack" || m_tKey.szSecondKey == L"AttackUp" ||
				m_tKey.szSecondKey == L"AttackDown" || m_tKey.szSecondKey == L"AttackGrenade"||
				m_tKey.szSecondKey == L"AttackNife"|| m_tKey.szSecondKey == L"AttackNife2") &&
				FrameEnd)
			{
				ChangeAnimation(L"Jump");
				SetFrameTime(TIME_JUMP);
				FrameReverse = false;
				FrameOne = true;
			}
			if (m_tKey.szSecondKey == L"LookingDown")
			{
				if (FrameEnd)
				{
					ChangeAnimation(L"Jump");
					SetFrameTime(TIME_JUMP);
					FrameReverse = false;
					FrameOne = true;
				}
			}
			if (m_tKey.szSecondKey == L"LookingUp" || m_tKey.szSecondKey == L"AttackLookingUp" ||
				m_tKey.szSecondKey == L"AttackLookingDown")
			{
				if (FrameEnd)
				{
					ChangeAnimation(L"Stand");
					SetFrameTime(TIME_STAND);
					FrameReverse = false;
					FrameOne = false;
				}
			}
		}
	}
	//================================================공격모션
	if (PUSHKEY(DIK_A))
	{
		if (Attacktime)
		{
			if (m_tKey.Option != L"H")  //헤비가 아닐때만 바로 방향바꿈.
			{
				if (PUSHKEY(DIK_LEFTARROW) && UPKEY(DIK_RIGHTARROW))
					m_tKey.eDir = DIRECTION_LEFT;
				if (PUSHKEY(DIK_RIGHTARROW) && UPKEY(DIK_LEFTARROW))
					m_tKey.eDir = DIRECTION_RIGHT;
			}

			//적이 가까이 있다면
			if (SINGLE(CObjMgr)->GetObjectList(L"1.Enemy") != NULL)
			{
				RECT rc;
				if (m_tKey.eDir == DIRECTION_LEFT)
					rc = { int(m_tInfo.vPos.x - 10 - 15),
							int(m_tInfo.vPos.y - 5 - 20),
							int(m_tInfo.vPos.x - 10 + 15),
							int(m_tInfo.vPos.y - 5 + 20) };
				else
					rc = { int(m_tInfo.vPos.x + 10 - 15),
							int(m_tInfo.vPos.y - 5 - 20),
							int(m_tInfo.vPos.x + 10 + 15),
							int(m_tInfo.vPos.y - 5 + 20) };

				for (auto iter = (*SINGLE(CObjMgr)->GetObjectList(L"1.Enemy")).begin();
					iter != SINGLE(CObjMgr)->GetObjectList(L"1.Enemy")->end(); ++iter)
				{
					if (SINGLE(CCollisionMgr)->ColRect(rc, *iter))
					{
						if (m_tKey.szSecondKey == L"AttackNife" && FrameEnd)
							ChangeAnimation(L"AttackNife2");
						else if (m_tKey.szSecondKey == L"AttackNife2" && FrameEnd)
							ChangeAnimation(L"AttackNife");
						else if(m_tKey.szSecondKey == L"AttackNifeSit" && FrameEnd)
							ChangeAnimation(L"AttackNifeSit2");
						else if(m_tKey.szSecondKey == L"AttackNifeSit2" && FrameEnd)
							ChangeAnimation(L"AttackNifeSit");
						else
						{
							if (m_bJump || (!m_bJump && (m_byState & STATE_DOWN) == 0))
							{
								if (rand() % 2 == 0)
								{
									ChangeAnimation(L"AttackNife");
									SetFrameTime(TIME_ACTION);
									FrameReverse = false;
									FrameOne = true;
								}
								else
								{
									ChangeAnimation(L"AttackNife2");
									SetFrameTime(TIME_ACTION);
									FrameReverse = false;
									FrameOne = true;
								}
							}
							else
							{
								if (rand() % 2 == 0)
								{
									ChangeAnimation(L"AttackNifeSit");
									SetFrameTime(TIME_ACTION);
									SitMotion = L"SitGrenade";
									FrameReverse = false;
									FrameOne = true;
								}
								else
								{
									ChangeAnimation(L"AttackNifeSit2");
									SetFrameTime(TIME_ACTION);
									SitMotion = L"SitGrenade";
									FrameReverse = false;
									FrameOne = true;
								}
							}
						}
					}
				}
			}

			//근접공격 모션 아닐경우 - 일반공격
			if (m_tKey.szSecondKey != L"AttackNife"&& m_tKey.szSecondKey != L"AttackNife2" &&
				m_tKey.szSecondKey != L"AttackNifeSit" &&m_tKey.szSecondKey != L"AttackNifeSit2")
			{
				if (PUSHKEY(DIK_UPARROW) && UPKEY(DIK_DOWNARROW))
				{
					if (m_tKey.Option == L"H" && ((m_byState & STATE_ATTACK) && (FrameEnd || m_tFrame.iFrame >= 5)))
					{
						m_byState |= STATE_UP;
						ChangeAnimationS(L"AttackUp");
						SetFrameTime(TIME_ACTION2 - Heavy);
						FrameReverse = false;
						FrameOne = true;
						m_bShot = true;
					}
					else if (m_tKey.Option != L"H" || (m_byState &STATE_ATTACK) == 0)
					{
						m_byState |= STATE_UP;
						ChangeAnimationS(L"AttackUp");
						SetFrameTime(TIME_ACTION2 - Heavy);
						FrameReverse = false;
						FrameOne = true;
						m_bShot = true;
					}
				}
				if (UPKEY(DIK_UPARROW) && PUSHKEY(DIK_DOWNARROW))
				{
					if (!m_bJump)
					{
						if (m_tKey.Option == L"H" && ((m_byState & STATE_ATTACK) && (FrameEnd || m_tFrame.iFrame >= 5)))
						{
							m_byState |= STATE_DOWN;
							ChangeAnimationS(L"AttackSit");
							SetFrameTime(TIME_ACTION2 - Heavy);
							SitMotion = L"SitShot";
							FrameReverse = false;
							FrameOne = true;
							m_bShot = true;
						}
						else if (m_tKey.Option != L"H" || (m_byState &STATE_ATTACK) == 0)
						{
							m_byState |= STATE_DOWN;
							ChangeAnimationS(L"AttackSit");
							SetFrameTime(TIME_ACTION2 - Heavy);
							SitMotion = L"SitShot";
							FrameReverse = false;
							FrameOne = true;
							m_bShot = true;
						}
					}
					else
					{
						if (m_tKey.Option == L"H" && ((m_byState & STATE_ATTACK) && (FrameEnd || m_tFrame.iFrame >= 5)))
						{
							m_byState |= STATE_DOWN;
							ChangeAnimationS(L"AttackDown");
							SetFrameTime(TIME_ACTION2 - Heavy);
							FrameReverse = false;
							FrameOne = true;
							m_bShot = true;
						}
						else if (m_tKey.Option != L"H" || (m_byState &STATE_ATTACK) == 0)
						{
							m_byState |= STATE_DOWN;
							ChangeAnimationS(L"AttackDown");
							SetFrameTime(TIME_ACTION2 - Heavy);
							FrameReverse = false;
							FrameOne = true;
							m_bShot = true;
						}
					}
				}
				if ((UPKEY(DIK_DOWNARROW) && UPKEY(DIK_UPARROW)) ||
					(PUSHKEY(DIK_DOWNARROW) && PUSHKEY(DIK_UPARROW)))
				{
					if (m_tKey.Option == L"H" && ((m_byState & STATE_ATTACK) && (FrameEnd || m_tFrame.iFrame >= 5)))
					{
						ChangeAnimationS(L"Attack");
						SetFrameTime(TIME_ACTION2 - Heavy);
						FrameReverse = false;
						FrameOne = true;
						m_bShot = true;
					}
					else if (m_tKey.Option != L"H" || (m_byState &STATE_ATTACK) == 0)
					{
						ChangeAnimationS(L"Attack");
						SetFrameTime(TIME_ACTION2 - Heavy);
						FrameReverse = false;
						FrameOne = true;
						m_bShot = true;
					}
				}
			}
			++ShotStack;
			m_byState |= STATE_ATTACK;
			Attacktime = false;
		}
	}
	if (UPKEY(DIK_A))
	{
		Attacktime = true;
	}

	if (PUSHKEY(DIK_D))
	{
		/*if (PUSHKEY(DIK_LEFTARROW) && UPKEY(DIK_RIGHTARROW))
			m_tKey.eDir = DIRECTION_LEFT;
		if (PUSHKEY(DIK_RIGHTARROW) && UPKEY(DIK_LEFTARROW))
			m_tKey.eDir = DIRECTION_RIGHT;*/

		if (Grenadetime)
		{
			if (UPKEY(DIK_UPARROW) && PUSHKEY(DIK_DOWNARROW))
			{
				if (!m_bJump)
				{
					ChangeAnimation(L"AttackGrenadeSit");
					SetFrameTime(TIME_ACTION2);
					SitMotion = L"SitGrenade";
					FrameReverse = false;
					FrameOne = true;
				}
				else
				{
					ChangeAnimation(L"AttackGrenade");
					SetFrameTime(TIME_ACTION2);
					FrameReverse = false;
					FrameOne = true;
				}
			}
			else
			{
				ChangeAnimation(L"AttackGrenade");
				SetFrameTime(TIME_ACTION2);
				FrameReverse = false;
				FrameOne = true;
			}
			m_byState |= STATE_ATTACK;
			Grenadetime = false;
		}
	}
	if (UPKEY(DIK_D))
	{
		Grenadetime = true;
	}

	//공격 텍스쳐 끝 프레임일때 공격상태 제거
	if ((m_byState & STATE_ATTACK) && FrameEnd)
		m_byState ^= STATE_ATTACK;

}

void CPlayer::Action()
{
	if (PUSHKEY(DIK_RIGHTARROW))
	{
		if (!m_bJump && (m_byState & STATE_DOWN) &&		//앉아서 공격 중엔 이동 멈춤.
			((m_byState & STATE_ATTACK)))
		{
			m_tInfo.vPos.x = m_tInfo.vPos.x;
		}
		else if ((m_tKey.szSecondKey == L"Sitting") && (FrameReverse == false))		//앉는 중일때도 이동 멈춤
			m_tInfo.vPos.x = m_tInfo.vPos.x;
		else if ((m_byState & STATE_DOWN) && !m_bJump)
		{
			m_tInfo.vPos.x += DeltaTime * 30;
			if (m_tInfo.vPos.x > SINGLE(CCamMgr)->GetCamPos().x + 304 - m_tInfo.vSize.x / 2)
				m_tInfo.vPos.x = SINGLE(CCamMgr)->GetCamPos().x + 304 - m_tInfo.vSize.x / 2;
		}
		else
		{
			m_tInfo.vPos.x += DeltaTime * 70;
			if (m_tInfo.vPos.x > SINGLE(CCamMgr)->GetCamPos().x + 304 - m_tInfo.vSize.x / 2)
				m_tInfo.vPos.x = SINGLE(CCamMgr)->GetCamPos().x + 304 - m_tInfo.vSize.x / 2;
		}
	}

	if (PUSHKEY(DIK_LEFTARROW))
	{
		if (!m_bJump && (m_byState & STATE_DOWN) &&
			((m_byState & STATE_ATTACK)))
			m_tInfo.vPos.x = m_tInfo.vPos.x;
		else if (m_tKey.szSecondKey == L"Sitting"&& FrameReverse == false)
			m_tInfo.vPos.x = m_tInfo.vPos.x;
		else if ((m_byState & STATE_DOWN) && !m_bJump)
		{
			m_tInfo.vPos.x -= DeltaTime * 30;
			if (m_tInfo.vPos.x < SINGLE(CCamMgr)->GetCamPos().x + m_tInfo.vSize.x / 2)
				m_tInfo.vPos.x = SINGLE(CCamMgr)->GetCamPos().x + m_tInfo.vSize.x / 2;
		}
		else
		{
			m_tInfo.vPos.x -= DeltaTime * 70;
			if (m_tInfo.vPos.x < SINGLE(CCamMgr)->GetCamPos().x + m_tInfo.vSize.x / 2)
				m_tInfo.vPos.x = SINGLE(CCamMgr)->GetCamPos().x + m_tInfo.vSize.x / 2;
		}
	}

	if (!m_bJump)
	{
		if (PUSHKEY(DIK_DOWNARROW) && UPKEY(DIK_UPARROW))
		{
			if (DownTime && m_tKey.szSecondKey != L"Sitting")
			{
				m_tInfo.vPos.y += 10;
				m_iFootposY -= 10;
				DownTime = false;
			}
		}
		if (UPKEY(DIK_DOWNARROW) && !DownTime ||
			((PUSHKEY(DIK_DOWNARROW) && PUSHKEY(DIK_UPARROW)) && !DownTime))
		{
			DownTime = true;
			m_tInfo.vPos.y -= 10;
			m_iFootposY += 10;
		}

		if ((PUSHKEY(DIK_LEFTARROW) && (UPKEY(DIK_RIGHTARROW))) ||
			(PUSHKEY(DIK_RIGHTARROW) && UPKEY(DIK_LEFTARROW)))
		{
			if (MoveTime && m_tKey.szSecondKey != L"TurnR" && ((m_byState & STATE_DOWN) == 0))
			{
				m_tInfo.vPos.y -= 2;
				m_iFootposY += 2;
				MoveTime = false;
			}
		}
		if ((PUSHKEY(DIK_LEFTARROW) && (PUSHKEY(DIK_RIGHTARROW))) ||
			(UPKEY(DIK_RIGHTARROW) && UPKEY(DIK_LEFTARROW)))
		{
			if (!MoveTime)
			{
				m_tInfo.vPos.y += 2;
				m_iFootposY -= 2;
				MoveTime = true;
			}
		}
	}
}

void CPlayer::Attack()
{
	int d;		//왼,오 방향 적용
	if (m_tKey.eDir == DIRECTION_LEFT)
		d = -1;
	else
		d = 1;

	if (m_tKey.szSecondKey == L"AttackNife" || m_tKey.szSecondKey == L"AttackNife2" ||		//근접 공격 모션일 경우 
		m_tKey.szSecondKey == L"AttackNifeSit" || m_tKey.szSecondKey == L"AttackNifeSit2")	//바로 충돌체크
	{
		if (m_tFrame.iFrame == 0)
			m_bShot = true;

		if (m_tFrame.iFrame == 3 && m_bShot)
		{
			RECT rc = { int(m_tInfo.vPos.x + 10*d - 15),int(m_tInfo.vPos.y - 5	  - 20),
						int(m_tInfo.vPos.x + 10*d + 15),int(m_tInfo.vPos.y - 5	  + 20) };

			for (auto iter = (*SINGLE(CObjMgr)->GetObjectList(L"1.Enemy")).begin();
				iter != SINGLE(CObjMgr)->GetObjectList(L"1.Enemy")->end(); ++iter)
			{
				if (SINGLE(CCollisionMgr)->ColRect(rc, *iter))
					(*iter)->SetHp(-10);
			}
			m_bShot = false;
		}
	}

	if (m_tKey.szSecondKey == L"Attack" || m_tKey.szSecondKey == L"AttackSit")		// 일반 공격 모션일 경우 총알생성
	{
		if (m_tKey.Option == L"" && m_tFrame.iFrame == 0 && m_bShot)	// 권총일 경우 첫 프레임에만
		{
			CreateBullet(0.f, d, D3DXVECTOR3(m_tInfo.vPos.x + 28 * d, m_tInfo.vPos.y - 3, 0));
			m_bShot = false;
		}
		else if (m_tKey.Option == L"H" && ((m_tFrame.iFrame % 2) == 1) && m_bShot)		//기관총일 경우 2프레임에 한번씩
		{
			if (m_tKey.szSecondKey == L"Attack")
			{
				CreateBullet(0.f, d);
				m_bShot = false;
			}
			else
			{
				CreateBullet(0.f, d, D3DXVECTOR3(m_tInfo.vPos.x + 35 * d, m_tInfo.vPos.y - 6, 0));
				m_bShot = false;
			}
		}
	}
	else if (m_tKey.szSecondKey == L"AttackUp")
	{
		if (m_tKey.Option == L"" && m_tFrame.iFrame == 0 && m_bShot)
		{
			CreateBullet(90.f, d, D3DXVECTOR3(m_tInfo.vPos.x + d, m_tInfo.vPos.y - 35, 0));
			m_bShot = false;
		}
		else if (m_tKey.Option == L"H" && ((m_tFrame.iFrame % 2) == 1) && m_bShot)
		{
			CreateBullet(90.f, d);
			m_bShot = false;
		}
	}
	else if (m_tKey.szSecondKey == L"AttackDown")
	{
		if (m_tKey.Option == L"" && m_tFrame.iFrame == 0 && m_bShot)
		{
			CreateBullet(-90.f, d, D3DXVECTOR3(m_tInfo.vPos.x + 3 * d, m_tInfo.vPos.y + 25, 0));
			m_bShot = false;
		}
		else if (m_tKey.Option == L"H" && ((m_tFrame.iFrame % 2) == 1) && m_bShot)
		{
			CreateBullet(-90.f, d);
			m_bShot = false;
		}
	}
	else if (m_tKey.szSecondKey == L"AttackLookingUp")
	{
		if ((m_tFrame.iFrame == 1) && m_bShot)
		{
			CreateBullet(18.f, d);
			m_bShot = false;
		}
		else if ((m_tFrame.iFrame == 3) && m_bShot)
		{
			CreateBullet(36.f, d);
			m_bShot = false;
		}
		else if ((m_tFrame.iFrame == 5) && m_bShot)
		{
			CreateBullet(54.f, d);
			m_bShot = false;
		}
		else if ((m_tFrame.iFrame == 7) && m_bShot)
		{
			CreateBullet(72.f, d);
			m_bShot = false;
		}
	}
	else if (m_tKey.szSecondKey == L"AttackLookingUpR")
	{
		if ((m_tFrame.iFrame == 1) && m_bShot)
		{
			CreateBullet(72.f, d);
			m_bShot = false;
		}
		else if ((m_tFrame.iFrame == 3) && m_bShot)
		{
			CreateBullet(54.f, d);
			m_bShot = false;
		}
		else if ((m_tFrame.iFrame == 5) && m_bShot)
		{
			CreateBullet(36.f, d);
			m_bShot = false;
		}
	}
	else if (m_tKey.szSecondKey == L"AttackLookingDown")
	{
		if ((m_tFrame.iFrame == 1) && m_bShot)
		{
			CreateBullet(-18.f, d);
			m_bShot = false;
		}
		else if ((m_tFrame.iFrame == 3) && m_bShot)
		{
			CreateBullet(-36.f, d);
			m_bShot = false;
		}
		else if ((m_tFrame.iFrame == 5) && m_bShot)
		{
			CreateBullet(-54.f, d);
			m_bShot = false;
		}
		else if ((m_tFrame.iFrame == 7) && m_bShot)
		{
			CreateBullet(-72.f, d);
			m_bShot = false;
		}
	}
	else if (m_tKey.szSecondKey == L"AttackLookingDownR")
	{
		if ((m_tFrame.iFrame == 1) && m_bShot)
		{
			CreateBullet(-72.f, d);
			m_bShot = false;
		}
		else if ((m_tFrame.iFrame == 3) && m_bShot)
		{
			CreateBullet(-54.f, d);
			m_bShot = false;
		}
		else if ((m_tFrame.iFrame == 5) && m_bShot)
		{
			CreateBullet(-36.f, d);
			m_bShot = false;
		}
	}

	//수류탄 생성
	if (m_tKey.szSecondKey == L"AttackGrenade")
	{
		if (m_tFrame.iFrame < 2)
			m_bShot = true;
		else if (m_tFrame.iFrame == 2 && m_bShot)
		{
			CreateGrenade(D3DXVECTOR3(m_tInfo.vPos.x + 15 * d, m_tInfo.vPos.y - 10, 0));
			m_bShot = false;
		}

	}
	else if (m_tKey.szSecondKey == L"AttackGrenadeSit")
	{
		if (m_tFrame.iFrame < 3)
			m_bShot = true;
		else if (m_tFrame.iFrame == 3 && m_bShot)
		{
			CreateGrenade(D3DXVECTOR3(m_tInfo.vPos.x + 15 * d, m_tInfo.vPos.y - 10, 0));
			m_bShot = false;
		}
	}

	//공격초기화
	if (m_tKey.Option == L"H" && m_byState & STATE_ATTACK)
	{
		if (m_tFrame.iFrame % 2 == 0 &&
			(m_tKey.szSecondKey != L"AttackGrenade" && m_tKey.szSecondKey != L"AttackGrenadeSit"))
			m_bShot = true;
	}
}

void CPlayer::SetFrameTime(float time)
{
	m_tFrame.fFrameTime = time;
}

HRESULT CPlayer::OnInit()
{
	m_tFrame.iFrame = 0;
	m_tFrame.fFrameTime = 0.11f;
	m_tFrame.fFrameTimeNow = 0;
	m_tKey.szRenderKey = L"Tarma";
	m_tKey.szSecondKey = L"Jump";
	m_tKey.eDir = DIRECTION_RIGHT;
	m_tKey.Option = L"";

	FrameStop = true;
	Heavy = 0.025f;				//기관총 프레임 조절 용도

	m_bMove = 0;
	m_byState = STATE_NONE;
	m_eLayer = LAYER_OBJECT2;
	m_tInfo.vPos = D3DXVECTOR3(20, 100, 0);
	m_tInfo.vCenter = D3DXVECTOR3(45,60,0);
	m_tInfo.vSize = D3DXVECTOR2(24, 28);
	m_iFootposY = 23;
	m_iHp = 1;

	m_bJump = true;
	m_fV = 0.7f;
	m_fTime = 0.f;

	m_fAngle = 0.f;
	m_vBulletPos = D3DXVECTOR3(0, 0, 0);
	m_bShot = true;
	m_fHeavyAngle = 2.f;

	m_iHBullets = 0;
	m_iGrenades = 10;
	SINGLE(CCamMgr)->SetCamObject(this);
	return S_OK;
}

int CPlayer::OnUpdate()
{
	//평소
	if (m_iHp > 0 && m_tKey.szSecondKey != L"Victory")
	{
		if (m_tKey.Option ==L"H" && m_iHBullets <= 0)
			SetEquip(L"");
		//모션 결정
		Motion();

		//이동 위치 계산
		Action();

		//총알,수류탄 생성
		Attack();
	}
	//피가 다닳았을경우
	else 
	{
		if ((m_byState & STATE_DIE) == 0)
		{
			SetEquip(L"");
			if (!DownTime)
			{
				DownTime = true;
				m_tInfo.vPos.y -= 10;
				m_iFootposY += 10;
			}
			if (m_bJump || m_iHp < -5)
			{
				ChangeAnimation(L"Death2");
				SetFrameTime(TIME_LOOK);
				FrameReverse = false;
				FrameOne = true;

				m_fTime = 0.f;
				m_fTimeNow = 0.f;
				m_fV = 2.2f;
				m_bJump = true;
			}
			else
			{
				ChangeAnimation(L"Death1");
				SetFrameTime(TIME_LOOK);
				FrameReverse = false;
				FrameOne = true;
			}
			m_byState = STATE_DIE;
		}
		else if (m_tKey.szSecondKey == L"Death1" &&m_tFrame.iFrame == 0)
		{
			if (DeathTime)
			{
				CObj* effect = new CEffect(LAYER_EFFECT);
				effect->SetPos(D3DXVECTOR3(m_tInfo.vPos.x, m_tInfo.vPos.y, 0));
				effect->SetRenderKey(L"Blood1");
				effect->GetKey().eDir = m_tKey.eDir;
				SINGLE(CObjMgr)->PushObject(L"2.Effect", effect);
				DeathTime = false;
			}
		}
		else if (m_tKey.szSecondKey == L"Death2" &&m_tFrame.iFrame == 0)
		{
			if (DeathTime)
			{
				CObj* effect = new CEffect(LAYER_EFFECT);
				effect->SetPos(D3DXVECTOR3(m_tInfo.vPos.x, m_tInfo.vPos.y, 0));
				effect->SetRenderKey(L"Blood2");
				effect->GetKey().eDir = m_tKey.eDir;
				SINGLE(CObjMgr)->PushObject(L"2.Effect", effect);
				DeathTime = false;
			}
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

	//죽은경우 깜박거림 후 삭제
	if (m_byState & STATE_DIE)
	{
		if (m_tKey.szSecondKey == L"Death1" && m_tFrame.iFrame > 16)
		{
			++m_iDeathCount;
			if ((m_iDeathCount / 10) % 2 == 0)
				m_iAlpha = 1;
			else
				m_iAlpha = 2;
			if (m_iDeathCount > 200)
				return RESULT_OBJECT_DELETE;
		}
		else if (m_tKey.szSecondKey == L"Death2" &&m_tFrame.iFrame > 8)
		{
			++m_iDeathCount;
			if ((m_iDeathCount / 10) % 2 == 0)
				m_iAlpha = 1;
			else
				m_iAlpha = 2;
			if (m_iDeathCount > 200)
			return RESULT_OBJECT_DELETE;
		}
	}

	//-----------------점프, 라인충돌(바닥)----------------------------------
	if (m_bJump)
		Jump();

	if(!(m_tKey.szSecondKey == L"Death2" && m_tFrame.iFrame < 5))
		Landing = LineCol();

	if (Landing)
	{
		if(m_byState & STATE_DOWN)
		m_byState ^= STATE_DOWN;
		if (m_tKey.szSecondKey == L"Death2")
			FrameStop = false;
	}
	else
	{
		if (m_tKey.szSecondKey == L"Death2" && m_tFrame.iFrame >= 5&&
			FrameStop)
		{
			m_tFrame.iFrame = 5;
		}
	}
	//----------------------객체 이동 적용(directX)----------------------------
	D3DXMATRIX matTrans, matScale;
	if(m_tKey.eDir == DIRECTION_RIGHT)
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

void CPlayer::OnRender()
{
	const TEXINFO* pTex = SINGLE(CTextureMgr)->GetTexture(
		m_tKey.Option + m_tKey.szRenderKey, m_tKey.szSecondKey, m_tFrame.iFrame);
	if (pTex == 0)
		return;
	SINGLE(CDevice)->GetSprite()->SetTransform(&m_tInfo.matWorld);
	SINGLE(CDevice)->GetSprite()->Draw(
		pTex->pTexture, NULL, &m_tInfo.vCenter, 0,
		D3DCOLOR_ARGB(255/m_iAlpha ,255,255,255));
}

void CPlayer::OnRelease()
{
}