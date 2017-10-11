#include "pch.h"
#include "PathfindingGame.h"

using namespace std;
using namespace DirectX;
using namespace Library;
using namespace Microsoft::WRL;

namespace Pathfinding
{
	const XMVECTORF32 PathfindingGame::BackgroundColor = Colors::SteelBlue;
	const int MAXSCORE = 3;

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

		mAudio = make_shared<AudioEngineComponent>(*this);
		mComponents.push_back(mAudio);
		mServices.AddService(AudioEngineComponent::TypeIdClass(), mAudio.get());
				
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
		Game::Update(gameTime);
	}

	void PathfindingGame::Draw(const GameTime &gameTime)
	{
		UNREFERENCED_PARAMETER(gameTime);
		mDirect3DDeviceContext->ClearRenderTargetView(mRenderTargetView.Get(), reinterpret_cast<const float*>(&BackgroundColor));
		mDirect3DDeviceContext->ClearDepthStencilView(mDepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

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