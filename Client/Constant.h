#pragma once

const float TIME_STAND   = 0.12f;
const float TIME_WALK    = 0.05f;
const float TIME_JUMP    = 0.07f;
const float TIME_LOOK    = 0.09f;		// + death
const float TIME_ACTION  = 0.05f; 
const float TIME_ACTION2 = 0.065f;		// pistol shot

const BYTE STATE_NONE    = 0x00;
const BYTE STATE_UP		 = 0x01;
const BYTE STATE_DOWN	 = 0x02;
const BYTE STATE_JUMP	 = 0x04;
const BYTE STATE_ATTACK  = 0x08;
const BYTE STATE_DIE	 = 0x10;


const float PI = 3.141592f;
const int RESULT_NONE          = 0x00000000;
const int RESULT_SCENE_LOGO	   = 0x00000001;
const int RESULT_SCENE_SELECT  = 0x00000002;
const int RESULT_SCENE_STAGE   = 0x00000004;
const int RESULT_SCENE_OVER	   = 0x00000008;

const int RESULT_OBJECT_DELETE = 0x00000010;
const int RESULT_GAME_EXIT     = 0x80000000;

const int WINSIZEX = 304;
const int WINSIZEY = 216;

enum DIRECTION
{
	DIRECTION_LEFT,
	DIRECTION_RIGHT,
};

enum LAYER
{
	LAYER_GROUND,		//배경
	LAYER_GROUND2,		//구조물, 나무기둥

	LAYER_OBJECT,		//적,장애물, 보스
	LAYER_EFFECT,		// 피, 적 폭발 , 보스 부품
	LAYER_OBJECT2,		// 플레이어
	LAYER_EFFECT2,		// boss_booster 사라지는 효과
	LAYER_BULLET,		//총알
	LAYER_EFFECT3,		//포탄형태 총알폭발

	LAYER_GROUND3,		//바깥 구조물

	LAYER_UI,
	LAYER_END,
};

enum SCENEID
{
	SCENEID_LOGO,
	SCENEID_SELECT,
	SCENEID_STAGE,
	SCENEID_OVER
};

enum WINMODE
{
	WIN_FULL,
	WIN_WINDOW,
};