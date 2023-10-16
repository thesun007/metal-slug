#include "StdAfx.h"
#include "LogoScene.h"
#include "Include.h"

CLogoScene::CLogoScene(void)
{}

CLogoScene::~CLogoScene(void)
{
	OnRelease();
}

HRESULT CLogoScene::CreatePlayerImage()
{
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Player/Tarma/Stand/tarma_leg_stand.png", L"TarmaLeg", L"Stand", 1)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Player/Tarma/Stand/tarma_pistol_stand(motion)%d.png", L"Tarma", L"StandMotion", 18)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Player/HTarma/Stand/tarma_heavy_stand(motion)%d.png", L"HTarma", L"StandMotion", 18)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Player/Tarma/Stand/tarma_pistol_stand(reload)%d.png", L"Tarma", L"StandMotion2", 18)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Player/Tarma/Stand/tarma_pistol_stand%d.png", L"Tarma", L"Stand", 6)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Player/HTarma/Stand/tarma_heavy_stand%d.png", L"HTarma", L"Stand", 6)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Player/Tarma/Stand/tarma_pistol_stop%d.png", L"Tarma", L"Stop", 7)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Player/HTarma/Stand/tarma_heavy_stop%d.png", L"HTarma", L"Stop", 7)))
		return E_FAIL;

	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Player/Tarma/Sit/tarma_pistol_sit(granade)%d.png", L"Tarma", L"SitGrenade", 6)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Player/HTarma/Sit/tarma_heavy_sit(granade)%d.png", L"HTarma", L"SitGrenade", 6)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Player/Tarma/Sit/tarma_pistol_sit(shot)%d.png", L"Tarma", L"SitShot", 6)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Player/HTarma/Sit/tarma_heavy_sit(shot)%d.png", L"HTarma", L"SitShot", 6)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Player/Tarma/Sit/tarma_pistol_sit(walk)%d.png", L"Tarma", L"Sit", 6)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Player/HTarma/Sit/tarma_heavy_sit(walk)%d.png", L"HTarma", L"Sit", 6)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Player/Tarma/Sit/tarma_pistol_sitting%d.png", L"Tarma", L"Sitting", 3)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Player/HTarma/Sit/tarma_heavy_sitting%d.png", L"HTarma", L"Sitting", 3)))
		return E_FAIL;

	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Player/Tarma/Walk/tarma_leg_walk%d.png", L"TarmaLeg", L"Walk", 12)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Player/Tarma/Walk/tarma_pistol_sitwalk%d.png", L"Tarma", L"SitWalk", 7)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Player/HTarma/Walk/tarma_heavy_sitwalk%d.png", L"HTarma", L"SitWalk", 7)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Player/Tarma/Walk/tarma_pistol_turnR%d.png", L"Tarma", L"TurnR", 2)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Player/HTarma/Walk/tarma_heavy_turnR%d.png", L"HTarma", L"TurnR", 2)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Player/Tarma/Walk/tarma_pistol_turnRsit%d.png", L"Tarma", L"TurnRSit", 2)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Player/HTarma/Walk/tarma_heavy_turnRsit%d.png", L"HTarma", L"TurnRSit", 2)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Player/Tarma/Walk/tarma_pistol_walk%d.png", L"Tarma", L"Walk", 12)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Player/HTarma/Walk/tarma_heavy_walk%d.png", L"HTarma", L"Walk", 12)))
		return E_FAIL;

	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Player/Tarma/Look/tarma_pistol_lookdown.png", L"Tarma", L"LookDown", 1)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Player/HTarma/Look/tarma_heavy_lookdown.png", L"HTarma", L"LookDown", 1)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Player/Tarma/Look/tarma_pistol_lookingdown%d.png", L"Tarma", L"LookingDown", 2)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Player/HTarma/Look/tarma_heavy_lookingdown%d.png", L"HTarma", L"LookingDown", 2)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Player/Tarma/Look/tarma_pistol_lookingup%d.png", L"Tarma", L"LookingUp", 2)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Player/HTarma/Look/tarma_heavy_lookingup%d.png", L"HTarma", L"LookingUp", 2)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Player/Tarma/Look/tarma_pistol_lookup%d.png", L"Tarma", L"LookUp", 6)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Player/HTarma/Look/tarma_heavy_lookup%d.png", L"HTarma", L"LookUp", 6)))
		return E_FAIL;

	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Player/Tarma/Jump/tarma_leg_frontjump%d.png", L"TarmaLeg", L"FrontJump", 6)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Player/Tarma/Jump/tarma_leg_jump%d.png", L"TarmaLeg", L"Jump", 12)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Player/Tarma/Jump/tarma_pistol_frontjump%d.png", L"Tarma", L"FrontJump", 6)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Player/HTarma/Jump/tarma_heavy_frontjump%d.png", L"HTarma", L"FrontJump", 6)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Player/Tarma/Jump/tarma_pistol_jump%d.png", L"Tarma", L"Jump", 12)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Player/HTarma/Jump/tarma_heavy_jump%d.png", L"HTarma", L"Jump", 12)))
		return E_FAIL;

	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Player/Tarma/Attack/tarma_pistol_attack%d.png", L"Tarma", L"Attack", 10)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Player/HTarma/Attack/tarma_heavy_attack%d.png", L"HTarma", L"Attack", 8)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Player/Tarma/Attack/tarma_pistol_attacksit%d.png", L"Tarma", L"AttackSit", 10)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Player/HTarma/Attack/tarma_heavy_attacksit%d.png", L"HTarma", L"AttackSit", 8)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Player/Tarma/Attack/tarma_pistol_attackup%d.png", L"Tarma", L"AttackUp", 10)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Player/HTarma/Attack/tarma_heavy_attackup%d.png", L"HTarma", L"AttackUp", 8)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Player/Tarma/Attack/tarma_pistol_attackdown%d.png", L"Tarma", L"AttackDown", 6)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Player/HTarma/Attack/tarma_heavy_attackdown%d.png", L"HTarma", L"AttackDown", 8)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Player/Tarma/Attack/tarma_pistol_attackgranade%d.png", L"Tarma", L"AttackGrenade", 6)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Player/HTarma/Attack/tarma_heavy_attackgranade%d.png", L"HTarma", L"AttackGrenade", 6)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Player/Tarma/Attack/tarma_pistol_attackgranadesit%d.png", L"Tarma", L"AttackGrenadeSit", 6)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Player/HTarma/Attack/tarma_heavy_attackgranadesit%d.png", L"HTarma", L"AttackGrenadeSit", 6)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Player/Tarma/Attack/tarma_pistol_attacknife%d.png", L"Tarma", L"AttackNife", 11)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Player/HTarma/Attack/tarma_heavy_attacknife%d.png", L"HTarma", L"AttackNife", 11)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Player/Tarma/Attack/tarma_pistol_attacknife2%d.png", L"Tarma", L"AttackNife2", 9)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Player/HTarma/Attack/tarma_heavy_attacknife2%d.png", L"HTarma", L"AttackNife2", 9)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Player/Tarma/Attack/tarma_pistol_attacknifesit%d.png", L"Tarma", L"AttackNifeSit", 5)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Player/HTarma/Attack/tarma_heavy_attacknifesit%d.png", L"HTarma", L"AttackNifeSit", 5)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Player/Tarma/Attack/tarma_pistol_attacknifesit2%d.png", L"Tarma", L"AttackNifeSit2", 9)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Player/HTarma/Attack/tarma_heavy_attacknifesit2%d.png", L"HTarma", L"AttackNifeSit2", 9)))
		return E_FAIL;

	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Player/HTarma/Attack/tarma_heavy_attacklookingdown%d.png", L"HTarma", L"AttackLookingDown", 8)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Player/HTarma/Attack/tarma_heavy_attacklookingdownR%d.png", L"HTarma", L"AttackLookingDownR", 6)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Player/HTarma/Attack/tarma_heavy_attacklookingup%d.png", L"HTarma", L"AttackLookingUp", 8)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Player/HTarma/Attack/tarma_heavy_attacklookingupR%d.png", L"HTarma", L"AttackLookingUpR", 6)))
		return E_FAIL;

	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Player/Tarma/Death/tarma_1death%d.png", L"Tarma", L"Death1", 19)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Player/Tarma/Death/tarma_2death%d.png", L"Tarma", L"Death2", 10)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Player/Tarma/Victory/tarma_victory%d.png", L"Tarma", L"Victory", 6)))
		return E_FAIL;
	return S_OK;
}

