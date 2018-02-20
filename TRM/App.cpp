// Precompiled headers
#include "pch.h"
#include "Game.h"

//include common namespaces for simplification
using namespace Windows::ApplicationModel;
using namespace Windows::ApplicationModel::Core;
using namespace Windows::ApplicationModel::Activation;
using namespace Windows::UI::Core;
using namespace Windows::UI::Popups;
using namespace Windows::System;
using namespace Windows::Foundation;
using namespace Windows::Graphics::Display;
using namespace Platform;

// Class definition for the core framework of the app

ref class App sealed : public IFrameworkView
{
public:
	// Functions called by Windows
	virtual void Initialize(CoreApplicationView^ appView)
	{
		// Set WindowClosed to show app is running
		this->m_WindowClosed = false;

		// Subscribe the OnActivation function to handle the Activated 'event'
		appView->Activated += ref new TypedEventHandler< CoreApplicationView ^, IActivatedEventArgs ^>(this, &App::OnActivated);

		CoreApplication::Suspending += ref new EventHandler<SuspendingEventArgs ^>(this, &App::OnSuspending);
		CoreApplication::Resuming += ref new EventHandler<Object ^>(this, &App::OnResuming);
	}

	virtual void SetWindow(CoreWindow^ window)
	{
		window->PointerPressed += ref new TypedEventHandler<CoreWindow ^, PointerEventArgs ^>(this, &App::OnPointerPressed);
		window->KeyDown += ref new TypedEventHandler<CoreWindow ^, KeyEventArgs ^>(this, &App::OnKeyDown);
		window->PointerWheelChanged += ref new TypedEventHandler<CoreWindow^, PointerEventArgs^>(this, &App::OnPointerWheelChanged);
		window->Closed += ref new TypedEventHandler<CoreWindow ^, CoreWindowEventArgs ^>(this, &App::OnClosed);
	}

	virtual void Load(String^ entryPoint) {}

	virtual void Run()
	{
		m_Game.Initialize();

		// Obtain a pointer to the window
		CoreWindow^ window = CoreWindow::GetForCurrentThread();

		// Repeat until window shuts down
		while (!m_WindowClosed) {

			// Run ProcessEvents() to dispatch events
			window->Dispatcher->ProcessEvents(CoreProcessEventsOption::ProcessAllIfPresent);

			// Calling update and render repeatedly
			m_Game.Update();
			m_Game.Render();
		}

	}

	virtual void Uninitialize() {}

	// An event that is called when the application windows is ready to be activated
	void OnActivated(CoreApplicationView^ sender, IActivatedEventArgs^ args)
	{
		// Obtain a pointer to the window
		CoreWindow^ window = CoreWindow::GetForCurrentThread();
		// Activate the window
		window->Activate();
	}

	// Input event handlers
	void OnPointerPressed(CoreWindow^ window, PointerEventArgs^ args)
	{
		auto pos = args->CurrentPoint->Position;
		MessageDialog dialog("You clicked on " + pos.X + " " + pos.Y, "Notice!!");

		dialog.ShowAsync();
	}

	void OnPointerWheelChanged(CoreWindow^ window, PointerEventArgs^ args)
	{
		int wheel = args->CurrentPoint->Properties->MouseWheelDelta;
		MessageDialog^ dialog = ref new MessageDialog("", "Mouse wheel event");
		dialog->Content = wheel.ToString();

		dialog->ShowAsync();
	}

	void OnKeyDown(CoreWindow^ window, KeyEventArgs^ args)
	{
		MessageDialog^ dialog = ref new MessageDialog("", "");

		bool show = true;
		switch (args->VirtualKey)
		{
		case VirtualKey::W:
			dialog->Content = "Move forward";
			dialog->Title = "W pressed";
			break;
		case VirtualKey::A:
			dialog->Content = "Move left";
			dialog->Title = "A pressed";
			break;
		case VirtualKey::S:
			dialog->Content = "Move backwrad";
			dialog->Title = "S pressed";
			break;
		case VirtualKey::D:
			dialog->Content = "Move right";
			dialog->Title = "D pressed";
			break;
		case VirtualKey::Escape:
			CoreApplication::Exit();
		default:
			show = false;
			break;
		}
		if (show)
			dialog->ShowAsync();
	}

	void OnClosed(CoreWindow^ window, CoreWindowEventArgs^ args)
	{
		// Ends the main app loop
		this->m_WindowClosed = true;
	}

	void OnSuspending(Object^ sender, SuspendingEventArgs^ args)
	{

	}

	void OnResuming(Object^ sender, Object^ args)
	{

	}

private:
	bool m_WindowClosed; // Turns true when it's time to shut down the window
	CGame m_Game;
};

// The class definition that creates an instance of our core class
ref class AppSource sealed : IFrameworkViewSource
{
public:
	virtual IFrameworkView^ CreateView()
	{
		return ref new App();
	}
};

[MTAThreadAttribute] // Define main() as a multi-threaded-appartment function

// The starting point of the app
int main(Array<String^>^ args)
{
	CoreApplication::Run(ref new AppSource());

	return 0;
}