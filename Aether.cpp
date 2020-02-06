#include "Aether.h"
#include "plane/Plane.h"
#include <stdlib.h>
#include <fstream>
#include <string>
#include <sstream>

// https://stackoverflow.com/questions/1120140/how-can-i-read-and-parse-csv-files-in-c
enum class CSVState
{
	UnquotedField,
	QuotedField,
	QuotedQuote
};

std::vector<std::string> readCSVRow(const std::string& row)
{
	CSVState state = CSVState::UnquotedField;
	std::vector<std::string> fields{ "" };
	size_t i = 0; // index of the current field
	for (char c : row)
	{
		switch (state)
		{
		case CSVState::UnquotedField:
			switch (c)
			{
			case ',': // end of field
				fields.push_back(""); i++;
				break;
			case '"': state = CSVState::QuotedField;
				break;
			default:  fields[i].push_back(c);
				break;
			}
			break;
		case CSVState::QuotedField:
			switch (c)
			{
			case '"': state = CSVState::QuotedQuote;
				break;
			default:  fields[i].push_back(c);
				break;
			}
			break;
		case CSVState::QuotedQuote:
			switch (c)
			{
			case ',': // , after closing quote
				fields.push_back(""); i++;
				state = CSVState::UnquotedField;
				break;
			case '"': // "" -> "
				fields[i].push_back('"');
				state = CSVState::QuotedField;
				break;
			default:  // end of quote
				state = CSVState::UnquotedField;
				break;
			}
			break;
		}
	}
	return fields;
}

/// Read CSV file, Excel dialect. Accept "quoted fields ""with quotes"""
std::vector<std::vector<std::string>> readCSV(std::istream &in)
{
	std::vector<std::vector<std::string>> table;
	std::string row;
	while (!in.eof())
	{
		std::getline(in, row);
		if (in.bad() || in.fail())
		{
			break;
		}
		auto fields = readCSVRow(row);
		table.push_back(fields);
	}
	return table;
}
Aether::Aether()
{
	std::ifstream file("stops.txt");
	std::vector<std::vector<std::string>> data = readCSV(file);
	file.close();

	for (auto& line : data)
	{
		try
		{
			this->_points.push_back(std::make_pair(std::make_pair(std::stod(line[4]), std::stod(line[5])), line[2]));
		}
		catch (const std::exception&)
		{ }
	}

	for (size_t i = 0; i < 100 && i < this->_points.size(); i++)
	{
		std::cout << this->_points[i].first.first << " " << this->_points[i].first.second << " " << this->_points[i].second  << std::endl;
	}
}

Aether::~Aether()
{
	//for (size_t i = 0; i < world.size(); i++)
	//{
	//	delete world[i];
	//	world[i] = nullptr;
	//}
}

bool Aether::OnUserCreate()
{
	// olc::PixelGameEngine::SetPixelMode(olc::Pixel::ALPHA);

	Plane::OnUserCreate();
	std::cout << __FUNCTION__ << std::endl;


	return true;
}

bool Aether::OnUserUpdate(float fElapsedTime)
{
	Plane::OnUserUpdate(fElapsedTime);//Clear(olc::BLACK);

	/**/
	double minx = minX();
	double miny = minY();
	double maxx = maxX();
	double maxy = maxY();

	int s = 90;
	for (int x = -s; x < s; x++)
	{
		for (int y = -s; y < s; y++)
		{
			Draw(x, y, olc::YELLOW);
		}
	}

	int num = 0;
	for(auto& p : this->_points)
	{
		if(num++ > 100) break;
		Draw(p.first.first, p.first.second, olc::WHITE);
		DrawString(p.first.first, p.first.second, p.second, olc::GREEN);
	}

	//for (size_t i = 0; i < 1000; i++)
	//{
	//	double x1 = minx + (rand()%1000)/1000.0 * (maxx-minx);
	//	double x2 = minx + (rand()%1000)/1000.0 * (maxx-minx);
	//	double y1 = miny + (rand()%1000)/1000.0 * (maxy-miny);
	//	double y2 = miny + (rand()%1000)/1000.0 * (maxy-miny);
	//	DrawLine(x1, y1, x2, y2);
	//}

	return true;
}
