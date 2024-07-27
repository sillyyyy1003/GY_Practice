#ifndef __SCENE_SPRING_H__
#define __SCENE_SPRING_H__

#include "SceneBase.hpp"
#include "DirectXTex/SimpleMath.h"
#include "Ball.h"

#include <vector>

class SceneSpring : public SceneBase
{
public:
	void Init();
	void Uninit();
	void Update(float tick);
	void Draw();
private:
	float m_time = 0.0f;
	float m_speed = 1.0f;

	DirectX::XMFLOAT3 m_springPos;
	DirectX::XMFLOAT3 m_ballPos;

	const float DEFAULT_LENGTH = 5.0f;			// �΂˂̎��R��
	const float SPRING_COEFFICIENT = 1.0f;		// �΂ˌW��
	const float ATT_COEFFICIENT = 0.5f;			// �����W��(Attenuation)
	const float BALL_MASS = 10.0f;				// ����
	DirectX::XMFLOAT3 m_velocity = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);						// ���x
	DirectX::XMFLOAT3 m_gravity_vec = DirectX::XMFLOAT3(0.0f, BALL_MASS * -0.98f, 0.0f);	// �d��(�x�N�g��)
	DirectX::XMFLOAT3 m_acceleration = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);					// �����x
};

#endif // __SCENE_SPRING_H__