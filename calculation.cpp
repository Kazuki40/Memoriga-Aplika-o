#include "calculation.h"

calculation::calculation()
{

}

calculation::~calculation()
{
}

void calculation::start()
{
	participant_data();
	calculation_func();
	write_file();
}

void calculation::participant_data()
{
	this->programme_answer.resize(priority.size());
	this->priority_num.resize(priority.size());

	for (unsigned long int data_length = 0; data_length < priority.size(); data_length++) {
		std::vector<std::string> temp = split.split_func(priority[data_length], ',');

		//No.,問題,答え,新規，pass.,正解数，不正解数，経過日数，連続日数，優先度
		this->programme_answer[data_length].push_back(temp[1]);
		this->programme_answer[data_length].push_back(temp[2]);
		this->programme_answer[data_length].push_back(temp[4]);

		this->priority_num[data_length].push_back(std::stoul(temp[5]));
		this->priority_num[data_length].push_back(std::stoul(temp[6]));
		this->priority_num[data_length].push_back(std::stoul(temp[8]));

	}

}

void calculation::calculation_func()
{

	//答え
	std::random_device seed_gen;
	std::mt19937_64 engine(seed_gen());

	do {

		std::system("pause");
		std::system("cls");
		std::uniform_int_distribution<> dist(0, this->programme_answer.size() - 1);
		unsigned long random = dist(engine);

		std::cout << " probramme:\n" << std::endl;

		if (std::stoi(this->programme_answer[random][2]) == 0) {
				std::cout <<"  " << this->programme_answer[random][0] << std::endl;
		}
		else {
			std::system(this->programme_answer[random][0].c_str());
		}



		std::system("pause");

		std::cout << this->programme_answer[random][1] << std::endl;

		std::cout << "correct:1\nincorrect:2" << std::endl;

		int answer;
		std::cin >> answer;

		if (answer == 1) {

			this->priority_num[random][0]++;
			this->finish_answer.push_back(this->programme_answer[random]);

			this->finish_num.push_back(this->priority_num[random]);
			this->programme_answer.erase(this->programme_answer.begin() + random);
			this->priority_num.erase(this->priority_num.begin() + random);
		}
		else {

			this->priority_num[random][1]++;

		}


	} while (this->finish_answer.size() < priority.size());


	return;
}

void calculation::write_file()
{
	std::ofstream ofs("temp.csv", std::ios::app);
	if (!ofs)
	{
		std::cerr << "error: file open\n" << std::endl;
		exit(3);
	}

	for (unsigned long long int temp = 0; temp < this->finish_answer.size(); temp++) {

		//No.,問題,答え,pass,,新規，正解数，不正解数，経過日数，連続日数，優先度
		ofs << (file_number + temp + 1)<< "," << this->finish_answer[temp][0] << "," << this->finish_answer[temp][1] <<  "," << 0 << "," << this->finish_answer[temp][2]<< "," << this->finish_num[temp][0] << "," << this->finish_num[temp][1] << "," << 0 << "," << (this->finish_num[temp][2]+1) << ",";

		//優先度の計算
		unsigned long long int priority_number = 0;
		priority_number = std::max((long long int)(this->finish_num[temp][1] - (long long int)this->finish_num[temp][0]) / ((long long int)this->finish_num[temp][2]+1), 1LL);
		ofs << priority_number << std::endl;

	}



	return;

}