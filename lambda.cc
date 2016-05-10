#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

int main(int argc, char const *argv[])
{
	std::vector<std::string> words{"1", "12", "123"};
	for (decltype(words.size()) index{0}; 
		 index != words.size(); ++index) {
		std::cout << words[index] << std::endl;
	}
	auto wc{std::find_if(words.begin(), words.end(),
		         [=] (const std::string& s) {return s.size() >= 2;})};
	std::cout << *wc << std::endl;
	return 0;
}