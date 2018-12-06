#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#include "hash_table.h"
#include "hash_table.cpp"
#include "suggestion.h"

#define suggest_count 5

int hamming(std::string, std::string);
bool compare(suggestion const &, suggestion const &);

//struct word {
//	std::string word;
//	int ham;
//};

void main() {
	hash_table<std::string, std::string> word_list(15000);
	std::vector<std::string> ref_list;
	std::ifstream word_in;
	word_in.open("word list.txt");
	//taking in word list
	if (word_in.is_open()) {
		while (!word_in.eof()) {
			std::string temp_str;
			word_in >> temp_str;
			word_list.insert(temp_str);
			ref_list.push_back(temp_str);
		}
	}
	else {
		std::cout << "error: unable to open word list file" << std::endl;
	}
	word_in.close();
	std::ifstream new_word_in;
	new_word_in.open("text.txt");
	//opening text file to be corrected or confirmed
	if (new_word_in.is_open()) {
		//loop to analyse all words in file in case there is more than one. must be seperated by /n
		while (!new_word_in.eof())
		{
			std::string new_temp_str;
			new_word_in >> new_temp_str;
			std::cout << new_temp_str << std::endl;
			//check for word
			if (word_list.exists(new_temp_str)) {
				std::cout << "word is already correct" << std::endl;
			}
			else {
				//accumulating suggestions
				suggestion suggest[suggest_count];
				//reseting array
				for (int i = 0; i < suggest_count; i++) {
					suggest[i].differ = new_temp_str.length();
					suggest[i].word = "~";
				}
				//comparing each word on list and gfetting hamming distance
				for (int i = 0; i < ref_list.size(); i++) {
					if (hamming(new_temp_str, ref_list[i]) < suggest[suggest_count-1].differ) {
						suggest[suggest_count-1].word = ref_list[i];
						suggest[suggest_count-1].differ = hamming(new_temp_str, ref_list[i]);
						std::sort(suggest, suggest + suggest_count, compare);
					}
				}
				std::cout << "corrections: " << std::endl;
				for (int i = 0; i < suggest_count; i++) {
					std::cout << suggest[i].word << std::endl;
				}
			}
		}
	}
	else {
		std::cout << "error: unable to open text to be corrected" << std::endl;
	}
	std::cout << std::endl;
	system("pause");
}

//function to properly sort suggestions array
bool compare(suggestion const & a, suggestion const & b){
	return a.differ < b.differ;
}


//hamming array
int hamming(std::string str_in_1, std::string str_in_2) {
	int diff;
	if (str_in_1.length() > str_in_2.length()) {
		diff = str_in_1.length() - str_in_2.length();
	}
	else {
		diff = str_in_2.length() - str_in_1.length();
	}
	for (int i = 0; i < str_in_1.length() && i < str_in_2.length(); i++) {
		if (str_in_1[i] != str_in_2[i]) {
			diff++;
		}
	}
	return diff;
}