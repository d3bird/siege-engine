#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <fstream>

class logger
{
  public:
	logger(std::string file_n, bool print = true, bool print_con = true, int total = -1);
	~logger();

	void log(std::string in, bool new_line = false);
	void print_to_file();

	void change_log_size(int i)
	{
		max_log_size = i;
		resize();
	}

	void set_file_name(std::string name)
	{
		file_name = name;
	}
	void set_location(std::string loc)
	{
		file_loc = loc;
	}

  private:
	void log_internal(std::string in, bool new_line = false);
	bool does_file_exist(std::string file);
	void resize();

	bool        print_file;
	bool        print_to_con;
	int         max_log_size;
	int         max_log_number;
	std::string file_name;
	std::string file_loc;

	std::vector<std::string> text_log;
};