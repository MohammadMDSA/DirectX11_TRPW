#pragma once
#include <wrl.h>
#include <windows.graphics.directx.h>

using namespace Microsoft::WRL;
using namespace Windows::UI::Core;

class CGame
{
public:
	void Initialize();		// Starting up code
	void Update();			// Code that manipulates the game, such as timer and input
	void Render();			// Draw graphics
};