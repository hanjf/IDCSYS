#include <iostream>
#include <fstream>
using namespace std;
int ReaddataFileChange(char* filename)//�ļ�ת����ת����ԭʼ�ļ�Ϊright���ɳ�������
{
	int row = 0;
	char preread;

	ifstream fin;
	fin.open(filename);
	if (fin.fail())
	{
		cout << "Input file " << filename << " opening failed!" << endl;
		exit(1);
	}

	ofstream fout;
	fout.open("Readdata.txt");
	if (fout.fail())
	{
		cout << "Output file opening failed!" << endl;
		exit(1);
	}

	while (fin.get(preread))
	{
		if (preread == ',')
		{
			fout << ' ';
		}
		else if (preread == '\n')
		{
			fout.put(preread);
			row++;
		}
		else 
			fout.put(preread);
	}
	
	fin.close();
	fout.close();

	return row;
}