#include "logger.h"

logger::logger(std::string file_n, bool print , bool print_con, int total) {
	max_log_size = total;
	print_file = print;
	print_to_con = print_con;
	file_name = file_n;
	if (file_name == "") {
		file_name = "no_name";
	}
	file_loc = "";
	max_log_number = -1;//will not print new log files if there are more than this
}

logger::~logger() {

	if (print_file) {
		print_to_file();
	}
}

void logger::log(std::string in, bool new_line) {

	if (print_to_con) {
		std::cout << in;
		if (new_line) {
			std::cout << std::endl;
		}
	}

	if (new_line) {
		text_log.push_back(in);
	}
	else {
		if (text_log.empty()) {
			text_log.push_back(in);
		}
		else {
			std::string temp = text_log[text_log.size() - 1];
			temp += in;
			text_log[text_log.size() - 1] = temp;
		}
	}
	while (max_log_size != -1) {
		if (text_log.size() > max_log_size) {
			text_log.erase(text_log.begin());
		}
	}
}

void logger::log_internal(std::string in, bool new_line) {
	std::string temp = "LOGGER:: "+in;
	log(in, new_line);
}


void  logger::print_to_file() {
	std::string log_file = file_name + ".log";
	int         count    = 0;
	while (does_file_exist(log_file))
	{
		log_internal("the file to print already exist", true);
		count++;
		log_file = file_name + std::to_string(count) + ".log";
		if (max_log_number != -1 && count >= max_log_number)
		{
			log_internal("there are too many log files(" + std::to_string(count)+") delete extra logs", true);
			return;
		}
	}
	std::ofstream output(file_loc + log_file);

	if (output.is_open()) {
		for (int i = 0; i < text_log.size(); i++) {
			output << text_log[i] << std::endl;
		}

		output.close();
	}
	else {
		log_internal("could not open file"), true;
	}
}

bool logger::does_file_exist(std::string file)
{
	std::ifstream ifile;
	ifile.open(file_loc + file);
	if (ifile)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void logger::resize() {
	while (max_log_size != -1) {
		if (text_log.size() > max_log_size) {
			text_log.erase(text_log.begin());
		}
	}
}