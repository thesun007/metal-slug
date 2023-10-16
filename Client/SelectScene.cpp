#include "stdafx.h"
#include "SelectScene.h"
#include "Include.h"


CSelectScene::CSelectScene()
	: m_iChoice(0),m_fTime(250), m_fSelectTime(0.f),m_bSelect(false), m_bNext(false), m_bKey(0)
{
}


CSelectScene::~CSelectScene()
{
	CObjMgr::Destroy();
}

void CSelectScene::CreateObject()
{
		CObj* pObj = new CCharacter;
		pObj->SetRenderKey(L"Marco");
		pObj->SetPos(D3DXVECTOR3(49,123 ,0 ));
		pObj->SetCenter(D3DXVECTOR3(32,60,0));
		SINGLE(CObjMgr)->PushObject(L"Marco", pObj);
	
		pObj = new CCharacter;
		pObj->SetRenderKey(L"Eri");
		pObj->SetPos(D3DXVECTOR3(117,123 ,0 ));
		pObj->SetCenter(D3DXVECTOR3(32, 60, 0));
		SINGLE(CObjMgr)->PushObject(L"Eri", pObj);
	
		pObj = new CCharacter;
		pObj->SetRenderKey(L"Tarma");
		pObj->SetPos(D3DXVECTOR3(185,123 ,0));
		pObj->SetCenter(D3DXVECTOR3(32, 60, 0));
		SINGLE(CObjMgr)->PushObject(L"Tarma", pObj);
	
		pObj = new CCharacter;
		pObj->SetRenderKey(L"Fio");
		pObj->SetPos(D3DXVECTOR3(253,123 ,0 ));
		pObj->SetCenter(D3DXVECTOR3(32, 60, 0));
		SINGLE(CObjMgr)->PushObject(L"Fio", pObj);

		pObj = new CM2;
		pObj->SetPos(D3DXVECTOR3(49, 123, 0));
		pObj->SetCenter(D3DXVECTOR3(32, 67, 0));
		((CM2*)pObj)->SetNumber(2);
		SINGLE(CObjMgr)->PushObject(L"M2marco", pObj);

		pObj = new CM2;
		pObj->SetPos(D3DXVECTOR3(117, 123, 0));
		pObj->SetCenter(D3DXVECTOR3(32, 67, 0));
		((CM2*)pObj)->SetNumber(3);
		SINGLE(CObjMgr)->PushObject(L"M2eri", pObj);

		pObj = new CM2;
		pObj->SetPos(D3DXVECTOR3(185, 123, 0));
		pObj->SetCenter(D3DXVECTOR3(32, 67, 0));
		((CM2*)pObj)->SetNumber(1);
		SINGLE(CObjMgr)->PushObject(L"M2tarma", pObj);

		pObj = new CM2;
		pObj->SetPos(D3DXVECTOR3(253, 123, 0));
		pObj->SetCenter(D3DXVECTOR3(32, 67, 0));
		((CM2*)pObj)->SetNumber(0);
		SINGLE(CObjMgr)->PushObject(L"M2fio", pObj);
}

HRESULT CSelectScene::OnInit()
{
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Select/background0.png", L"Background")))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Select/marco%d.png", L"Character", L"Marco", 3)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Select/eri%d.png", L"Character", L"Eri", 3)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Select/eri.png", L"Character", L"EriS", 1)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Select/tarma%d.png", L"Character",L"Tarma",3)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Select/tarma.png", L"Character", L"TarmaS", 1)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Select/fio%d.png", L"Character", L"Fio", 3)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Select/m2.png", L"M2")))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Select/m2select.png", L"M2select")))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Select/eri_ani%d.png", L"Ani", L"Eri_ani", 6)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Select/tarma_ani%d.png", L"Ani", L"Tarma_ani", 6)))
		return E_FAIL;
	
		if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
			L"../Resource/Texture/Select/p1.png", L"P1")))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/scenechange.png", L"Scenechange")))
		return E_FAIL;

	CreateObject();
	return S_OK;
}

