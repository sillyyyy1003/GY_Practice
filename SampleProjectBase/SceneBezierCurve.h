#ifndef __SCENE_BEZIER_CURVE_H__
#define __SCENE_BEZIER_CURVE_H__

#include "SceneBase.hpp"
#include "DirectXTex/SimpleMath.h"

#include <vector>

#include "Ball.h"

class SceneBezierCurve : public SceneBase
{
public:
	void Init();
	void Uninit();
	void Update(float tick);
	void Draw();
private:
	float m_time = 0.0f;
	float m_speed = 1.0f;

	std::vector<DirectX::XMFLOAT3> m_positions;

	Ball m_ball;

	DirectX::XMFLOAT3 GetBezierCurvePosition(float t);
	DirectX::XMFLOAT3 GetBezeirCurveVelocity(float t);
};

#endif // __SCENE_BEZIER_CURVE_H__