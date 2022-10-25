#ifndef OWL_GRAPHICS_H
#define OWL_GRAPHICS_H

#include "Window.h"

// Simplifies the release of pointers
template <typename TReturnType>
void ReleaseDevice(TReturnType* Device)
{
	Device->Release();
	Device = nullptr;
}

class RGraphics
{
public:
	RGraphics();
	~RGraphics();

	// Static attributes
	static ID3D11Device* s_Device;
	static ID3D11DeviceContext* s_Context;
	static D3D11_VIEWPORT s_Viewport;

	// Main methods
	bool Initialize(CWindow*& Window);

	inline void SwapBuffers() { m_SwapChain->Present(m_VSync, NULL); s_Context->OMSetRenderTargets(1, &m_RenderTargetView, nullptr); }
	inline void ClearBackBuffer() { s_Context->ClearRenderTargetView(m_RenderTargetView, m_BackgroundColor); }
	inline void SetVerticalSynchronization(bool State) { m_VSync = State; }

	// Get methods
	inline ID3D11Device*& GetGraphicDevice() const { return s_Device; }
	inline ID3D11DeviceContext*& GetGraphicContext() const { return s_Context; }

private:
	IDXGISwapChain* m_SwapChain;
	ID3D11RenderTargetView* m_RenderTargetView;
	ID3D11BlendState* m_BlendState;
	D3D_FEATURE_LEVEL m_FeatureLevel;
	float m_BackgroundColor[4];
	bool m_VSync;
};

#endif // !OWL_GRAPHICS_H
