#pragma once
#include<iostream>
#include<sstream>
#include<fstream>
#include<ostream>
#include<istream>
#include<ostream>
#include<random>
#include<string>
#include<vector>
#include<filesystem>

#include"split.h"

class prepare
{
public:
	prepare();
	~prepare();
	void func();
	void write_file();
	unsigned long data_length;
	std::string file_name;
	std::vector<std::string> data;
	std::vector<std::string> target_data;

	class split split;

private:
	unsigned long prictice_number;
	void import_number();
	void import_file();	
	void choose_target_data();

	void temp_file();

};

