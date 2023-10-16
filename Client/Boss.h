#pragma once
#include "Enemy.h"
#include "BossWait.h"

class CBoss :
	public CEnemy
{
private:
	CAi* m_pAI;
	CObj* m_pDoor;
	CObj* m_pBooster1;
	CObj* m_pBooster2;
	LINE* m_pline[5];

	bool FrameEnd;
	bool FrameReverse;
	bool FrameOne;

	bool death;		//hp<0되자마자 Setmove초기화용

	bool dontmove;
	float MoveTimeNow;
	float MoveTime;
	int MaxSpeed;
	int Speed;
	int F;			//마찰력

	bool	Landing;
	int		m_iMaxHp;
	//총알
	bool m_bShot;			//총알 제어 (특정모션에서 한번만 실행하게끔)
public:
	virtual vector<RECT> GetRect(void);
	bool& GetFrameEnd() { return FrameEnd; }
	bool& GetLanding() { return Landing; }
	void SetFrame(bool reverse, bool one) { FrameReverse = reverse; FrameOne = one; }
	void SetMove(float movetime) { MoveTimeNow = 0.f; MoveTime = movetime; }
	int GetHp()const { return m_iHp; }
	void SetDonMove(bool move) { dontmove = move; }
	LINE** GetLine() { return m_pline; }
public:
	bool Move();		// 부드러운 이동 
	void Motion();
	void Action();
	void CreateBullet();
	void CreateLine();
	void CreateBoom();
	void CreateBigBoom();
public:
	virtual HRESULT OnInit();
	virtual int OnUpdate();
	virtual void OnRender();
	virtual void OnRelease();
public:
	CBoss();
	~CBoss();
};