int CSelectScene::OnUpdate()
{
	SINGLE(CObjMgr)->OnUpdate();
	if (!m_bSelect)
	{
		if (PUSHKEY(DIK_RIGHTARROW))
		{
			if (m_bKey == 0)
			{
				if (m_iChoice == 3)
					m_iChoice = 0;
				else
					++m_iChoice;
				m_bKey = 1;
			}
		}
		if (PUSHKEY(DIK_LEFTARROW))
		{
			if (m_bKey == 0)
			{
				if (m_iChoice == 0)
					m_iChoice = 3;
				else
					--m_iChoice;
				m_bKey = 1;
			}
		}
		if (UPKEY(DIK_LEFTARROW) && UPKEY(DIK_RIGHTARROW))
			m_bKey = 0;

		if (m_iChoice == 0)
			((CCharacter*)SINGLE(CObjMgr)->GetObjectList(L"Marco")->front())->SetFrame(1);
		else if (m_iChoice == 1)
			((CCharacter*)SINGLE(CObjMgr)->GetObjectList(L"Eri")->front())->SetFrame(1);
		else if (m_iChoice == 2)
			((CCharacter*)SINGLE(CObjMgr)->GetObjectList(L"Tarma")->front())->SetFrame(1);
		else if (m_iChoice == 3)
			((CCharacter*)SINGLE(CObjMgr)->GetObjectList(L"Fio")->front())->SetFrame(1);

		if (PUSHKEY(DIK_A))
		{
			m_bSelect = true;
			CObj* ani = new CM2Ani;
			if (m_iChoice == 0)
			{
				((CCharacter*)SINGLE(CObjMgr)->GetObjectList(L"Marco")->front())->SetFrame(2);
				((CM2*)SINGLE(CObjMgr)->GetObjectList(L"M2marco")->front())->SetSelect();
			}
			else if (m_iChoice == 1)
			{
				((CCharacter*)SINGLE(CObjMgr)->GetObjectList(L"Eri")->front())->SetFrame(2);
				((CM2*)SINGLE(CObjMgr)->GetObjectList(L"M2eri")->front())->SetSelect();
				ani->SetRenderKey(L"Eri_ani");
				((CM2Ani*)ani)->SetParentWorld(&SINGLE(CObjMgr)->GetObjectList(L"M2eri")->front()->GetInfo().matWorld);
				SINGLE(CObjMgr)->PushObject(L"M2Ani", ani);
			}
			else if (m_iChoice == 2)
			{
				((CCharacter*)SINGLE(CObjMgr)->GetObjectList(L"Tarma")->front())->SetFrame(2);
				((CM2*)SINGLE(CObjMgr)->GetObjectList(L"M2tarma")->front())->SetSelect();
				ani->SetRenderKey(L"Tarma_ani");
				((CM2Ani*)ani)->SetParentWorld(&SINGLE(CObjMgr)->GetObjectList(L"M2tarma")->front()->GetInfo().matWorld);
				SINGLE(CObjMgr)->PushObject(L"M2Ani", ani);
			}
			else if (m_iChoice == 3)
			{
				((CCharacter*)SINGLE(CObjMgr)->GetObjectList(L"Fio")->front())->SetFrame(2);
				((CM2*)SINGLE(CObjMgr)->GetObjectList(L"M2fio")->front())->SetSelect();
			}

		}
	}

	if (m_bSelect)
	{
		m_fSelectTime += DeltaTime;
		if (m_fSelectTime > 2)
			m_bNext = true;
	}

	if (!m_bNext)
	{
		if (m_fTime > 0)
			m_fTime -= 0.7f;
	}
	else
	{
		if (m_fTime <250)
			++m_fTime;
		if (m_fTime > 250)
			return RESULT_SCENE_STAGE;
	}
	return RESULT_NONE;
}

void CSelectScene::OnRender()
{
	SINGLE(CObjMgr)->OnRender();

	const TEXINFO* pTex = SINGLE(CTextureMgr)->GetTexture(
		L"Background");
	D3DXMATRIX matTrans;
	D3DXMatrixTranslation(&matTrans,
		0.f,
		0.f,
		0.f);
	SINGLE(CDevice)->GetSprite()->SetTransform(&matTrans);
	SINGLE(CDevice)->GetSprite()->Draw(
		pTex->pTexture, NULL, NULL, 0,
		D3DCOLOR_ARGB(255, 255, 255, 255));

	const TEXINFO* pTex1 = SINGLE(CTextureMgr)->GetTexture(
		L"P1");
	D3DXMatrixTranslation(&matTrans,
		49.f + 68 * m_iChoice,
		49.f,
		0.f);
	SINGLE(CDevice)->GetSprite()->SetTransform(&matTrans);
	SINGLE(CDevice)->GetSprite()->Draw(
		pTex1->pTexture, NULL, &D3DXVECTOR3(13.5, 9, 0), 0,
		D3DCOLOR_ARGB(255, 255, 255, 255));

	const TEXINFO* pTex2 = SINGLE(CTextureMgr)->GetTexture(
		L"Scenechange");
	D3DXMatrixTranslation(&matTrans,
		0.f,
		0.f,
		0.f);
	SINGLE(CDevice)->GetSprite()->SetTransform(&matTrans);
	SINGLE(CDevice)->GetSprite()->Draw(
		pTex2->pTexture, NULL, NULL, 0,
		D3DCOLOR_ARGB((int)m_fTime, 255, 255, 255));
	
}

void CSelectScene::OnRelease()
{
	CObjMgr::Destroy();
}

