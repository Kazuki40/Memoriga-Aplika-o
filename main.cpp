//暗記アプリ

#include<iostream>
#include<sstream>
#include<fstream>
#include<ostream>
#include<istream>
#include<ostream>
#include<random>
#include<string>
#include<vector>

#include"split.h"
#include"prepare.h"
#include"calculation.h"

int main() {

	prepare data_set;
	data_set.func();
	std::vector<std::string> temp = data_set.target_data;

	calculation calc;
	calc.priority = data_set.target_data;
	calc.file_number = data_set.data.size();
	calc.start();
	data_set.write_file();


	return 0;

}

//ファイル
//No.,問題,答え.新規，正解数，不正解数，経過日数，連続日数，優先度
//1,問題1,答え1,0-1,0(整数),0(整数),0(整数)，0（整数），0(整数)

//優先度
//新規　1　上から
//四捨五入（（不正解+経過日数-正解）/連続日数）と1の大きい方

