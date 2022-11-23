#include "PCH.h"
#include "Renderer.h"

const unsigned short Renderer::s_MinBatchSize = 128;
const unsigned short Renderer::s_MaxBatchSize = 4096;
const unsigned short Renderer::s_SpriteVertices = 4;
const unsigned short Renderer::s_SpriteIndices = 6;

Renderer::Renderer()
	: m_InputLayout{ nullptr },  m_VertexShader{ nullptr }, m_PixelShader{ nullptr }, m_RasterizerState{ nullptr },
      m_SamplerState{ nullptr }, m_VertexBuffer{ nullptr }, m_IndexBuffer{ nullptr }, m_ConstantBuffer{ nullptr }
{
	m_VertexBufferPosition = 0;
}

Renderer::~Renderer()
{
    ReleaseComponent(m_ConstantBuffer);
	ReleaseComponent(m_IndexBuffer);
	ReleaseComponent(m_VertexBuffer);
	ReleaseComponent(m_SamplerState);
	ReleaseComponent(m_RasterizerState);
	ReleaseComponent(m_PixelShader);
	ReleaseComponent(m_VertexShader);
	ReleaseComponent(m_InputLayout);
}

bool Renderer::Initialize(Window*& Window, Graphics*& Graphics)
{
	// Vertex shader
	ID3DBlob* VertexShaderSource = nullptr;
	if (FAILED(D3DReadFileToBlob(L"Shaders/Vertex.cso", &VertexShaderSource))) { return false; }
	if (FAILED(Graphics->GetGraphicDevice()->CreateVertexShader(VertexShaderSource->GetBufferPointer(), VertexShaderSource->GetBufferSize(), nullptr, &m_VertexShader))) { return false; }

	// Input layout
	D3D11_INPUT_ELEMENT_DESC InputLayoutDesc[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,       0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	if (FAILED(Graphics->GetGraphicDevice()->CreateInputLayout(InputLayoutDesc, 3, VertexShaderSource->GetBufferPointer(), VertexShaderSource->GetBufferSize(), &m_InputLayout))) { return false; }

	VertexShaderSource->Release();

	// Pixel shader
	ID3DBlob* PixelShaderSource = nullptr;
	if (FAILED(D3DReadFileToBlob(L"Shaders/Pixel.cso", &PixelShaderSource))) { return false; };
	if (FAILED(Graphics->GetGraphicDevice()->CreatePixelShader(PixelShaderSource->GetBufferPointer(), PixelShaderSource->GetBufferSize(), nullptr, &m_PixelShader))) { return false; }

	PixelShaderSource->Release();

    // Rasterizer state
    D3D11_RASTERIZER_DESC RasterizerDesc = {};
    RasterizerDesc.FillMode = D3D11_FILL_SOLID;
    //RasterizerDesc.FillMode = D3D11_FILL_WIREFRAME;
    RasterizerDesc.CullMode = D3D11_CULL_NONE;
    RasterizerDesc.DepthClipEnable = true;

    if (FAILED(Graphics->GetGraphicDevice()->CreateRasterizerState(&RasterizerDesc, &m_RasterizerState))) { return false; }

    // Vertex buffer
    D3D11_BUFFER_DESC VertexBufferDesc = { 0 };
    VertexBufferDesc.ByteWidth = sizeof(Vertex) * s_SpriteVertices * s_MaxBatchSize;
    VertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
    VertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    VertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

    if (FAILED(Graphics->GetGraphicDevice()->CreateBuffer(&VertexBufferDesc, nullptr, &m_VertexBuffer)))
        return false;

    // Index buffer
    D3D11_BUFFER_DESC IndexBufferDesc = { 0 };
    IndexBufferDesc.ByteWidth = sizeof(short) * s_SpriteIndices * s_MaxBatchSize;
    IndexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    IndexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

    std::vector<short> Indices = {};
    Indices.reserve(static_cast<std::vector<short, std::allocator<short>>::size_type>(s_MaxBatchSize) * s_SpriteIndices);

    for (short i = 0; i < s_MaxBatchSize * s_SpriteVertices; i += s_SpriteVertices)
    {
        Indices.push_back(i);
        Indices.push_back(i + 1);
        Indices.push_back(i + 2);

        Indices.push_back(i + 1);
        Indices.push_back(i + 3);
        Indices.push_back(i + 2);
    }

    D3D11_SUBRESOURCE_DATA IndexData = { 0 };
    IndexData.pSysMem = &Indices.front();

    if (FAILED(Graphics->GetGraphicDevice()->CreateBuffer(&IndexBufferDesc, &IndexData, &m_IndexBuffer)))
        return false;

    // Constant buffer
    D3D11_BUFFER_DESC ConstantBufferDesc = { 0 };
    ConstantBufferDesc.ByteWidth = sizeof(DirectX::XMMATRIX);
    ConstantBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
    ConstantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    ConstantBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

    float ScaleX = (Graphics->GetViewport().Width > 0) ? 2.0f / Graphics->GetViewport().Width : 0.0f;
    float ScaleY = (Graphics->GetViewport().Height > 0) ? 2.0f / Graphics->GetViewport().Height : 0.0f;

    DirectX::XMMATRIX TransformMatrix
    (
        ScaleX,  0,       0,    0,
        0,      -ScaleY,  0,    0,
        0,       0,       1,    0,
       -1,       1,       0,    1
    );

    D3D11_SUBRESOURCE_DATA ConstantData = { 0 };
    DirectX::XMMATRIX WorldViewProjection = XMMatrixTranspose(TransformMatrix);
    ConstantData.pSysMem = &WorldViewProjection;

    if (FAILED(Graphics->GetGraphicDevice()->CreateBuffer(&ConstantBufferDesc, &ConstantData, &m_ConstantBuffer))) { return false; }

    // Texture sampler
    D3D11_SAMPLER_DESC SamplerDesc = {};
    SamplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    SamplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    SamplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    SamplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    SamplerDesc.MipLODBias = 0.0f;
    SamplerDesc.MaxAnisotropy = (Graphics->GetGraphicDevice()->GetFeatureLevel() > D3D_FEATURE_LEVEL_9_1) ? 16 : 2;
    SamplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    SamplerDesc.BorderColor[0] = 0.0f;
    SamplerDesc.BorderColor[1] = 0.0f;
    SamplerDesc.BorderColor[2] = 0.0f;
    SamplerDesc.BorderColor[3] = 0.0f;
    SamplerDesc.MinLOD = 0;
    SamplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

    // cria o amostrador da textura
    if (FAILED(Graphics->GetGraphicDevice()->CreateSamplerState(&SamplerDesc, &m_SamplerState))) { return false; }

    // Setup Direct3D's pipeline
    unsigned int VertexStride = sizeof(Vertex);
    unsigned int VertexOffset = 0;

    Graphics->GetGraphicContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &VertexStride, &VertexOffset);
    Graphics->GetGraphicContext()->IASetIndexBuffer(m_IndexBuffer, DXGI_FORMAT_R16_UINT, 0);
    Graphics->GetGraphicContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    Graphics->GetGraphicContext()->IASetInputLayout(m_InputLayout);
    Graphics->GetGraphicContext()->VSSetShader(m_VertexShader, NULL, 0);
    Graphics->GetGraphicContext()->VSSetConstantBuffers(0, 1, &m_ConstantBuffer);
    Graphics->GetGraphicContext()->PSSetShader(m_PixelShader, NULL, 0);
    Graphics->GetGraphicContext()->PSSetSamplers(0, 1, &m_SamplerState);
    Graphics->GetGraphicContext()->RSSetState(m_RasterizerState);

	return true;
}

