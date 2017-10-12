#include "pch.h"
#include "Tile.h"

using namespace DirectX;
using namespace Library;
using namespace std;
using namespace Microsoft::WRL;

namespace Pathfinding
{
	Tile::Tile(Game& game, TileType tileType) :
		DrawableGameComponent(game), mBounds(Rectangle::Empty)
	{
		SetType(tileType);
	}

	const Library::Rectangle& Tile::Bounds() const
	{
		return mBounds;
	}

	void Tile::SetBounds(int32_t x, int32_t y)
	{
		
		mX = x;
		mY = y;		
	}



	void Tile::Initialize()
	{
		
	}

	void Tile::Update(const Library::GameTime& gameTime)
	{
		UNREFERENCED_PARAMETER(gameTime);
	}

	void Tile::Draw(const Library::GameTime& gameTime)
	{
		UNREFERENCED_PARAMETER(gameTime);

		XMFLOAT2 position(static_cast<float>(mX), static_cast<float>(mY));

		SpriteManager::DrawTexture2D(mTexture.Get(), position);
	}
	void Tile::SetType(TileType tileType)
	{
		// Load a texture
		ComPtr<ID3D11Resource> textureResource;
		wstring textureName;
		switch (tileType)
		{
			case TileType::End:
			{
				textureName = endFile;
				break;
			}
			
			case TileType::Start:
			{
				textureName = startFile;
				break;
			}
			
			case TileType::Wall:
			{
				textureName = wallFile;
				break;
			}			
			case TileType::Ground:
			{
				textureName = groundFile;
				break;
			}			
			case TileType::Path:
			{
				textureName = pathFile;
				break;
			}
		}
		
		ThrowIfFailed(CreateWICTextureFromFile(mGame->Direct3DDevice(), textureName.c_str(), textureResource.ReleaseAndGetAddressOf(), mTexture.ReleaseAndGetAddressOf()), "CreateWICTextureFromFile() failed.");

		ComPtr<ID3D11Texture2D> texture;
		ThrowIfFailed(textureResource.As(&texture), "Invalid ID3D11Resource returned from CreateWICTextureFromFile. Should be a ID3D11Texture2D.");

		mBounds = TextureHelper::GetTextureBounds(texture.Get());
		mTextureHalfSize.X = mBounds.Width / 2;
		mTextureHalfSize.Y = mBounds.Height / 2;
	}
	std::string Tile::ToString() const
	{
		return "Tile";
	}
}