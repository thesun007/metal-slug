#pragma once
#include "ObjDynamic.h"
#include "NpcWait.h"

class CNpc :
	public CObjDynamic
{
private:
	CAi* m_pAI;
	int m_iLevel;			//���� 0:����x, 1:����o

	bool FrameEnd;
	bool FrameReverse;
	bool FrameOne;

	bool	Landing;
	float   JumpTime;
	bool	DownTime;	//�ɾ������� ��ġ����
	bool	FreeTime;

	//����
	int	 m_iGift;			//���� ���� (0:���, 1:����ź)
	bool m_bGive;			//���� ���� (Ư����ǿ��� �ѹ��� �����ϰԲ�)

public:
	bool& GetFrameEnd() { return FrameEnd; }
	bool& GetLanding() { return Landing; }
	void SetFrame(bool reverse, bool one) { FrameReverse = reverse; FrameOne = one; }
public:
	void SetLevel(int level) { m_iLevel = level; }
	int GetLevel()const { return m_iLevel; }
	void SetItem(int item) { m_iGift = item; }
public:
	void Motion();
	void Action();
	void Give();
	void CreateItem(D3DXVECTOR3 pos, wstring name);
public:
	virtual HRESULT OnInit();
	virtual int OnUpdate();
	virtual void OnRender();
	virtual void OnRelease();
public:
	CNpc();
	~CNpc();
};

