#pragma once
#include<iostream>
#include<sstream>
#include<fstream>
#include<ostream>
#include<istream>
#include<string>
#include<vector>
#include<random>
#include<algorithm>
#include"split.h"

class calculation
{
public:
	calculation();
	~calculation();
	void participant_data();
	void calculation_func();
	std::vector<std::string> priority;
	std::vector<std::vector<std::string>> programme_answer;
	std::vector<std::vector<unsigned long long int>> priority_num;
	std::vector<std::vector<std::string>> finish_answer;
	std::vector<std::vector<unsigned long long int>>finish_num;
	std::vector<std::string> finish_data;
	split split;
	void write_file();
	unsigned long long int file_number;
	void start();
};

