//�ËL�A�v��

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

//�t�@�C��
//No.,���,����.�V�K�C���𐔁C�s���𐔁C�o�ߓ����C�A�������C�D��x
//1,���1,����1,0-1,0(����),0(����),0(����)�C0�i�����j�C0(����)

//�D��x
//�V�K�@1�@�ォ��
//�l�̌ܓ��i�i�s����+�o�ߓ���-�����j/�A�������j��1�̑傫����

