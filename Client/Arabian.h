#pragma once
#include "Enemy.h"
#include "Wait.h"
#include "Special.h"

class CArabian : public CEnemy
{
private:
	CAi* m_pAI;

	bool FrameEnd;
	bool FrameReverse;
	bool FrameOne;

	bool	Landing;

	//셔플 제어
	int shuffle;
	float m_fNowTime;
	float m_fWaitTime;

	//총알
	bool m_bShot;			//총알 제어 (특정모션에서 한번만 실행하게끔)
public:
	void SetAi() { delete m_pAI; m_pAI = new CSpecial; }
	bool& GetFrameEnd() { return FrameEnd; }
	bool& GetLanding() { return Landing; }
	void SetFrame(bool reverse, bool one) { FrameReverse = reverse; FrameOne = one; }
public:
	void EJump();
	void Motion();
	void Action();
	void Attack();
	void CreateBullet(D3DXVECTOR3 pos,wstring name);
public:
	virtual HRESULT OnInit();
	virtual int OnUpdate();
	virtual void OnRender();
	virtual void OnRelease();
public:
	CArabian();
	~CArabian();
};

