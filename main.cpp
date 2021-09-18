#include <iostream>
#include <fstream>
#include <vector>

int main(int argc, const char** argv) {
	if (argc != 2)
		exit(-1);
	std::ifstream ifile(argv[1], std::ios::binary);
	if (!ifile.is_open())
		exit(-1);

	std::vector<char> data;
	char* c = new char;
	{
		int i = 0;
		while (ifile.read(c, 1)) {
			data.push_back(*c);
			i++;
			if (!(i & 0xffffff))
				std::cout << i / 0x100000 << std::endl;
		}
		std::cout << i << std::endl;
	}
	ifile.close();
	std::cout << "Copied to memory\n";
	std::cin.get();

	std::ofstream ofile(argv[1], std::ios::trunc | std::ios::binary);
	ofile.write(data.data(), data.size());
	ofile.close();
}