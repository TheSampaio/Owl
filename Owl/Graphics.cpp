#include "PCH.h"
#include "Graphics.h"

// Initializes static attributes
ID3D11Device* RGraphics::s_Device = nullptr;
ID3D11DeviceContext* RGraphics::s_Context = nullptr;
D3D11_VIEWPORT RGraphics::s_Viewport {NULL};

// Initilizes attributes
RGraphics::RGraphics()
{
	m_SwapChain = nullptr;
	m_RenderTargetView = nullptr;
	m_BlendState = nullptr;
	m_FeatureLevel = D3D_FEATURE_LEVEL_11_0;

	m_BackgroundColor[0] = 0.0f;
	m_BackgroundColor[1] = 0.0f;
	m_BackgroundColor[2] = 0.0f;
	m_BackgroundColor[3] = 0.0f;

	m_VSync = true;
}

// Destroy pointers
RGraphics::~RGraphics()
{
	if (m_BlendState)		{ ReleaseDevice(m_BlendState); }
	if (m_RenderTargetView) { ReleaseDevice(m_RenderTargetView); }
	if (m_SwapChain)		{ m_SwapChain->SetFullscreenState(false, nullptr); ReleaseDevice(m_SwapChain); }
	if (s_Context)			{ s_Context->ClearState(); ReleaseDevice(s_Context); }
	if (s_Device)			{ ReleaseDevice(s_Device); }
}

// Initializes "Graphics" class
bool RGraphics::Initialize(CWindow*& Window)
{
	unsigned int CreateDeviceFlags = 0;

// if Visual Studio's debug mode is true
#ifdef _DEBUG
	CreateDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	// Create D3D11 device AS hardware
	if FAILED(D3D11CreateDevice(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, CreateDeviceFlags, nullptr, 0, D3D11_SDK_VERSION, &s_Device, &m_FeatureLevel, &s_Context))
	{
		// Create D3D11 device AS software
		if FAILED(D3D11CreateDevice(NULL, D3D_DRIVER_TYPE_WARP, NULL, CreateDeviceFlags, nullptr, 0, D3D11_SDK_VERSION, &s_Device, &m_FeatureLevel, &s_Context))
		{
			return false;
		}

		// Feedbacks user
		MessageBox(Window->GetId(), L"You are using WARP Adapter: Your GPU don't suports D3D11.", L"Owl Eingine", MB_OK | MB_ICONWARNING);
	}

	// Window's color
	COLORREF Color = Window->GetBackgroundColor();
	m_BackgroundColor[0] = GetRValue(Color) / 255.0f;
	m_BackgroundColor[1] = GetGValue(Color) / 255.0f;
	m_BackgroundColor[2] = GetBValue(Color) / 255.0f;
	m_BackgroundColor[3] = 1.0f;

	// Gets device to get adapter
	IDXGIDevice* DXGIDevice = nullptr;
	if FAILED(s_Device->QueryInterface(__uuidof(IDXGIDevice), (void**) &DXGIDevice)) { return false; }

	// Gets adapter to get factory
	IDXGIAdapter* DXGIAdapter = nullptr;
	if FAILED(DXGIDevice->GetParent(__uuidof(IDXGIAdapter), (void**) &DXGIAdapter)) { return false; }

	// Gets factory to create a swap chain
	IDXGIFactory* DXGIFactory = nullptr;
	if FAILED(DXGIAdapter->GetParent(__uuidof(IDXGIFactory), (void**) &DXGIFactory)) { return false; }

	// Swap chain desc
	DXGI_SWAP_CHAIN_DESC SwapChainDesc{ 0 };
	SwapChainDesc.BufferDesc.Width = Window->GetSize()[0];
	SwapChainDesc.BufferDesc.Height = Window->GetSize()[1];
	SwapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	SwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	SwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	SwapChainDesc.SampleDesc.Count = 1;
	SwapChainDesc.SampleDesc.Quality = 0;
	SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	SwapChainDesc.BufferCount = 2;
	SwapChainDesc.OutputWindow = Window->GetId();
	SwapChainDesc.Windowed = (Window->GetDisplayMode() != CWindow::EDisplayMode::FULLSCREEN);
	SwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	SwapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	// Creates a swap chain and associates it with a window
	if FAILED(DXGIFactory->CreateSwapChain(s_Device, &SwapChainDesc, &m_SwapChain)) { return false; }
	if FAILED(DXGIFactory->MakeWindowAssociation(Window->GetId(), DXGI_MWA_NO_ALT_ENTER)) { return false; }

	// Render target view
	ID3D11Texture2D* BackBuffer = nullptr;
	if FAILED(m_SwapChain->GetBuffer(0, __uuidof(BackBuffer), (void**) &BackBuffer)) { return false; }
	if FAILED(s_Device->CreateRenderTargetView(BackBuffer, nullptr, &m_RenderTargetView)) { return false; }

	// Setup render target view
	s_Context->OMSetRenderTargets(1, &m_RenderTargetView, nullptr);

	// Viewport
	s_Viewport.TopLeftX = 0.0f;
	s_Viewport.TopLeftY = 0.0f;
	s_Viewport.Width = static_cast<FLOAT>(Window->GetSize()[0]);
	s_Viewport.Height = static_cast<FLOAT>(Window->GetSize()[1]);
	s_Viewport.MinDepth = 0.0f;
	s_Viewport.MaxDepth = 1.0f;

	// Setup viewports
	s_Context->RSSetViewports(1, &s_Viewport);

	// Blend state
	D3D11_BLEND_DESC BlendStateDesc{ 0 };
	BlendStateDesc.AlphaToCoverageEnable = false;
	BlendStateDesc.IndependentBlendEnable = false;
	BlendStateDesc.RenderTarget[0].BlendEnable = true;
	BlendStateDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	BlendStateDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	BlendStateDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	BlendStateDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	BlendStateDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	BlendStateDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	BlendStateDesc.RenderTarget[0].RenderTargetWriteMask = 0x0F;

	// Create a blender state and setups it
	if FAILED(s_Device->CreateBlendState(&BlendStateDesc, &m_BlendState)) { return false; }
	s_Context->OMSetBlendState(m_BlendState, nullptr, 0xffffffff);

	// Release created pointers
	DXGIDevice->Release();
	DXGIAdapter->Release();
	DXGIFactory->Release();
	BackBuffer->Release();

	return true;
}
