#include "StdAfx.h"
#include "Obstacle.h"
#include "Include.h"

CObstacle::CObstacle(void)
{}

CObstacle::~CObstacle(void)
{
	OnRelease();
}

HRESULT CObstacle::OnInit()
{
	m_eLayer = LAYER_OBJECT;
	

	return S_OK;
}

int CObstacle::OnUpdate()
{
	return RESULT_NONE;
}

void CObstacle::OnRender()
{
	D3DXMATRIX matTrans;
	
	/*const TEXINFO* pTex;*/

}

void CObstacle::OnRelease()
{

}