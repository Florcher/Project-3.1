#include "Input.h"
#include "Output.h"





int main() {

	Input in;
	std::shared_ptr<DataBase> dataPtr = in.input("file.txt");

	Output out;
	out.output(dataPtr, "file1.txt");



	return 0;
}