HRESULT CLogoScene::CreateBulletImage()
{
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Bullet/pistol.png", L"Bullet", L"Pistol", 1)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Bullet/heavy.png", L"Bullet", L"Heavy", 1)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Bullet/hit_ground%d.png", L"Bullet", L"HitGround", 10)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Bullet/hit_enemy%d.png", L"Bullet", L"HitEnemy", 10)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Grenade/grenade%d.png", L"Grenade", L"Grenade", 17)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Grenade/grenadeeffect%d.png", L"Grenade", L"GrenadeEffect", 27)))
		return E_FAIL;

	//적총알
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Enemy/Arabian/Bullet/sword%d.png", L"Sword", L"Sword", 30)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Enemy/Arabian/Bullet/sword_landing.png", L"Sword", L"Landing", 1)))
		return E_FAIL;

	//보스 부스터
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Enemy/Boss/Bullet/booster_1ready%d.png", L"Booster", L"Ready1", 3)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Enemy/Boss/Bullet/booster_2ready%d.png", L"Booster", L"Ready2", 6)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Enemy/Boss/Bullet/booster_3ready%d.png", L"Booster", L"Ready3", 17)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Enemy/Boss/Bullet/booster_attack%d.png", L"Booster", L"Attack", 6)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Enemy/Boss/Bullet/booster_normal%d.png", L"Booster", L"Normal", 4)))
		return E_FAIL;
	//보스 문(적소환)
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Enemy/Boss/Bullet/boss_door%d.png", L"Door", L"Open", 7)))
		return E_FAIL;
	return S_OK;
}

