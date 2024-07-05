#ifndef __BALL_H__
#define __BALL_H__

#include "DirectXTex/SimpleMath.h"
#include <vector>

#pragma once
// 球クラス
class Ball
{
public:
	Ball();
	Ball(DirectX::XMFLOAT3 pos);
	void SetColor(DirectX::XMFLOAT4 color);
	void InitPosition(DirectX::XMFLOAT3 pos);

	void SetSpeed(float speed);
	void SetAcceleration(float acceleration);

	void AddPos(DirectX::XMFLOAT3 pos);

	void Update(float tick);
	void Draw();

	bool HitSphere(Ball b);			// ボール同士の当たり判定
	float GetRadius();				// 球の半径を取得
	DirectX::XMFLOAT3 GetPosition();

	//追加
	void SetScale(float scale);
	void Fade(float alpha) { m_color.w -= alpha; };
	float GetAlpha() { return m_color.w; };
	DirectX::XMFLOAT4 GetColor() { return m_color; };

public:

	bool isInput = false;
	DirectX::XMFLOAT3 m_basePos;	// 初期座標
	DirectX::XMFLOAT3 m_pos;
	DirectX::XMFLOAT3 m_speedVec;
	float m_time = 0.0f;			// 時間
	float m_speed = 0.0f;			// 速度
	float m_acceleration = 0.0f;	// 加速度
	float m_mass = 1.0f;
	bool isHit = false;
	//追加
	bool isActive = true;
	float mRange = 0.0f;

private:
	DirectX::XMFLOAT4X4 m_mat;		// ワールド行列
	DirectX::XMFLOAT4 m_color;		// 球の色
	DirectX::XMFLOAT3 m_scale;		// 球のサイズ
	float m_baseRadius = 0.5f;		// 半径

	const float m_gravity = 9.8f;	// 重力
};

#endif // __BALL_H__