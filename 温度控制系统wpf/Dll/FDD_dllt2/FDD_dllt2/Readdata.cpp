#include <iostream>
#include <fstream>
using namespace std;
void Readdata(double value[21][120],int row)//读取正常数据，原始文件为right，由程序生成
{
	double prenum;//预读数据
	int i;//循环量
	int rrow = 1;

	ifstream fr;
	fr.open("Readdata.txt");
	if (fr.fail())
	{
		cout << "Input Readdata.txt opening failed!" << endl;
		exit(1);
	}

//读取第一排标题
//	do
//	{
//		fr.get(preread);
//	}while (preread != '\n');

//读取第type列需要的数据（三十分钟之前读取最开始的数据，三十分钟之后读取三十分钟之前的数据）
	if (row < 1921)
	{
		for (i = 0;i < 120;i++)
		{
			fr >> prenum;
			value[0][i] = prenum;
			fr >> prenum;
			value[1][i] = prenum;
			fr >> prenum;
			value[2][i] = prenum;
			fr >> prenum;
			value[3][i] = prenum;
			fr >> prenum;
			value[4][i] = prenum;
			fr >> prenum;
			value[5][i] = prenum;
			fr >> prenum;
			value[6][i] = prenum;
			fr >> prenum;
			value[7][i] = prenum;
			fr >> prenum;
			value[8][i] = prenum;
			fr >> prenum;
			value[9][i] = prenum;
			fr >> prenum;
			value[10][i] = prenum;
			fr >> prenum;
			value[11][i] = prenum;
			fr >> prenum;
			value[12][i] = prenum;
			fr >> prenum;
			value[13][i] = prenum;
			fr >> prenum;
			value[14][i] = prenum;
			fr >> prenum;
			value[15][i] = prenum;
			fr >> prenum;
			value[16][i] = prenum;
			fr >> prenum;
			value[17][i] = prenum;
			fr >> prenum;
			value[18][i] = prenum;
			fr >> prenum;
			value[19][i] = prenum;
			fr >> prenum;
			value[20][i] = prenum;
		}
	}
	else 
	{
		while (true)
		{
			if (rrow > row-1921)
			{
				for (i = 0;i < 120;i++)
				{
					fr >> prenum;
					value[0][i] = prenum;
					fr >> prenum;
					value[1][i] = prenum;
					fr >> prenum;
					value[2][i] = prenum;
					fr >> prenum;
					value[3][i] = prenum;
					fr >> prenum;
					value[4][i] = prenum;
					fr >> prenum;
					value[5][i] = prenum;
					fr >> prenum;
					value[6][i] = prenum;
					fr >> prenum;
					value[7][i] = prenum;
					fr >> prenum;
					value[8][i] = prenum;
					fr >> prenum;
					value[9][i] = prenum;
					fr >> prenum;
					value[10][i] = prenum;
					fr >> prenum;
					value[11][i] = prenum;
					fr >> prenum;
					value[12][i] = prenum;
					fr >> prenum;
					value[13][i] = prenum;
					fr >> prenum;
					value[14][i] = prenum;
					fr >> prenum;
					value[15][i] = prenum;
					fr >> prenum;
					value[16][i] = prenum;
					fr >> prenum;
					value[17][i] = prenum;
					fr >> prenum;
					value[18][i] = prenum;
					fr >> prenum;
					value[19][i] = prenum;
					fr >> prenum;
					value[20][i] = prenum;
				}
			}
			else
			{
				for (i = 0;i < 21;i++)
					fr >> prenum;
				rrow++;
			}
		}
	}
	
	fr.close();

}