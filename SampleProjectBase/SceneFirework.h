#ifndef __SCENE_FIREWORK_H__
#define __SCENE_FIREWORK_H__
#include "SceneBase.hpp"
#include "Ball.h"
#include <vector>

class SceneFirework:public SceneBase
{
public:
	void Init();
	void Uninit();
	void Update(float tick);
	void Draw();

private:

	float m_time = 0;

	Ball mLaunch;

	std::vector<Ball> mFirework;

	bool isExploded = false;
	bool isFinish = false;

};

#endif // __SCENE_FIREWORK_H__