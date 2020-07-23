#pragma once
#include <string>

namespace Shining
{
	class CSVParser
	{
	public:
		CSVParser() = default;
		~CSVParser() = default;

		void LoadTileMapData(const std::string& csvFilePath, std::vector<int>& tileIDs) const;
	private:
	};
}


