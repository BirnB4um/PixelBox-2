#include <Windows.h>
#include <vector>
#include <string>
#include <fstream>

class IO_DATA
{
public:
	static std::string choose_open_file(int nr_file_name = 0);
	static std::string choose_save_file(int nr_file_name = 0);
	static bool save_to_file(std::string file_name, const char *output_data, const size_t data_size, bool append_data);
	static bool read_from_file(std::string file_name, std::vector<char>& input_data);
};

