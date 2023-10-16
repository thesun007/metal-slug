#pragma once

#include "ObjDynamic.h"

class CPlayer : public CObjDynamic
{
protected:
	bool Jumptime;
	bool Attacktime;
	bool Grenadetime;
	bool DownTime;				//������ �߽�����
	bool MoveTime;				//�۶� �߽�����
	bool DeathTime;

	bool FrameEnd;
	bool FrameReverse;
	bool FrameOne;
	bool FrameStop;			//Ư�� �����϶� ������ ��� ���߱�

	float Heavy;			// �������϶� ������ �ӵ� ����뵵
	wstring SitMotion;
	bool	Landing;
	int		ShotStack;
		
	//�Ѿ�
	int m_iHBullets;
	int m_iGrenades;
	float m_fAngle;				
	D3DXVECTOR3 m_vBulletPos;
	bool m_bShot;		//�Ѿ� ����
	float m_fHeavyAngle;	
public:
	void Motion();
	void Action();
	void Attack();
	void CreateBullet(float angle, int d = 1, D3DXVECTOR3 pos= D3DXVECTOR3(0,0,0));
	void CreateGrenade(D3DXVECTOR3 pos = D3DXVECTOR3(0, 0, 0));
	void SetEquip(wstring equipment);
public:
	void SetFrameTime(float time);		//�ؽ��� ������ ��� �ӵ�
	bool GetJump() {return m_bJump;}
public:
	virtual HRESULT OnInit();
	virtual int OnUpdate();
	virtual void OnRender();
	virtual void OnRelease();
public:
	CPlayer(void);
	virtual ~CPlayer(void);
};

