#include <fstream>
#include <iostream>

using namespace std;

void WriteFile(double value[21],char* filename)
{
	int i;

	ofstream fout;
	fout.open(filename,ios::app);
	if (fout.fail())
	{
		cout << "Output file opening failed!" << endl;
		exit(1);
	}

	for (i=0;i<21;i++)
	{
		fout << value[i] << ',';
		if (i == 20)
			fout << '\n';
	}

	fout.close();
}