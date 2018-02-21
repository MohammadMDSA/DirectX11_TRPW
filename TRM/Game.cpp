#include "pch.h"
#include "Game.h"

// Initializes and prepare Direct3D
void CGame::Initialize()
{
	// Define temp pointer variables to the device and device context
	ComPtr<ID3D11Device> tempDevice;
	ComPtr<ID3D11DeviceContext> tempDeviceContext;

	// Creating the device and device context object
	D3D11CreateDevice(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&tempDevice,
		nullptr,
		&tempDeviceContext
	);

	// Convert the pointers from the DX 11 version to the DX 11.2 version
	tempDevice.As(&m_Device);
	tempDeviceContext.As(&m_DeviceContext);

	// Convert D3D11Device1 interfac3e to an IDXGIDevice1
	ComPtr<IDXGIDevice1> dxgiDevice;
	m_Device.As(&dxgiDevice);

	//Utilize the IDXGIDevice1 interface to get access to the adapter
	ComPtr<IDXGIAdapter> dxgiAdapter;
	dxgiDevice->GetAdapter(&dxgiAdapter);

	// Use the IDXGIAdapter interface to get access to the parent
	ComPtr<IDXGIFactory2> dxgiFactory;
	dxgiAdapter->GetParent(__uuidof(IDXGIFactory2), &dxgiFactory);

	// set up the swap chain description struct
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc = { 0 };

	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;	// How the swap chain should be utilized
	swapChainDesc.BufferCount = 2;									// A front buffer and a back buffer
	swapChainDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;				// A common swap chain effect
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;	// The recomended swap mode
	swapChainDesc.SampleDesc.Count = 1;								// Disables anti-aliasing

	CoreWindow^ window = CoreWindow::GetForCurrentThread(); // Obtain a pointer to the window

	dxgiFactory->CreateSwapChainForCoreWindow(
		m_Device.Get(),							// Address of the device
		reinterpret_cast<IUnknown*>(window),	// Address of the window
		&swapChainDesc,							// Address of the swap chain description
		nullptr,
		&m_SwapChain
	);

	// Get a direct pointer to the back buffer
	ComPtr<ID3D11Texture2D> backBuffer;
	m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), &backBuffer);

	// Create a render target that points to our back buffer
	m_Device->CreateRenderTargetView(backBuffer.Get(), nullptr, &m_RenderTarget);
}

// Performs update to the game states
void CGame::Update()
{

}

// Renders a single frame of 3D graphics
void CGame::Render()
{
	// Switch the back buffer and front buffer
	m_SwapChain->Present(1, 0);
}