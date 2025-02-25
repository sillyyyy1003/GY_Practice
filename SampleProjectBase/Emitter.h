#ifndef __EMITTER_H__
#define __EMITTER_H__

#include <vector>
#include <random>

#include "Particle.h"
#include "DirectXTex/SimpleMath.h"

#pragma once
// 球クラス
class Emitter
{
public:
	Emitter(DirectX::XMFLOAT3 pos);
	void Init();
	void Update(float tick);
	void Drow();
	void CreateParticle();	//パーティクル生成
	bool RecycleParticle();	//パーティクル再利用
	void SetVector(float minx, float maxx, float miny, float maxy, float minz, float maxz); // パーティクル速度ベクトル設定
	void SetGeneratNum(float min, float max);
	void SetGeneratTime(float time);
private:
	const int m_particleMax = 1000;		// 最大生成数
	DirectX::XMFLOAT4X4 m_mat;			// ワールド行列

	float m_time = 0.0f;				// 経過時間
	std::vector<Particle> m_particles;	// パーティクル管理配列
	int m_generatNum_min = 1;			// 生成数
	int m_generatNum_max = 1;
	float m_generatTime = 0.1f;		// 生成間隔
	float m_generatTimeCount = 0.0f; 

	// 乱数関係
	std::random_device rd;
	std::mt19937 mt;
	float Rand_f(float min,float max);	// min~maxの間の値を返す乱数生成関数
public:
	DirectX::XMFLOAT3 m_pos;		// 初期座標
	// 生成用パラメーター ------------------------------------------------------
	float lifeTime_min = 1.0f;		// 生存時間最短
	float lifeTime_max = 1.0f;		// 生存時間最長
	float gravity = 9.8f;			// 重力
	DirectX::XMFLOAT4 color_start = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);	// 開始時の色
	DirectX::XMFLOAT4 color_end = DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);;	// 終了時の色
	float colorChangeStartRate = 0.8f;		// 色変化開始 0.0~1.0

	float vecx_min = 0.0f;		// 射出ベクトル
	float vecx_max = 0.0f;
	float vecy_min = 0.0f;
	float vecy_max = 0.0f;
	float vecz_min = 0.0f;
	float vecz_max = 0.0f;

	float deg_min = 0.0f;		//射出角度
	float deg_max = 0.0f;

	float mass = 1.0f;			// 質量
	float refRate = 1.0f;		// 反発係数
	// --------------------------------------------------------------------------
};

#endif // __EMITTER_H__