#include "StdAfx.h"
#include "StageScene.h"
#include "Include.h"

CStageScene::CStageScene(void)
{}

CStageScene::~CStageScene(void)
{
	OnRelease();
}

void CStageScene::ReadLine()
{
	HANDLE hFile;
	DWORD dwByte;
	hFile = CreateFile(L"../Data/Line.dat", GENERIC_READ
		, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	while (1)
	{
		LINE* pLine = new LINE;

		ReadFile(hFile, pLine, sizeof(LINE), &dwByte, NULL);
		if (dwByte == 0)
		{
			delete pLine;
			pLine = NULL;
			break;
		}
		m_listLine.push_back(pLine);

	}
	CloseHandle(hFile);
}

void CStageScene::CreateGround()
{
	CObj* pGround = new CBackground;
	pGround->SetRenderKey(L"Sky");
	pGround->SetPos(D3DXVECTOR3(0, 0, 0));
	SINGLE(CObjMgr)->PushObject(L"1Sky", pGround);

	pGround = new CBackground;
	pGround->SetRenderKey(L"Desert");
	SINGLE(CObjMgr)->PushObject(L"2Desert", pGround);

	pGround = new CBackground;
	pGround->SetRenderKey(L"Map");
	SINGLE(CObjMgr)->PushObject(L"3Map", pGround);

	CObj* pGround2 = new CSecondBack;
	pGround2->SetRenderKey(L"Banner");
	pGround2->SetPos(D3DXVECTOR3(3520, 8, 0));
	SINGLE(CObjMgr)->PushObject(L"Banner", pGround2);

	/*pGround2 = new CSecondBack;
	pGround2->SetRenderKey(L"Drum");
	SINGLE(CObjMgr)->PushObject(L"Drum", pGround);*/

	pGround2 = new CSecondBack;
	pGround2->SetRenderKey(L"Ltent");
	pGround2->SetPos(D3DXVECTOR3(3420,87, 0));
	SINGLE(CObjMgr)->PushObject(L"Ltent", pGround2);

	pGround2 = new CSecondBack;
	pGround2->SetRenderKey(L"Rtent");
	pGround2->SetPos(D3DXVECTOR3(3737,87, 0));
	SINGLE(CObjMgr)->PushObject(L"Rtent", pGround2);
}

void CStageScene::CreateEnemy()
{
	CObj* enemy = new CArabian;
	enemy->SetLine(&m_listLine);
	enemy->SetPos(D3DXVECTOR3(430, 170, 0));
	((CArabian*)enemy)->SetLevel(1);
	SINGLE(CObjMgr)->PushObject(L"1.Enemy", enemy);

	enemy = new CArabian;
	enemy->SetLine(&m_listLine);
	enemy->SetPos(D3DXVECTOR3(470, 180, 0));
	((CArabian*)enemy)->SetLevel(1);
	SINGLE(CObjMgr)->PushObject(L"1.Enemy", enemy);

	enemy = new CArabian;
	enemy->SetLine(&m_listLine);
	enemy->SetPos(D3DXVECTOR3(600,150,0));
	((CArabian*)enemy)->SetLevel(0);
	SINGLE(CObjMgr)->PushObject(L"1.Enemy", enemy);

	enemy = new CArabian;
	enemy->SetLine(&m_listLine);
	enemy->SetPos(D3DXVECTOR3(690, 170, 0));
	((CArabian*)enemy)->SetLevel(3);
	SINGLE(CObjMgr)->PushObject(L"1.Enemy", enemy);

	enemy = new CArabian;
	enemy->SetLine(&m_listLine);
	enemy->SetPos(D3DXVECTOR3(730, 80, 0));
	((CArabian*)enemy)->SetLevel(1);
	SINGLE(CObjMgr)->PushObject(L"1.Enemy", enemy);

	enemy = new CArabian;
	enemy->SetLine(&m_listLine);
	enemy->SetPos(D3DXVECTOR3(730, 170, 0));
	((CArabian*)enemy)->SetLevel(2);
	SINGLE(CObjMgr)->PushObject(L"1.Enemy", enemy);

	enemy = new CArabian;
	enemy->SetLine(&m_listLine);
	enemy->SetPos(D3DXVECTOR3(1330, 60, 0));
	((CArabian*)enemy)->SetLevel(2);
	SINGLE(CObjMgr)->PushObject(L"1.Enemy", enemy);

	enemy = new CArabian;
	enemy->SetLine(&m_listLine);
	enemy->SetPos(D3DXVECTOR3(1330, 100, 0));
	((CArabian*)enemy)->SetLevel(1);
	SINGLE(CObjMgr)->PushObject(L"1.Enemy", enemy);

	enemy = new CArabian;
	enemy->SetLine(&m_listLine);
	enemy->SetPos(D3DXVECTOR3(1330, 170, 0));
	((CArabian*)enemy)->SetLevel(2);
	SINGLE(CObjMgr)->PushObject(L"1.Enemy", enemy);

	enemy = new CArabian;
	enemy->SetLine(&m_listLine);
	enemy->SetPos(D3DXVECTOR3(1610, 100, 0));
	((CArabian*)enemy)->SetLevel(1);
	SINGLE(CObjMgr)->PushObject(L"1.Enemy", enemy);

	enemy = new CArabian;
	enemy->SetLine(&m_listLine);
	enemy->SetPos(D3DXVECTOR3(1610, 170, 0));
	((CArabian*)enemy)->SetLevel(3);
	SINGLE(CObjMgr)->PushObject(L"1.Enemy", enemy);

	enemy = new CArabian;
	enemy->SetLine(&m_listLine);
	enemy->SetPos(D3DXVECTOR3(1960, 90, 0));
	((CArabian*)enemy)->SetLevel(0);
	SINGLE(CObjMgr)->PushObject(L"1.Enemy", enemy);

	enemy = new CArabian;
	enemy->SetLine(&m_listLine);
	enemy->SetPos(D3DXVECTOR3(2860, 95, 0));
	((CArabian*)enemy)->SetLevel(1);
	SINGLE(CObjMgr)->PushObject(L"1.Enemy", enemy);
	
	enemy = new CArabian;
	enemy->SetLine(&m_listLine);
	enemy->SetPos(D3DXVECTOR3(2860, 170, 0));
	((CArabian*)enemy)->SetLevel(2);
	SINGLE(CObjMgr)->PushObject(L"1.Enemy", enemy);

	enemy = new CArabian;
	enemy->SetLine(&m_listLine);
	enemy->SetPos(D3DXVECTOR3(2920, 95, 0));
	((CArabian*)enemy)->SetLevel(0);
	SINGLE(CObjMgr)->PushObject(L"1.Enemy", enemy);

	enemy = new CArabian;
	enemy->SetLine(&m_listLine);
	enemy->SetPos(D3DXVECTOR3(2920, 170, 0));
	((CArabian*)enemy)->SetLevel(3);
	SINGLE(CObjMgr)->PushObject(L"1.Enemy", enemy);

	enemy = new CArabian;
	enemy->SetLine(&m_listLine);
	enemy->SetPos(D3DXVECTOR3(3045, 90, 0));
	((CArabian*)enemy)->SetLevel(1);
	SINGLE(CObjMgr)->PushObject(L"1.Enemy", enemy);

	enemy = new CArabian;
	enemy->SetLine(&m_listLine);
	enemy->SetPos(D3DXVECTOR3(3045, 170, 0));
	((CArabian*)enemy)->SetLevel(2);
	SINGLE(CObjMgr)->PushObject(L"1.Enemy", enemy);

	enemy = new CArabian;
	enemy->SetLine(&m_listLine);
	enemy->SetPos(D3DXVECTOR3(3070, 170, 0));
	((CArabian*)enemy)->SetLevel(2);
	SINGLE(CObjMgr)->PushObject(L"1.Enemy", enemy);

	enemy = new CArabian;
	enemy->SetLine(&m_listLine);
	enemy->SetPos(D3DXVECTOR3(3160, 90, 0));
	((CArabian*)enemy)->SetLevel(3);
	SINGLE(CObjMgr)->PushObject(L"1.Enemy", enemy);

	enemy = new CArabian;
	enemy->SetLine(&m_listLine);
	enemy->SetPos(D3DXVECTOR3(3160, 170, 0));
	((CArabian*)enemy)->SetLevel(2);
	SINGLE(CObjMgr)->PushObject(L"1.Enemy", enemy);

	enemy = new CBoss;
	((CBoss*)enemy)->SetLevel(0);
	enemy->SetLine(&m_listLine);
	SINGLE(CObjMgr)->PushObject(L"1.Enemy", enemy);

	CObj* enemy2 = new CBoss2;
	((CBoss2*)enemy2)->SetParent(enemy);
	enemy2->GetKey().szRenderKey = L"BoosterL";
	enemy2->GetLayer() = LAYER_OBJECT;
	enemy2->SetPos(D3DXVECTOR3(-97, 19,0 ));
	SINGLE(CObjMgr)->PushObject(L"1.Enemy2", enemy2);

	enemy2 = new CBoss2;
	((CBoss2*)enemy2)->SetParent(enemy);
	enemy2->GetKey().szRenderKey = L"BoosterR";
	enemy2->GetLayer() = LAYER_OBJECT;
	enemy2->SetPos(D3DXVECTOR3(97, 19, 0));
	SINGLE(CObjMgr)->PushObject(L"1.Enemy2", enemy2);

	enemy2 = new CBoss2;
	((CBoss2*)enemy2)->SetParent(enemy);
	enemy2->GetKey().szRenderKey = L"EngineL";
	enemy2->GetLayer() = LAYER_EFFECT;
	enemy2->SetPos(D3DXVECTOR3(-98, 8, 0));
	SINGLE(CObjMgr)->PushObject(L"1.Enemy2", enemy2);

	enemy2 = new CBoss2;
	((CBoss2*)enemy2)->SetParent(enemy);
	enemy2->GetKey().szRenderKey = L"EngineR";
	enemy2->GetLayer() = LAYER_EFFECT;
	enemy2->SetPos(D3DXVECTOR3(98, 8, 0));
	SINGLE(CObjMgr)->PushObject(L"1.Enemy2", enemy2);
}

void CStageScene::CreateNpc()
{
	CObj* npc = new CNpc;
	npc->SetLine(&m_listLine);
	npc->SetPos(D3DXVECTOR3(623, 190, 0));
	npc->SetRenderKey(L"Wait1");
	((CNpc*)npc)->SetLevel(0);
	((CNpc*)npc)->SetItem(0);
	SINGLE(CObjMgr)->PushObject(L"1.Enemy", npc);

	npc = new CNpc;
	npc->SetLine(&m_listLine);
	npc->SetPos(D3DXVECTOR3(645, 120, 0));
	npc->SetRenderKey(L"Wait1");
	((CNpc*)npc)->SetLevel(0);
	((CNpc*)npc)->SetItem(0);
	SINGLE(CObjMgr)->PushObject(L"1.Enemy", npc);

	npc = new CNpc;
	npc->SetLine(&m_listLine);
	npc->SetPos(D3DXVECTOR3(1305, 110, 0));
	npc->SetRenderKey(L"Wait2");
	((CNpc*)npc)->SetLevel(1);
	((CNpc*)npc)->SetItem(1);
	SINGLE(CObjMgr)->PushObject(L"1.Enemy", npc);

	npc = new CNpc;
	npc->SetLine(&m_listLine);
	npc->SetPos(D3DXVECTOR3(1415, 110, 0));
	npc->SetRenderKey(L"Wait1");
	((CNpc*)npc)->SetLevel(1);
	((CNpc*)npc)->SetItem(1);
	SINGLE(CObjMgr)->PushObject(L"1.Enemy", npc);

	npc = new CNpc;
	npc->SetLine(&m_listLine);
	npc->SetPos(D3DXVECTOR3(1650, 110, 0));
	npc->SetRenderKey(L"Wait1");
	((CNpc*)npc)->SetLevel(0);
	((CNpc*)npc)->SetItem(1);
	SINGLE(CObjMgr)->PushObject(L"1.Enemy", npc);

	npc = new CNpc;
	npc->SetLine(&m_listLine);
	npc->SetPos(D3DXVECTOR3(2030, 95, 0));
	npc->SetRenderKey(L"Wait1");
	((CNpc*)npc)->SetLevel(1);
	((CNpc*)npc)->SetItem(0);
	npc->GetKey().eDir = DIRECTION_RIGHT;
	SINGLE(CObjMgr)->PushObject(L"1.Enemy", npc);

	npc = new CNpc;
	npc->SetLine(&m_listLine);
	npc->SetPos(D3DXVECTOR3(2840, 100, 0));
	npc->SetRenderKey(L"Wait1");
	((CNpc*)npc)->SetLevel(1);
	((CNpc*)npc)->SetItem(0);
	SINGLE(CObjMgr)->PushObject(L"1.Enemy", npc);


}


HRESULT CStageScene::OnInit()
{
	m_fTime = 255;
	ReadLine();
	/*m_hdc = GetDC(g_hWnd);*/
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Ground/background0.png", L"Background",L"Sky",1)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Ground/background1.png", L"Background", L"Desert", 1)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Ground/background2.png", L"Background", L"Map", 1)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Ground/background3.png", L"Background", L"Footprint", 1)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Ground/background_banner%d.png", L"SecondBack", L"Banner", 4)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Ground/background_drum.png", L"SecondBack", L"Drum", 1)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Ground/background_lefttent%d.png", L"SecondBack", L"Ltent", 4)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Ground/background_righttent%d.png", L"SecondBack", L"Rtent", 4)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Ground/background_wall.png", L"SecondBack", L"Wall", 1)))
		return E_FAIL;

	CreateGround();

	CObj* player = new CPlayer;
	player->SetLine(&m_listLine);
	if(FAILED(SINGLE(CObjMgr)->PushObject(
		L"1.Tarma",player)))
		return E_FAIL;

	CObj* player2 = new CPlayer2;
	((CPlayer2*)player2)->SetParentWorld(&player->GetInfo().matWorld);
	if (FAILED(SINGLE(CObjMgr)->PushObject(L"1.TarmaLeg", player2)))
		return E_FAIL;

	CreateEnemy();
	CreateNpc();

	return S_OK;
}

