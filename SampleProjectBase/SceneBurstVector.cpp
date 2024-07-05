//#include <DirectXMath.h>
#include "math.h"
#include "Geometory.h"
#include "DebugLog.h"
#include "SceneBurstVector.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

void SceneBurstVector::Init()
{
	Ball b1 = Ball(XMFLOAT3(-10.0f, 0.0f, 0.0f));
	b1.m_speedVec = (XMFLOAT3(5.0f, 0.0f, 0.0f));
	b1.SetColor(XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));
	m_Balls.push_back(b1);

	Ball b2 = Ball(XMFLOAT3(10.0f, 0.0f, 0.0f));
	b2.m_speedVec = (XMFLOAT3(-5.0f, 0.0f, 0.0f));
	b2.SetColor(XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f));
	m_Balls.push_back(b2);

	Ball b3 = Ball(XMFLOAT3(-5.0f, 0.0f, 10.0f));
	b3.m_speedVec = (XMFLOAT3(3.0f, 0.0f, -5.0f));
	m_Balls.push_back(b3);
}
void SceneBurstVector::Uninit()
{

}
void SceneBurstVector::Update(float tick)
{
	//ŽžŠÔXV
	m_time += tick;

	for (auto& ball : m_Balls)
	{
		ball.m_time += m_time;
	}


	// ‰Û‘è”ÍˆÍ--------------------------------------------------------------------------

	for (auto i = m_Balls.begin(); i != m_Balls.end(); ++i)
	{
		for (auto j = i + 1; j != m_Balls.end(); ++j)
		{
			if(i->HitSphere(*j))
			{
				float e = 0.7f;
				DirectX::XMFLOAT3 v1 = ((i->m_mass - e * j->m_mass) * i->m_speedVec + (1 + e) * j->m_mass * j->m_speedVec) / (i->m_mass + j->m_mass);
			
				DirectX::XMFLOAT3 v2 = ((j->m_mass - e * i->m_mass) * j->m_speedVec + (1 + e) * i->m_mass * i->m_speedVec) / (i->m_mass + j->m_mass);

				i->m_speedVec = v1;
				j->m_speedVec = v2;
			}
		}
		
	}


	//“–‚½‚è”»’è


	for (auto& ball : m_Balls)
	{
		ball.m_pos = ball.m_pos + ball.m_speedVec * tick;
		
	}

	// ----------------------------------------------------------------------------------
}
void SceneBurstVector::Draw()
{
	for (int i = 0; i < m_Balls.size(); i++)
	{
		m_Balls[i].Draw();
	}
}
