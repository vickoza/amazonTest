#include <fstream>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <tuple>
#include <numeric>
#include <string>
#include <vector>

int main(int argc, char* argv[])
{
	std::vector<std::tuple<std::string, std::vector<long double>>> data;
	std::string filename{(argc> 1)?argv[1]:"random_numbers.csv"};
	std::string header;
	std::ifstream file{filename};
	std::getline(file, header);
	std::istringstream headerReader(header);
	std::string colName;
	while (getline(headerReader, colName, ','))
	{
		data.emplace_back(colName, std::vector<long double>{});
	}
	
	auto cur = data.begin();
	for(long double val; file>>val;)
	{
		char temp;
		file>>temp;
		std::get<1>(*cur).emplace_back(val);
		++cur;
		if(cur == data.end())
			cur = data.begin();
	}

	const auto default_precision {std::cout.precision()};
	std::cout << std::setprecision(17);
	for(const auto& tupl :data)
	{
		auto mean = std::reduce((std::get<1>(tupl)).begin(), (std::get<1>(tupl)).end())/ (std::get<1>(tupl)).size();
		auto sd = std::sqrt(std::accumulate((std::get<1>(tupl)).begin(), (std::get<1>(tupl)).end(), 0.0L, [mean](long double a, long double b) { return a + ((b-mean)*(b-mean));})/((std::get<1>(tupl)).size()-1));
		auto [min, max] = std::minmax_element((std::get<1>(tupl)).begin(), (std::get<1>(tupl)).end());
		std::cout << std::get<0>(tupl) << " : [ " << (std::get<1>(tupl)).size() << ", " << mean << ", " << sd << ", " << *min << ", " << *max <<" ]\n";
	}
	std::cout << std::setprecision(default_precision);	
	return 0;
}