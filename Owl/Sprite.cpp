#include "PCH.h"
#include "Sprite.h"

#include "Application.h"

const float Layer::Front  = 0.00f;
const float Layer::Upper  = 0.25f;
const float Layer::Middle = 0.50f;
const float Layer::Lower  = 0.75f;
const float Layer::Back   = 0.99f;

Sprite::Sprite(std::string FilePath)
{
    m_Image = new Image(FilePath);
    m_bLocalImage = true;

    m_Size = { m_Image->GetSize()[0], m_Image->GetSize()[1] };
    m_SpriteData.Texture = m_Image->GetTexture();
}

Sprite::Sprite(Image* Image)
{
    m_Image = Image;
    m_bLocalImage = false;

    m_Size = { m_Image->GetSize()[0], m_Image->GetSize()[1] };
    m_SpriteData.Texture = m_Image->GetTexture();
}

Sprite::~Sprite()
{
    if (m_bLocalImage) { delete m_Image; }
}

std::array<unsigned int, 2>& Sprite::GetSize()
{
    return m_Size;
}

void Sprite::Draw(float X, float Y, float Z)
{
    m_SpriteData.X = X;
    m_SpriteData.Y = Y;
    m_SpriteData.Depth = Z;

    m_SpriteData.Scale = 1.0f;
    m_SpriteData.Rotation = 0.0f;
    m_SpriteData.Size[0] = m_Image->GetSize()[0];
    m_SpriteData.Size[1] = m_Image->GetSize()[1];

    Application::s_Renderer->Draw(&m_SpriteData);
}