void Renderer::Draw(SpriteData* Sprite)
{
	SpriteVector.push_back(Sprite);
}

void Renderer::Render()
{
    std::sort(SpriteVector.begin(), SpriteVector.end(), [](SpriteData* A, SpriteData* B) -> bool { return A->Depth > B->Depth; });

    unsigned int SpriteVectorSize = unsigned int(SpriteVector.size());

    if (SpriteVectorSize == 0)
        return;

    ID3D11ShaderResourceView* BatchTexture = nullptr;
    unsigned int BatchStart = 0;

    for (unsigned int i = 0; i < SpriteVectorSize; ++i)
    {
        ID3D11ShaderResourceView* Texture = SpriteVector[i]->Texture;

        if (Texture != BatchTexture)
        {
            if (i > BatchStart)
            {
                RenderBatch(BatchTexture, &SpriteVector[BatchStart], i - BatchStart);
            }

            BatchTexture = Texture;
            BatchStart = i;
        }
    }

    RenderBatch(BatchTexture, &SpriteVector[BatchStart], SpriteVectorSize - BatchStart);

    SpriteVector.clear();
}

void Renderer::RenderBatch(ID3D11ShaderResourceView* Texture, SpriteData** Sprites, unsigned int Count)
{
    Graphics::s_Context->PSSetShaderResources(0, 1, &Texture);

    while (Count > 0)
    {
        unsigned int BatchSize = Count;
        unsigned int RemainingSpace = s_MaxBatchSize - m_VertexBufferPosition;

        if (BatchSize > RemainingSpace)
        {
            if (RemainingSpace < s_MinBatchSize)
            {
                m_VertexBufferPosition = 0;
                BatchSize = (Count < s_MaxBatchSize) ? Count : s_MaxBatchSize;
            }

            else
            {
                BatchSize = RemainingSpace;
            }
        }

        D3D11_MAP MapType = (m_VertexBufferPosition == 0) ? D3D11_MAP_WRITE_DISCARD : D3D11_MAP_WRITE_NO_OVERWRITE;
        D3D11_MAPPED_SUBRESOURCE MappedBuffer;
        Graphics::s_Context->Map(m_VertexBuffer, 0, MapType, 0, &MappedBuffer);

        Vertex* Vertices = static_cast<Vertex*>(MappedBuffer.pData) + static_cast<unsigned long long>(m_VertexBufferPosition) * s_SpriteVertices;

        for (unsigned int i = 0; i < BatchSize; ++i)
        {
            using namespace DirectX;

            XMVECTOR Size = XMVectorMergeXY(XMLoadInt(&Sprites[i]->Size[0]), XMLoadInt(&Sprites[i]->Size[1]));
            XMVECTOR TextureSize = XMConvertVectorUIntToFloat(Size, 0);
            XMVECTOR InverseTextureSize = XMVectorReciprocal(TextureSize);

            XMFLOAT2 PositionXY(Sprites[i]->X, Sprites[i]->Y);
            float Scale = Sprites[i]->Scale;
            XMFLOAT2 Center(0.0f, 0.0f);
            float Rotation = Sprites[i]->Rotation;
            float LayerDepth = Sprites[i]->Depth;

            XMVECTOR Source = XMVectorSet(0, 0, 1, 1);
            XMVECTOR Destination = XMVectorPermute<0, 1, 4, 4>(XMLoadFloat2(&PositionXY), XMLoadFloat(&Scale));
            XMVECTOR Color = XMVectorSet(1, 1, 1, 1);
            XMVECTOR PriginRotationDepth = XMVectorSet(Center.x, Center.y, Rotation, LayerDepth);

            XMVECTOR SourceSize = XMVectorSwizzle<2, 3, 2, 3>(Source);
            XMVECTOR DestinationSize = XMVectorSwizzle<2, 3, 2, 3>(Destination);

            XMVECTOR IsZeroMask = XMVectorEqual(SourceSize, XMVectorZero());
            XMVECTOR NonZeroSourceSize = XMVectorSelect(SourceSize, g_XMEpsilon, IsZeroMask);

            XMVECTOR Origin = XMVectorDivide(PriginRotationDepth, NonZeroSourceSize);

            Origin *= InverseTextureSize;

            DestinationSize *= TextureSize;

            XMVECTOR RotationMatrix1;
            XMVECTOR RotationMatrix2;

            if (Rotation != 0)
            {
                float Sin, Cos;

                XMScalarSinCos(&Sin, &Cos, Rotation);

                XMVECTOR SinV = XMLoadFloat(&Sin);
                XMVECTOR CosV = XMLoadFloat(&Cos);

                RotationMatrix1 = XMVectorMergeXY(CosV, SinV);
                RotationMatrix2 = XMVectorMergeXY(-SinV, CosV);
            }

            else
            {
                RotationMatrix1 = g_XMIdentityR0;
                RotationMatrix2 = g_XMIdentityR1;
            }

            static XMVECTORF32 CornerOffsets[s_SpriteVertices] =
            {
                { 0, 0 },
                { 1, 0 },
                { 0, 1 },
                { 1, 1 },
            };

            int MirrorBits = 0;

            for (int i = 0; i < s_SpriteVertices; ++i)
            {
                using namespace DirectX;

                XMVECTOR CornerOffset = (CornerOffsets[i] - Origin) * DestinationSize;

                XMVECTOR Position1 = XMVectorMultiplyAdd(XMVectorSplatX(CornerOffset), RotationMatrix1, Destination);
                XMVECTOR Position2 = XMVectorMultiplyAdd(XMVectorSplatY(CornerOffset), RotationMatrix2, Position1);

                XMVECTOR Position = XMVectorPermute<0, 1, 7, 6>(Position2, PriginRotationDepth);

                XMStoreFloat4(reinterpret_cast<XMFLOAT4*>(&Vertices[i].Position), Position);

                XMStoreFloat4(&Vertices[i].Color, Color);

                XMVECTOR textureCoordinate = XMVectorMultiplyAdd(CornerOffsets[i ^ MirrorBits], SourceSize, Source);

                XMStoreFloat2(&Vertices[i].Texture, textureCoordinate);
            }

            Vertices += s_SpriteVertices;
        }

        Graphics::s_Context->Unmap(m_VertexBuffer, 0);

        unsigned int StartIndex = (unsigned int)m_VertexBufferPosition * s_SpriteIndices;
        unsigned int IndexCount = (unsigned int)BatchSize * s_SpriteIndices;
        Graphics::s_Context->DrawIndexed(IndexCount, StartIndex, 0);

        m_VertexBufferPosition += BatchSize;

        Sprites += BatchSize;
        Count -= BatchSize;
    }
}