HRESULT CLogoScene::CreateEnemyImage()
{
	//아라비안
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Enemy/Arabian/arabian_1death%d.png", L"Arabian", L"Death1", 20)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Enemy/Arabian/arabian_2death%d.png", L"Arabian", L"Death2", 13)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Enemy/Arabian/arabian_attack%d.png", L"Arabian", L"Attack", 17)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Enemy/Arabian/arabian_backstep%d.png", L"Arabian", L"BackStep", 4)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Enemy/Arabian/arabian_jump%d.png", L"Arabian", L"Jump", 11)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Enemy/Arabian/arabian_landing%d.png", L"Arabian", L"Landing", 2)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Enemy/Arabian/arabian_prepare_attack%d.png", L"Arabian", L"Prepare", 6)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Enemy/Arabian/arabian_shuffle%d.png", L"Arabian", L"Shuffle", 6)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Enemy/Arabian/arabian_throwing%d.png", L"Arabian", L"Throwing", 19)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Enemy/Arabian/arabian_turnR%d.png", L"Arabian", L"TurnR", 2)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Enemy/Arabian/arabian_run%d.png", L"Arabian", L"Run", 12)))
		return E_FAIL;

	//보스
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Enemy/Boss/boss_boosterL.png", L"BoosterL", L"Normal", 1)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Enemy/Boss/boss_boosterL_break%d.png", L"BoosterL", L"Break", 6)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Enemy/Boss/boss_boosterR.png", L"BoosterR", L"Normal", 1)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Enemy/Boss/boss_boosterR_break%d.png", L"BoosterR", L"Break", 6)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Enemy/Boss/boss_engineL%d.png", L"EngineL", L"Normal", 3)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Enemy/Boss/boss_engineL_attack%d.png", L"EngineL", L"Attack", 2)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Enemy/Boss/boss_engineR%d.png", L"EngineR", L"Normal", 3)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Enemy/Boss/boss%d.png", L"Boss", L"", 7)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Enemy/Boss/boss_death.png", L"Boss", L"Death", 1)))
		return E_FAIL;

	return S_OK;
}

