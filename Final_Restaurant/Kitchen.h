#pragma once
#include <AI.h>
#include <REngine.h>

class Kitchen : public AI::Entity
{
public:
	Kitchen(AI::AIWorld& world);
	void Load();
	void Unload();

	void Update(float deltaTime);
	void Render();
	void DebugRender();
	
	bool GetFood() { return true; }

private:
	Texture2D mTexture;

};