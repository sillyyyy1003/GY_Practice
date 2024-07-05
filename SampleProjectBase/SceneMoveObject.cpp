#include "SceneMoveObject.h"
#include "Model.h"
#include "CameraBase.h"
#include "LightBase.h"
#include "Input.h"

void SceneMoveObject::Init()
{
	// “™‘¬’¼ü‰^“®
	ball_1.InitPosition(DirectX::XMFLOAT3(-10.0f, 0.0f, 0.0f));
	ball_1.SetSpeed(3.0f);
	ball_1.SetColor({ 1, 0, 0, 1 });

	// “™‰Á‘¬“x‰^“®
	ball_2.InitPosition(DirectX::XMFLOAT3(-10.0f, 0.0f, -2.0f));
	ball_2.SetAcceleration(1.0f);
	ball_2.SetSpeed(1.0f);
	ball_2.SetColor({ 0, 1, 0, 1 });

	// Ž©—R—Ž‰º‰^“®
	ball_3.InitPosition(DirectX::XMFLOAT3(0.0f, 10.0f, -4.0f));
	ball_3.SetColor({ 0, 0, 1, 1 });

	// ‚’¼“Š‚°ã‚°
	ball_4.InitPosition(DirectX::XMFLOAT3(0.0f, 5.0f, -6.0f));
	ball_4.SetSpeed(10.0f);
	ball_4.SetColor({ 1, 0, 1, 1 });

	// …•½“ŠŽË
	ball_5.InitPosition(DirectX::XMFLOAT3(-5.0f, 8.0f, -8.0f));
	ball_5.SetSpeed(10.0f);
	ball_5.SetColor({ 0, 1, 1, 1 });

	// ŽÎ•û“ŠŽË
	ball_6.InitPosition(DirectX::XMFLOAT3(-8.0f, 0.0f, -10.0f));
	ball_6.SetSpeed(15.0f);
	ball_6.SetColor(DirectX::XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f));
	

	// +•ûŒü–Úˆó
	ball_7.InitPosition(DirectX::XMFLOAT3(10.0f, 0.0f, 0.0f));
	ball_7.SetColor(DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));
	ball_8.InitPosition(DirectX::XMFLOAT3(0.0f, 10.0f, 0.0f));
	ball_8.SetColor(DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f));
	ball_9.InitPosition(DirectX::XMFLOAT3(0.0f, 0.0f, 10.0f));
	ball_9.SetColor(DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f));
}

void SceneMoveObject::Uninit()
{
}

void SceneMoveObject::Update(float tick)
{
	// ŽžŠÔXV
	m_time += tick;
	ball_1.m_time += tick;
	ball_2.m_time += tick;
	ball_3.m_time += tick;
	ball_4.m_time += tick;
	ball_5.m_time += tick;
	ball_6.m_time += tick;

	// ‰Û‘è”ÍˆÍ ----------------------------------------------------------

	// “™‘¬’¼ü‰^“®
	ball_1.m_pos.x = ball_1.m_time * ball_1.m_speed;

	// “™‰Á‘¬“x‰^“®
	ball_2.m_pos.x = ball_2.m_speed * ball_2.m_time + 0.5 * ball_2.m_acceleration * ball_2.m_time * ball_2.m_time;

	// Ž©—R—Ž‰º‰^“®
	ball_3.m_pos.y = -0.5 * 9.8 * ball_3.m_time * ball_3.m_time;

	// ‚’¼“Š‚°ã‚°
	ball_4.m_pos.y = ball_4.m_speed * ball_4.m_time - 0.5 * 9.8 * ball_4.m_time * ball_4.m_time;

	// …•½“ŠŽË
	ball_5.m_pos.x = ball_5.m_time * ball_5.m_speed;
	ball_5.m_pos.y = - 0.5 * 9.8 * ball_5.m_time * ball_5.m_time;

	//// ŽÎ•û“ŠŽË
	int deg = 60;				// “ŠŽËŠp“x
	deg = deg * XM_PI / 180.0f; //ƒ‰ƒWƒAƒ“‚É•ÏŠ·
	ball_6.m_pos.x = cos(deg) * ball_6.m_speed * ball_6.m_time;
	ball_6.m_pos.y = sin(deg) * ball_6.m_speed * ball_6.m_time - 0.5 * 9.8 * ball_6.m_time * ball_6.m_time;

	// -------------------------------------------------------------------
 
	// ˆê’èŽžŠÔŒãƒŠƒZƒbƒg
	if (RESET_TIME != 0)
	{
		if (ball_1.m_time >= RESET_TIME) {
			ball_1.m_pos = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
			ball_1.m_time = 0.0f;
		}
		if (ball_2.m_time >= RESET_TIME) {
			ball_2.m_pos = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
			ball_2.m_time = 0.0f;
		}
		if (ball_3.m_time >= RESET_TIME){
			ball_3.m_pos = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
			ball_3.m_time = 0.0f;
		}
		if (ball_4.m_time >= RESET_TIME) {
			ball_4.m_pos = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
			ball_4.m_time = 0.0f;
		}
		if (ball_5.m_time >= RESET_TIME) {
			ball_5.m_pos = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
			ball_5.m_time = 0.0f;
		}
		if (ball_6.m_time >= RESET_TIME) {
			ball_6.m_pos = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
			ball_6.m_time = 0.0f;
		}
	}
}

void SceneMoveObject::Draw()
{
	ball_1.Draw();
	ball_2.Draw();
	ball_3.Draw();
	ball_4.Draw();
	ball_5.Draw();
	ball_6.Draw();
	ball_7.Draw();
	ball_8.Draw();
	ball_9.Draw();
}
