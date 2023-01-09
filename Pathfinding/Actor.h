#pragma once
#include <REngine.h>

class Actor
{

public:
	Actor();
	~Actor();
	
	Actor(REng::Math::Vector2 pos, Texture2D texture)
	{
		mPosition = pos, mTexture = texture;
		mRect.x = 0.f;
		mRect.y = 0.f;
		mRect.width = mTexture.width; // multiply by -1 would flip it
		mRect.height = mTexture.height; //default:show the full texture
	}
	
private:
	REng::Math::Vector2 mPosition;
	Texture2D mTexture;
	Rectangle mRect;

	
};

