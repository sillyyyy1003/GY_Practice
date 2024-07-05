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
	const float G = 9.8f;	// 重力
	const float RESET_TIME = 8.0;	// 球のリセット時間

	Ball ball_1;	// 等速直線運動
	Ball ball_2;	// 等加速度運動
	Ball ball_3;	// 自由落下運動
	Ball ball_4;	// 垂直投げ上げ
	Ball ball_5;	// 水平投射
	Ball ball_6;	// 斜方投射
	Ball ball_7;	// 目印
	Ball ball_8;	// 目印
	Ball ball_9;	// 目印
};

#endif // __SCENE_MOVE_H__