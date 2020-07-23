#include "ShiningEnginePCH.h"
#include "CSVParser.h"
#include "SimpleException.h"
#include <fstream>
#include <regex>
#include "ResourceManager.h"

void Shining::CSVParser::LoadTileMapData(const std::string& csvFilePath, std::vector<int>& tileIDs) const
{
	std::regex regex{ "^(?:\\w)*(?:\\.csv$)" };
	if (!std::regex_match(csvFilePath, regex))
	{
		throw SimpleException{ "Exception occured: " + csvFilePath + " is not a valid csv file" };
	}

	std::ifstream ifstream{ Shining::ResourceManager::GetInstance().LoadFileForReading(csvFilePath) };
	if (!ifstream.good())
	{
		throw SimpleException{ "Exception occured: error opening file " + csvFilePath};
	}

	while (!ifstream.eof())
	{
		std::string line{};
		std::getline(ifstream, line, ',');
		tileIDs.push_back(std::stoi(line));
	}
}