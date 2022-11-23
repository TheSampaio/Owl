#pragma once

#include "Graphics.h"
#include "Sprite.h"
#include "Window.h"

struct Vertex
{
	DirectX::XMFLOAT3 Position;
	DirectX::XMFLOAT4 Color;
	DirectX::XMFLOAT2 Texture;
};

class Renderer
{
public:
	Renderer();
	~Renderer();

	bool Initialize(Window*& Window, Graphics*& Graphics);
	void Draw(SpriteData* Sprite);
	void Render();

private:
	ID3D11InputLayout* m_InputLayout;
	ID3D11VertexShader* m_VertexShader;
	ID3D11PixelShader* m_PixelShader;
	ID3D11RasterizerState* m_RasterizerState;
	ID3D11SamplerState* m_SamplerState;
	ID3D11Buffer* m_VertexBuffer;
	ID3D11Buffer* m_IndexBuffer;
	ID3D11Buffer* m_ConstantBuffer;
	unsigned int m_VertexBufferPosition;

	static const unsigned short s_MinBatchSize;
	static const unsigned short s_MaxBatchSize;
	static const unsigned short s_SpriteVertices;
	static const unsigned short s_SpriteIndices;

	std::vector<SpriteData*> SpriteVector;
	
	void RenderBatch(ID3D11ShaderResourceView* Texture, SpriteData** Sprites, unsigned int Count);
};
