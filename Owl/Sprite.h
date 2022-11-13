#pragma once

#include "Image.h"

struct SpriteData
{
	float X, Y;
	float Rotation, Scale;
	float Depth;
	std::array<unsigned int, 2> Size;
	ID3D11ShaderResourceView* Texture;
};

struct Layer
{
	static const float Front;
	static const float Upper;
	static const float Middle;
	static const float Lower;
	static const float Back;
};

class Sprite
{
public:
	Sprite(std::string FilePath);
	Sprite(Image* Image);
	~Sprite();

	std::array<unsigned int, 2>& GetSize();
	void Draw(float X, float Y, float Z = Layer::Middle);

private:
	SpriteData m_SpriteData;
	bool m_bLocalImage;
	Image* m_Image;

	std::array<unsigned int, 2> m_Size;
};
