#pragma once

#include "Window.h"

// Simplifies the release of pointers
template <class Type>
void ReleaseComponent(Type* Component)
{
	if (Component)
	{
		Component->Release();
		Component = nullptr;
	}
}

class Graphics
{
public:
	Graphics();
	~Graphics();

	// Static attributes
	static ID3D11Device* s_Device;
	static ID3D11DeviceContext* s_Context;
	static D3D11_VIEWPORT s_Viewport;

	// Main methods
	bool Initialize(Window*& Window);

	inline void SwapBuffers()                          { m_SwapChain->Present(m_VSync, NULL); s_Context->OMSetRenderTargets(1, &m_RenderTargetView, nullptr); }
	inline void ClearBackBuffer()                      { s_Context->ClearRenderTargetView(m_RenderTargetView, m_BackgroundColor); }
	inline void SetVerticalSynchronization(bool State) { m_VSync = State; }

	// Get methods
	inline ID3D11Device*& GetGraphicDevice()         const { return s_Device; }
	inline ID3D11DeviceContext*& GetGraphicContext() const { return s_Context; }
	inline D3D11_VIEWPORT& GetViewport()             const { return s_Viewport; }

private:
	IDXGISwapChain* m_SwapChain;
	ID3D11RenderTargetView* m_RenderTargetView;
	ID3D11BlendState* m_BlendState;
	D3D_FEATURE_LEVEL m_FeatureLevel;
	float m_BackgroundColor[4];
	bool m_VSync;
};
