#include "SceneFirework.h"

#include "CameraBase.h"
#include "Model.h"
#include "PointLight.h"
#include "Shader.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

#define M_PI 3.14159265


void SceneFirework::Init()
{
	mLaunch.InitPosition({ 0.f, 0.f, 0.f });
	mLaunch.m_speedVec = { 0,13,0 };
	mLaunch.SetScale(0.2);
	float initSpeed = 2.f;

	//Y軸速度
	for (int i = 0; i < 500; i++)
	{
		Ball ball;

		ball.InitPosition({ 0.f, 0.f, 0.f });

		float theta = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 2.0f * M_PI; // 随机方位角
		float phi = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 2.f * M_PI; // 角度が(0,360)


		float x = cos(phi) * sin(theta) * initSpeed;
		float y = sin(phi) * initSpeed;
		float z = cos(phi) * cos(theta) * initSpeed;
		DirectX::XMFLOAT3 speedVec = { x,y,z };

		ball.SetColor(XMFLOAT4((rand() % 10 + 1) * 0.1f,// 0.4～1(0.1刻み)
			(rand() % 10 + 1) * 0.1f,			// 0.4～1(0.1刻み)
			(rand() % 10 + 1) * 0.1f,			// 0.4～1(0.1刻み)
			1.0f));

		//if (phi > 4.0f * M_PI / 3.f)
		//{
		//	ball.SetColor(Color(1.0f, 0.0f, 0.0f, 1.0f));
		//}
		//else if (phi >= 2.f * M_PI / 3.f && phi <= 4.0f * M_PI / 3.f)
		//{
		//	ball.SetColor(Color(0.0f, 1.0f, 0.0f, 1.0f));
		//}else
		//{
		//	ball.SetColor(Color(0.0f, 0.0f, 1.0f, 1.0f));
		//}
		//

		ball.m_speedVec = speedVec;
		ball.SetScale(0.05);
		ball.mRange = 10.f;
		mFirework.push_back(ball);

		std::string name = "PointLight" + std::to_string(i);
		PointLight* pPointLight = CreateObj<PointLight>(name.c_str());
		pPointLight->SetRange(ball.mRange);
		pPointLight->SetPos(ball.m_pos);
		pPointLight->SetDiffuse(ball.GetColor());
		
	}

	Shader* shader[] = {
	CreateObj<VertexShader>("VS_WorldPosition"),
	CreateObj<PixelShader>("PS_PointLight"),
	};
	const char* file[] = {
		"Assets/Shader/VS_WorldPosition.cso",
		"Assets/Shader/PS_PointLight.cso",
	};

	int shaderNum = _countof(shader);
	for (int i = 0; i < shaderNum; ++i)
	{
		if (FAILED(shader[i]->Load(file[i])))
		{
			MessageBox(NULL, file[i], "Shader Error", MB_OK);
		}
	}
}

void SceneFirework::Uninit()
{
}

void SceneFirework::Update(float tick)
{


	//Phase Up
	if(mLaunch.isActive)
	{
		mLaunch.m_speedVec.y -= 10.f * tick;
		mLaunch.m_pos = mLaunch.m_pos + mLaunch.m_speedVec * tick;

		//Set particle set;
		if (mLaunch.m_speedVec.y <= 0)
		{
			isExploded = true;
			mLaunch.isActive = false;
			for (auto& ball : mFirework)
			{
				ball.m_pos = mLaunch.m_pos;
			
			}
		}
		return;
	}
	
	m_time += tick;

	//Phase Bloom

	for (auto& it : mFirework)
	{

		if(it.isActive)
		{
			//抵抗を計算
			it.m_speedVec.y -= 3.f * tick;

			it.Fade(tick * 1);
			it.mRange -= tick * 6;
			//制限
			it.mRange = max(it.mRange, 0.01f);
			
			//lifetime過ぎたら描画しないように
			if (it.GetAlpha() <= 0.f)
			{
				it.isActive = false;
				isFinish = true;
				return;
			}

			it.m_pos = it.m_pos + it.m_speedVec * tick;
		}
	}



}

void SceneFirework::Draw()
{
	// 各種取得
	Model* pModel = GetObj<Model>("Model");
	CameraBase* pCamera = GetObj<CameraBase>("Camera");
	LightBase* pLight = GetObj<LightBase>("Light");


	// 定数バッファに渡す行列の情報
	DirectX::XMFLOAT4X4 mat[3];
	DirectX::XMStoreFloat4x4(&mat[0], DirectX::XMMatrixIdentity());
	mat[1] = pCamera->GetView();
	mat[2] = pCamera->GetProj();

	DirectX::XMFLOAT3 lightDir =
		pLight->GetDirection();
	DirectX::XMFLOAT4 light[] = {
		pLight->GetDiffuse(),
		pLight->GetAmbient(),
		{lightDir.x, lightDir.y, lightDir.z, 0.0f}
	};

	// 定数バッファに渡すポイントライトの情報
	struct Light {
		DirectX::XMFLOAT4 color;
		DirectX::XMFLOAT3 pos;
		float range;
	};


	Light lights[1000];
	//打ち上げの部分
	std::string name = "PointLight" + std::to_string(0);
	PointLight* pPointLight = GetObj<PointLight>(name.c_str());
	lights[0].color = mLaunch.GetColor();
	lights[0].pos = mLaunch.m_pos;
	lights[0].range = 5.f;

	//Particle
	if (isExploded)
	{
		for (int i = 1; i < mFirework.size(); ++i)
		{
		std::string name = "PointLight" + std::to_string(i);
		PointLight* pPointLight = GetObj<PointLight>(name.c_str());

		lights[i].color = { pPointLight->GetDiffuse().x,pPointLight->GetDiffuse().y ,pPointLight->GetDiffuse().z,mFirework[i - 1].GetAlpha() };
		lights[i].pos = mFirework[i].m_pos;
		lights[i].range = mFirework[i].mRange;
		}
	}

	Shader* shader[] = 
	{
		GetObj<Shader>("VS_WorldPosition"),
		GetObj<Shader>("PS_PointLight"),
	};

	// モデルの表示(点光源)
	DirectX::XMStoreFloat4x4(&mat[0], DirectX::XMMatrixTranspose(
		DirectX::XMMatrixTranslation(0.0f, 0.0f, 0.0f)
	));

	int isLight[] = { 1,0,0,0 };

	if (!isExploded)
	{
		isLight[0] = 0;
		isLight[1] = 1;
	}else
	{
		isLight[0] = 1;
		isLight[1] = mFirework.size();
	}

	if(isFinish)
	{
		isLight[0] = 0;
		isLight[1] = 0;
	}
	

	shader[0]->WriteBuffer(0, mat);
	shader[1]->WriteBuffer(0, lights);
	shader[1]->WriteBuffer(1, isLight);

	pModel->SetVertexShader(shader[0]);
	pModel->SetPixelShader(shader[1]);
	pModel->Draw();


	if (mLaunch.isActive)
	{
		mLaunch.Draw();
	}
	else
	{
		for (auto& it : mFirework)
		{
			if (it.isActive)
			{
				it.Draw();
			}
		
		}
	}

}