HRESULT CLogoScene::CreateNpcImage()
{
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Npc/npc_1free%d.png", L"Npc", L"Free1", 4)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Npc/npc_1wait%d.png", L"Npc", L"Wait1", 8)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Npc/npc_2free%d.png", L"Npc", L"Free2", 3)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Npc/npc_2wait%d.png", L"Npc", L"Wait2", 18)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Npc/npc_give%d.png", L"Npc", L"Give", 5)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Npc/npc_giving%d.png", L"Npc", L"Giving", 7)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Npc/npc_jump%d.png", L"Npc", L"Jump", 8)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Npc/npc_move%d.png", L"Npc", L"Move", 11)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Npc/npc_run%d.png", L"Npc", L"Run", 8)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Npc/npc_salute%d.png", L"Npc", L"Salute", 14)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Npc/npc_turnR%d.png", L"Npc", L"TurnR", 2)))
		return E_FAIL;
	return S_OK;
}

HRESULT CLogoScene::CreateItemImage()
{
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Item/heavy.png", L"Heavy", L"", 1)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Item/heavy_death.png", L"Heavy", L"Death", 1)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Item/grenade%d.png", L"Grenade", L"", 6)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Item/grenade_death.png", L"Grenade", L"Death", 1)))
		return E_FAIL;
	return S_OK;
}

HRESULT CLogoScene::CreateEffectImage()
{

	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Effect/wood%d.png", L"Effect", L"Wood", 7)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Effect/blood%d.png", L"Effect", L"Blood2", 8)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Effect/blood2%d.png", L"Effect", L"Blood1", 10)))
		return E_FAIL;

	//폭발
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Effect/bigboom%d.png", L"Effect", L"BigBoom", 28)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Effect/mediumboom%d.png", L"Effect", L"MediumBoom", 28)))
		return E_FAIL;

	//보스 부스터공격 끝모션
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Effect/booster%d.png", L"Effect", L"Booster", 16)))
		return E_FAIL;

	//보스 부스터 후폭풍
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Effect/blast_attack%d.png", L"Blast", L"Attack", 6)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Effect/blast_attackend%d.png", L"Blast", L"AttackEnd", 4)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Effect/blast_normal%d.png", L"Blast", L"Normal", 6)))
		return E_FAIL;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Stage/Effect/blast_ready%d.png", L"Blast", L"Ready", 6)))
		return E_FAIL;
	return S_OK;
}

HRESULT CLogoScene::OnInit()
{
	m_fSceneChangeTime = 0;
	if (FAILED(SINGLE(CTextureMgr)->InsertTexture(
		L"../Resource/Texture/Logo/logo.png"
		, L"Logo")))
		return E_FAIL;
	return S_OK;
}

int CLogoScene::OnUpdate()
{
	m_fSceneChangeTime += DeltaTime;
	if (m_fSceneChangeTime >= 3.0f)
	{
		if (FAILED(CreatePlayerImage()))
			return RESULT_GAME_EXIT;
		if (FAILED(CreateBulletImage()))
			return RESULT_GAME_EXIT;
		if (FAILED(CreateEnemyImage()))
			return RESULT_GAME_EXIT;
		if (FAILED(CreateNpcImage()))
			return RESULT_GAME_EXIT;
		if (FAILED(CreateItemImage()))
			return RESULT_GAME_EXIT;
		if (FAILED(CreateEffectImage()))
			return RESULT_GAME_EXIT;
		return RESULT_SCENE_SELECT;
	}
	return RESULT_NONE;
}

void CLogoScene::OnRender()
{
	D3DXMATRIX matTrans;
	const TEXINFO* pTex = SINGLE(CTextureMgr)->GetTexture(
		L"Logo");
	D3DXMatrixTranslation(&matTrans,
		WINSIZEX/2,
		WINSIZEY/2,
		0.f);
	SINGLE(CDevice)->GetSprite()->SetTransform(&matTrans);
	SINGLE(CDevice)->GetSprite()->Draw(
		pTex->pTexture, NULL, &D3DXVECTOR3(133,88,0), 0,
		D3DCOLOR_ARGB(255, 255, 255, 255));
	
}

void CLogoScene::OnRelease()
{

}
