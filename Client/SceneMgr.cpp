#include "StdAfx.h"
#include "SceneMgr.h"
#include "Include.h"

CSceneMgr::CSceneMgr(void)
	:m_pScene(0)
{}

CSceneMgr::~CSceneMgr(void)
{
	OnRelease();
}

HRESULT CSceneMgr::LoadScene(SCENEID ID)
{
	OnRelease();
	switch(ID)
	{
	case SCENEID_LOGO:
		m_pScene = new CLogoScene;
		break;
	case SCENEID_SELECT:
		m_pScene = new CSelectScene;
		break;
	case SCENEID_STAGE:
		m_pScene = new CStageScene;
		break;
	case SCENEID_OVER:
		m_pScene = new CGameOver;
		break;
	}
	if(m_pScene)
	{
		if(FAILED(m_pScene->OnInit()))
			return E_FAIL;
	}
	else
		return E_FAIL;
	return S_OK;
}

int CSceneMgr::OnUpdate()
{
	return m_pScene->OnUpdate();
}

void CSceneMgr::OnRender()
{
	m_pScene->OnRender();
}

void CSceneMgr::OnRelease()
{
	if(m_pScene != 0)
	{
		delete m_pScene;
		m_pScene = 0;
	}
}
