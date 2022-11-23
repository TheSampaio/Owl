#pragma once

#include "Texture.h"

class Image
{
public:
	Image(std::string FilePath);
	~Image();

	inline std::array<unsigned short, 2>& GetSize()     { return m_Size; };
	inline ID3D11ShaderResourceView* GetTexture() const { return m_TextureView; }

private:
	ID3D11ShaderResourceView* m_TextureView;
	unsigned int m_Width, m_Height;

	std::array<unsigned short, 2> m_Size;
};

