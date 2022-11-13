#include "PCH.h"
#include "Image.h"

#include "Graphics.h"

Image::Image(std::string FilePath)
	: m_TextureView{ nullptr }
{
	D3D11CreateTextureFromFile(Graphics::s_Device, Graphics::s_Context, FilePath.c_str(), nullptr, &m_TextureView, m_Width, m_Height);
	m_Size = { m_Width, m_Height };
}

Image::~Image()
{
	if (m_TextureView)
	{
		ID3D11Resource* Resource = nullptr;
		m_TextureView->GetResource(&Resource);

		if (Resource)
		{
			Resource->Release();
			Resource = nullptr;
		}

		m_TextureView->Release();
		m_TextureView = nullptr;
	}
}
