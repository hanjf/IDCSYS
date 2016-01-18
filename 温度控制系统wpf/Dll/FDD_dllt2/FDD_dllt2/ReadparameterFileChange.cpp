#include <iostream>
#include <fstream>
using namespace std;
int ReadparameterFileChange(char* filename)//转换文件，文件用于读取历史数据用于预测
{
	int row = 0;
	int k = 1;
	char preread;

	ifstream fin;
	fin.open(filename);
	if (fin.fail())
	{
		cout << "Input file " << filename << " opening failed!" << endl;
		exit(1);
	}

	ofstream fout;
	fout.open("Readparameter.txt");
	if (fout.fail())
	{
		cout << "Output file opeing failed!" << endl;
		exit(1);
	}

	while (fin.get(preread))
	{
		if (k == 1 && preread == ' ')
		{}
		else if (k == 1 && preread == ',')
		{
			fout << ',';
			k = 0;
		}
		else if (k != 1 && preread == ',')
		{
			fout << ' ';
		}
		else if (preread == '\n')
		{
			fout.put(preread);
			row++;
			k = 1;
		}
		else 
			fout.put(preread);
	}

	fin.close();
	fout.close();

	return row;
}