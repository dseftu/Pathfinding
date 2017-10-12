#pragma once

#include "DrawableGameComponent.h"
#include "Rectangle.h"
#include <d3d11_2.h>
#include <DirectXMath.h>
#include <wrl.h>

namespace Pathfinding
{
	enum class TileType
	{
		Start = 1,
		End = 2,
		Ground = 3,
		Path = 4,
		Wall = 5,
	};

	class Tile final : public Library::DrawableGameComponent
	{


	public:
		Tile(Library::Game& game, TileType typeType);

		const Library::Rectangle& Bounds() const;

		void Initialize() override;
		void Update(const Library::GameTime& gameTime) override;
		void Draw(const Library::GameTime& gameTime) override;
		void Tile::SetBounds(int32_t x, int32_t y);
		void SetType(TileType typeType);
		virtual std::string ToString() const;

	private:
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mTexture;
		Library::Point mTextureHalfSize;
		Library::Rectangle mBounds;
		int32_t mX = 0;
		int32_t mY = 0;

		const std::wstring startFile = L"Content\\Start.png";
		const std::wstring endFile = L"Content\\End.png";
		const std::wstring groundFile = L"Content\\Ground.png";
		const std::wstring pathFile = L"Content\\Path.png";
		const std::wstring wallFile = L"Content\\Wall.png";
	};
}
