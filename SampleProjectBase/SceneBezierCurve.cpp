#include "SceneBezierCurve.h"
#include "Geometory.h"
#include "DebugLog.h"
#include "math.h"

using namespace DirectX::SimpleMath;

void SceneBezierCurve::Init()
{
	m_positions.push_back(DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f));	//Q0
	m_positions.push_back(DirectX::XMFLOAT3(2.0f, 4.0f, 0.0f));	//Q1
	m_positions.push_back(DirectX::XMFLOAT3(6.0f, 4.0f, 0.0f));	//Q2
	m_positions.push_back(DirectX::XMFLOAT3(8.0f, 0.0f, 0.0f));	//Q3

}
void SceneBezierCurve::Uninit()
{

}
void SceneBezierCurve::Update(float tick)
{
	m_time += tick;

	m_ball.m_pos = GetBezierCurvePosition(m_time / 5);

	if (m_time > 5)
	{
		m_time = 0;
	}


}
void SceneBezierCurve::Draw()
{
	DirectX::XMFLOAT3 start;
	DirectX::XMFLOAT3 end;
	DirectX::XMFLOAT4 color = DirectX::XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f);

	// 直線表示(デバッグ)
	for (int i=0;i< m_positions.size() -1; i++)
	{
		start = DirectX::XMFLOAT3(m_positions[i].x, m_positions[i].y, m_positions[i].z);
		end = DirectX::XMFLOAT3(m_positions[i+1].x, m_positions[i+1].y, m_positions[i+1].z);
		Geometory::AddLine(start,color,end, color);
	}
	Geometory::DrawLines();

	// 曲線表示
	start = DirectX::XMFLOAT3(m_positions[0].x, m_positions[0].y, m_positions[0].z);
	color = DirectX::XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f);

	float t = 0.0f;
	for (int i = 0; i <= 100; i++)
	{
		end = GetBezierCurvePosition(t);
		Geometory::AddLine(start, color, end, color);
		start = end;
		t += 0.01f;
	}

	Geometory::DrawLines();
	m_ball.Draw();
}

DirectX::XMFLOAT3 SceneBezierCurve::GetBezierCurvePosition(float t)
{
	// ベジェ曲線計算
	DirectX::XMFLOAT3 outpos = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	// 課題範囲--------------------------------------------------------------------------

	outpos.x = pow((1 - t), 3) * m_positions[0].x + 3 * pow((1 - t), 2) * t * m_positions[1].x + 3 * (1 - t) * t * t * m_positions[2].x + pow(t, 3) * m_positions[3].x;
	outpos.y = pow((1 - t), 3) * m_positions[0].y + 3 * pow((1 - t), 2) * t * m_positions[1].y + 3 * (1 - t) * t * t * m_positions[2].y + pow(t, 3) * m_positions[3].y;
	outpos.z = pow((1 - t), 3) * m_positions[0].z + 3 * pow((1 - t), 2) * t * m_positions[1].z + 3 * (1 - t) * t * t * m_positions[2].z + pow(t, 3) * m_positions[3].z;

	// ----------------------------------------------------------------------------------
	return outpos;
}

DirectX::XMFLOAT3 SceneBezierCurve::GetBezeirCurveVelocity(float t)
{
	DirectX::XMFLOAT3 velocity = { 0,0,0 };
	velocity.x = 3 * pow((1 - t), 2) * (m_positions[1].x - m_positions[0].x) + 6 * (1 - t) * t * (m_positions[2].x - m_positions[1].x) + 3 * pow(t, 2) * (m_positions[3].x - m_positions[2].x);
	velocity.y = 3 * pow((1 - t), 2) * (m_positions[1].y - m_positions[0].y) + 6 * (1 - t) * t * (m_positions[2].y - m_positions[1].y) + 3 * pow(t, 2) * (m_positions[3].y - m_positions[2].y);
	velocity.z = 3 * pow((1 - t), 2) * (m_positions[1].z - m_positions[0].z) + 6 * (1 - t) * t * (m_positions[2].z - m_positions[1].z) + 3 * pow(t, 2) * (m_positions[3].z - m_positions[2].z);

	return velocity;
}
