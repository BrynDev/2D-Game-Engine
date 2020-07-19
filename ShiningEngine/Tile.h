#pragma once
namespace Shining
{
	struct TileInfo
	{
		int texCoord;
		int id;
	};


	class Tile final
	{
	public:
		Tile(const TileInfo& info);
		~Tile() = default;
	private:
		TileInfo m_Info;
	};
}