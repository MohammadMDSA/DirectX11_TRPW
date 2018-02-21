#pragma once
#include <wrl.h>
#include <windows.graphics.directx.h>

using namespace Microsoft::WRL;
using namespace Windows::UI::Core;

class CGame
{
public:
	ComPtr<ID3D11Device1>			m_Device;			// The device interface(Virtual representation of the video adaptor)
	ComPtr<ID3D11DeviceContext1>	m_DeviceContext;	// The control panel for the GPU
	ComPtr<IDXGISwapChain1>			m_SwapChain;		// The swap chaan interface

	void Initialize();									// Starting up code
	void Update();										// Code that manipulates the game, such as timer and input
	void Render();										// Draw graphics
};