int CStageScene::OnUpdate()
{
	SINGLE(CCreateMgr)->CreateEnemy(&m_listLine);

	if (!SINGLE(CObjMgr)->GetObjectList(L"1.Tarma")->empty())
	{
		if(m_fTime >5)
			m_fTime -= 2.5;
	}
	else
	{
		if (m_fTime < 250)
			m_fTime += 0.5f;
		else
			return RESULT_SCENE_OVER;
	}

	return SINGLE(CObjMgr)->OnUpdate();
}

void CStageScene::OnRender()
{
	SINGLE(CObjMgr)->OnRender();

	const TEXINFO* pTex2 = SINGLE(CTextureMgr)->GetTexture(
		L"Scenechange");
	D3DXMATRIX matTrans;
	D3DXMatrixTranslation(&matTrans,
		0.f,
		0.f,
		0.f);
	SINGLE(CDevice)->GetSprite()->SetTransform(&matTrans);
	SINGLE(CDevice)->GetSprite()->Draw(
		pTex2->pTexture, NULL, NULL, 0,
		D3DCOLOR_ARGB((int)m_fTime, 255, 255, 255));

	/*for (list<LINE*>::iterator iter = m_listLine.begin();
		iter != m_listLine.end(); ++iter)
	{
		MoveToEx(m_hdc, int((*iter)->tLPoint.x - SINGLE(CCamMgr)->GetCamPos().x)
			, int((*iter)->tLPoint.y - SINGLE(CCamMgr)->GetCamPos().y), NULL);
		LineTo(m_hdc, int((*iter)->tRPoint.x - SINGLE(CCamMgr)->GetCamPos().x), int((*iter)->tRPoint.y - SINGLE(CCamMgr)->GetCamPos().y) );
	}*/
}

void CStageScene::OnRelease()
{
	CObjMgr::Destroy();
	SINGLE(CCamMgr)->OnInit();
	auto iter = m_listLine.begin();
	for (; iter != m_listLine.end(); ++iter)
	{
		delete *iter;
	}
	m_listLine.clear();
}
