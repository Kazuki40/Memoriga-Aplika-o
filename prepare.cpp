#include "prepare.h"
#include "split.h"


prepare::prepare() {
	data_length = 0;
	prictice_number = 0;


}

prepare::~prepare() {

	}

void prepare::func() {
	prepare::import_number();
	prepare::import_file();
	prepare::choose_target_data();
	prepare::temp_file();
}


void prepare::import_number() {
	auto func = []()-> unsigned long {
		std::string str;
		std::cout << "How many do you study?\n ";
		std::cin >> str;
		unsigned long ans = 0;
		try
		{
			ans = std::stoul(str);
		}
		catch (...)
		{
			std::cerr << "error: waring number\n";
			exit(1);
		}

		return ans;

		};


	this->prictice_number = func();

	return;
}

void prepare::import_file() {

	std::cout << "What do you study in the csv file?\n ";
	std::cin >> file_name;

	std::ifstream ifs(file_name, std::ios::in);

	if (!ifs)
	{
		std::cerr << "error: file open\n" << std::endl;
		exit(2);
	}

	std::string str;
	while (getline(ifs, str)) {
		if (this->data_length != 0) {
			this->data.push_back(str);
		}
		this->data_length++;

	}
	this->data_length--;
	ifs.close();

	if (this->prictice_number > this->data.size()) {
		this->prictice_number = this->data.size();
	}

	return;
}

void prepare::choose_target_data() {
	this->target_data.resize(this->prictice_number);

	//優先度
	//新規　1　上から
	//四捨五入（（不正解+経過日数-正解）/連続日数）と1の大きい方

	unsigned long new_data = 0;
	unsigned long loop_num;
	


	for (loop_num = 0; loop_num < this->data.size(); loop_num++) {


		std::vector<std::string> temp = split.split_func(this->data[loop_num], ',');

		//No.,問題,答え,新規，pass,正解数，不正解数，経過日数，連続日数，優先度
		if (std::stoi(temp[3]) == 1) {

			//対象のデータを追加
			this->target_data[new_data] = this->data[loop_num];
			new_data++;

			//対象のデータを削除
			this->data.erase(this->data.begin() + loop_num);
			loop_num--;
		}
		if (new_data == this->prictice_number) {
			break;
		}
	}

	//優先度
	if (new_data < this->prictice_number) {
		std::vector<unsigned long int> priority;
		unsigned long long int sum_temp = 0;

		for (loop_num = 0; loop_num < this->data.size(); loop_num++) {
			//No.,問題,答え,新規,pass,正解数,不正解数,経過日数,連続日数,優先度
			std::vector<std::string> temp_2 = split.split_func(this->data[loop_num], ',');
			sum_temp += std::stoul(temp_2[9]);
			priority.push_back(std::stoul(temp_2[9]));
		}

		//乱数
		std::random_device seed_gen;
		std::mt19937_64 engine(seed_gen());


		do {
			std::uniform_int_distribution<> dist(0, sum_temp);
			unsigned long random = dist(engine);

			unsigned long temp = 0;

			for (loop_num = 0; loop_num < priority.size(); loop_num++) {
				temp += priority[loop_num];
				if (random <= temp) {
					break;
				}
			}

			//データの追加
			this->target_data[new_data] = this->data[loop_num];

			//データの整理
			sum_temp -= priority[loop_num];
			this->data.erase(this->data.begin() + loop_num);
			priority.erase(priority.begin() + loop_num);
			new_data++;

		} while (new_data < this->prictice_number);



	}

	return;
}


void prepare::temp_file() {
	std::ofstream ofs("temp.csv", std::ios::out);
	if (!ofs)
	{
		std::cerr << "error: file open\n" << std::endl;
		exit(2);
	}

	ofs << "No.,問題,答え,新規,pass,正解数,不正解数,経過日数,連続日数,優先度" << std::endl;

	for (unsigned long loop_num = 0; loop_num < this->data.size(); loop_num++) {
		std::vector<std::string> temp_out = split.split_func(this->data[loop_num], ',');
	
		ofs <<(loop_num+1) << "," << temp_out[1] << "," << temp_out[2] << "," << temp_out[3] << "," << temp_out[4] << "," << temp_out[5] << "," << temp_out[6] << "," << std::stoul(temp_out[7]) +1<< "," << 0 << "," << std::stoul(temp_out[9])+1 << std::endl;
	
	}
	ofs.close();
	return;
}

void prepare::write_file() {
	std::filesystem::remove(this->file_name);
	std::filesystem::rename("temp.csv", this->file_name);
	return;
}