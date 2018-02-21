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
}

// Performs update to the game states
void CGame::Update()
{

}

// Renders a single frame of 3D graphics
void CGame::Render()
{

}