#include "pch.h"
#include "PathfindingGame.h"

#include "Rectangle.h"

using namespace std;
using namespace DirectX;
using namespace Library;
using namespace Microsoft::WRL;

IMGUI_API LRESULT ImGui_ImplDX11_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace Pathfinding
{
	XMVECTORF32 PathfindingGame::BackgroundColor = Colors::Black;
	PathfindingGame::PathfindingGame(function<void*()> getWindowCallback, function<void(SIZE&)> getRenderTargetSizeCallback) :
		Game(getWindowCallback, getRenderTargetSizeCallback)
	{
	}

	void PathfindingGame::Initialize()
	{
		SpriteManager::Initialize(*this);				
		BlendStates::Initialize(mDirect3DDevice.Get());

		mKeyboard = make_shared<KeyboardComponent>(*this);
		mComponents.push_back(mKeyboard);
		mServices.AddService(KeyboardComponent::TypeIdClass(), mKeyboard.get());

		mImGui = make_shared<ImGuiComponent>(*this);
		mComponents.push_back(mImGui);
		mServices.AddService(ImGuiComponent::TypeIdClass(), mImGui.get());
		auto imGuiWndProcHandler = make_shared<UtilityWin32::WndProcHandler>(ImGui_ImplDX11_WndProcHandler);
		UtilityWin32::AddWndProcHandler(imGuiWndProcHandler);

		// 1. Show a simple window
		// Tip: if we don't call ImGui::Begin()/ImGui::End() the widgets appears in a window automatically called "Debug"
		auto sampleImGuiRenderBlock1 = make_shared<ImGuiComponent::RenderBlock>([this]()
		{
			ImGui::Begin("Input Controls");
			static float f = 0.0f;
			ImGui::Text("Current grid: ");
			ImGui::Text("Current start: ");
			ImGui::Text("Current end: ");
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::End();
		});
		mImGui->AddRenderBlock(sampleImGuiRenderBlock1);
				
		srand((unsigned int)time(NULL));	

		Game::Initialize();
	}

	void PathfindingGame::Shutdown()
	{
		BlendStates::Shutdown();
		SpriteManager::Shutdown();
	}

	void PathfindingGame::Update(const GameTime &gameTime)
	{
		if (mKeyboard->WasKeyPressedThisFrame(Keys::Escape))
		{
			Exit();
		}
		Game::Update(gameTime);
	}

	void PathfindingGame::Draw(const GameTime &gameTime)
	{
		mDirect3DDeviceContext->ClearRenderTargetView(mRenderTargetView.Get(), reinterpret_cast<const float*>(&BackgroundColor));
		mDirect3DDeviceContext->ClearDepthStencilView(mDepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

		Game::Draw(gameTime);

		HRESULT hr = mSwapChain->Present(1, 0);

		// If the device was removed either by a disconnection or a driver upgrade, we must recreate all device resources.
		if (hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET)
		{
			HandleDeviceLost();
		}
		else
		{
			ThrowIfFailed(hr, "IDXGISwapChain::Present() failed.");
		}
	}

	void PathfindingGame::Exit()
	{
		PostQuitMessage(0);
	}

}