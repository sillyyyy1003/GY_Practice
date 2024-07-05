#ifndef __SCENE_MOVE_H__
#define __SCENE_MOVE_H__

#include "SceneBase.hpp"
#include "Ball.h"

class SceneMoveObject: public SceneBase
{
public:
	void Init();
	void Uninit();
	void Update(float tick);
	void Draw();
private:
	float m_time = 0.0f;
	float speed = 1.0f;
	const float G = 9.8f;	// �d��
	const float RESET_TIME = 8.0;	// ���̃��Z�b�g����

	Ball ball_1;	// ���������^��
	Ball ball_2;	// �������x�^��
	Ball ball_3;	// ���R�����^��
	Ball ball_4;	// ���������グ
	Ball ball_5;	// ��������
	Ball ball_6;	// �Ε�����
	Ball ball_7;	// �ڈ�
	Ball ball_8;	// �ڈ�
	Ball ball_9;	// �ڈ�
};

#endif // __SCENE_MOVE_H__