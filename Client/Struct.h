#pragma once

typedef struct tagFrame
{
	int iFrame;
	float fFrameTime;
	float fFrameTimeNow;
}FRAME;

typedef struct tagRenderKey
{
	wstring szRenderKey;
	wstring szSecondKey;
	DIRECTION eDir;
	wstring Option;
}RENDERKEY;

typedef struct tagObjInfo
{
	D3DXVECTOR3 vPos;
	D3DXVECTOR3 vCenter;
	D3DXVECTOR2 vSize;
	D3DXMATRIX matWorld;
}OBJINFO;

typedef struct tagTexture
{
	LPDIRECT3DTEXTURE9 pTexture;
	D3DXIMAGE_INFO Info;
}TEXINFO;

typedef struct tagLine
{
	POINTFLOAT tLPoint;
	POINTFLOAT tRPoint;

	tagLine() {}
	tagLine(POINTFLOAT _lPoint, POINTFLOAT _rPoint)
		:tLPoint(_lPoint), tRPoint(_rPoint)
	{

	}
}LINE;