#include "SceneSpring.h"
#include "Geometory.h"
#include "Input.h"

#include "DebugLog.h"
using namespace DirectX::SimpleMath;

void SceneSpring::Init()
{
	//m_springPos = DirectX::XMFLOAT3(5.0f, 10.0f, 5.0f);
	//m_ballPos = DirectX::XMFLOAT3(5.0f, 5.0f, 5.0f);

	m_springPos = Vector3(5.0f, 10.0f, 5.0f);
	m_ballPos = Vector3(5.0f, 5.0f, 5.0f);
}
void SceneSpring::Uninit()
{

}
void SceneSpring::Update(float tick)
{
	m_time += tick;
	bool isInput = false;

	if (IsKeyPress(VK_UP)){
		m_ballPos.z += 0.1f;
		isInput = true;
	}
	if (IsKeyPress(VK_LEFT)) {
		m_ballPos.x += -0.1f;
		isInput = true;
	}
	if (IsKeyPress(VK_DOWN)) {
		m_ballPos.z += -0.1f;
		isInput = true;
	}
	if (IsKeyPress(VK_RIGHT)) {
		m_ballPos.x += 0.1f;
		isInput = true;
	}
	if (IsKeyPress(VK_SPACE)) {
		m_ballPos.y += -0.1f;
		isInput = true;
	}

	// ばねの処理-------------------------------------------------------------------------------------
	// スプリングの長さを計算
	//DirectX::XMFLOAT3 springLen = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	Vector3 springLen = Vector3(0.f, 0.f, 0.f);
	springLen = m_ballPos - m_springPos; //ボールの位置 - スプリングの位置
	float len = sqrtf(springLen.x * springLen.x + springLen.y * springLen.y + springLen.z * springLen.z);

	// スプリングのテンションを計算
	float tension = SPRING_COEFFICIENT * (len - DEFAULT_LENGTH);
	DirectX::XMFLOAT3 tensionVec = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	//tensionVec.x = -1.0f * スプリングの長さx軸 * (テンション / スプリングの長さ)
	//tensionVec.y = -1.0f * スプリングの長さy軸 * (テンション / スプリングの長さ)
	//tensionVec.z = -1.0f * スプリングの長さz軸 * (テンション / スプリングの長さ)

	// ここまでばねの処理-------------------------------------------------------------------------------------

	// ボールの処理------------------------------------------------------------------------------------------- 
	// 抵抗力を求める
	DirectX::XMFLOAT3 resistance = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);	// 抵抗力
	//resistance = -速度 * ATT_COEFFICIENT;

	DirectX::XMFLOAT3 resultant = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);	// 合力
	// かかる力を合成（合力＝重力＋張力＋抵抗力）


	// 入力がある場合は以下の処理を止めて球の移動処理に逃がす
	if (isInput){
		return;;
	}

	// 合力と質量から加速度を求める


	// 速度に加速度を加える


	// 速度から座標を移動
	m_ballPos.x += m_velocity.x;
	m_ballPos.y += m_velocity.y;
	m_ballPos.z += m_velocity.z;

	// ここまでボールの処理-------------------------------------------------------------------------------------------
}
void SceneSpring::Draw()
{
	DirectX::XMFLOAT4 color = DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
	Geometory::AddLine(m_springPos, color, m_ballPos, color);
	Geometory::DrawLines();

	// 球の座標行列作成
	DirectX::XMFLOAT4X4 mat;
	DirectX::XMStoreFloat4x4(&mat, DirectX::XMMatrixTranspose(
		DirectX::XMMatrixTranslation(m_ballPos.x, m_ballPos.y, m_ballPos.z)	// 球の座標
	));

	Geometory::SetWorld(mat);		// 行列セット
	Geometory::DrawSphere();		// 球描画
}
