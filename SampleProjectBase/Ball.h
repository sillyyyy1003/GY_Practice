#ifndef __BALL_H__
#define __BALL_H__

#include "DirectXTex/SimpleMath.h"
#include <vector>

#pragma once
// ���N���X
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

	bool HitSphere(Ball b);			// �{�[�����m�̓����蔻��
	float GetRadius();				// ���̔��a���擾
	DirectX::XMFLOAT3 GetPosition();

	//�ǉ�
	void SetScale(float scale);
	void Fade(float alpha) { m_color.w -= alpha; };
	float GetAlpha() { return m_color.w; };
	DirectX::XMFLOAT4 GetColor() { return m_color; };

public:

	bool isInput = false;
	DirectX::XMFLOAT3 m_basePos;	// �������W
	DirectX::XMFLOAT3 m_pos;
	DirectX::XMFLOAT3 m_speedVec;
	float m_time = 0.0f;			// ����
	float m_speed = 0.0f;			// ���x
	float m_acceleration = 0.0f;	// �����x
	float m_mass = 1.0f;
	bool isHit = false;
	//�ǉ�
	bool isActive = true;
	float mRange = 0.0f;

private:
	DirectX::XMFLOAT4X4 m_mat;		// ���[���h�s��
	DirectX::XMFLOAT4 m_color;		// ���̐F
	DirectX::XMFLOAT3 m_scale;		// ���̃T�C�Y
	float m_baseRadius = 0.5f;		// ���a

	const float m_gravity = 9.8f;	// �d��
};

#endif // __BALL_H__