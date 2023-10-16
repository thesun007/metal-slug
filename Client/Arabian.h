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

	//���� ����
	int shuffle;
	float m_fNowTime;
	float m_fWaitTime;

	//�Ѿ�
	bool m_bShot;			//�Ѿ� ���� (Ư����ǿ��� �ѹ��� �����ϰԲ�)
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

