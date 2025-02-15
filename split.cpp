#include "split.h"

//�X�v�����g�֐�
std::vector<std::string> split::split_func(const std::string& str, const char&del) {
	unsigned long long int first = 0;
	unsigned long long int last = str.find_first_of(del);

	std::vector<std::string> result;

	while (first < str.size()) {
		std::string subStr(str, first, last - first);

		result.push_back(subStr);

		first = last + 1;
		last = str.find_first_of(del, first); //�O����l����������

		if (last == std::string::npos) {
			last = str.size();
		}
	}

	return result;
}

