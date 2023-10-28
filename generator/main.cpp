#include <fstream>
#include <cmath>


/*
	Tool for generating lookup tables
*/

// write a table
void writeTable(std::ofstream &f, int *table, int size) {
	f << "{" << std::endl;
	for (int j = 0; j < size / 16; ++j) {
		f << "\t";
		for (int i = 0; i < 16; ++i) {
			f << table[j * 16 + i] << ", ";
		}
		f << std::endl;
	}
	f << "};" << std::endl;
}

// generate permutation table
void generatePermute(const std::string &path) {
	srand(1337);

	// initialize perutation table
	int permute[256];
	for (int i = 0; i < 256; ++i) {
		permute[i] = i;
	}

	// shuffle permutation table
	for (int i = 0; i < 10000; ++i) {
		int x = rand() & 0xff;
		int y = rand() & 0xff;
		std::swap(permute[x], permute[y]);
	}

	// write permutation table and function
	std::ofstream f(path);
	f << "// generated by generatePermute()" << std::endl;
	f << "const uint8_t permute8[256] = ";
	writeTable(f, permute, 256);
	f.close();
}

int main(int argc, const char **argv) {

	generatePermute("coco/permute8.hpp");

	return 0;
}