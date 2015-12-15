#include <iostream>
#include <fstream>

using namespace std;

double average(double value[],int size);
void Readparameter(double value[21][5],int distance,int row)//value[0～4]为滤波处理后的用于预测的数据，原始文件normal，由PAC导出
{
	const int totalline = 21;
	char preread;//预读字符
	double prenum;//预读数据
	int i = 0;//数组编号
	int count = 0;//记录读取数据的行数
	int rrow = 1;//记录读取到的文件行数
	const int size = 2*15;//设备时间常数的2倍
	const int totalsize = size*5;
	double data[21][totalsize];//滤波数据
	double aver1[21][size];
	double aver2[21][size];
	double aver3[21][size];
	double aver4[21][size];
	double aver5[21][size];

	ifstream fr;
	fr.open("Readparameter.txt");
	if (fr.fail())
	{
		cout << "Input Readparameter.txt opening failed!" << endl;
		exit(1);
	}
	
//读取第一排标题
//	do
//	{
//		fr.get(preread);
//	}while (preread != '\n');

	//读取第type列需要的数据
	while (fr.get(preread))
	{
		if (preread == ',')
		{
			if (rrow > (row - (4*distance + size)))//有标题多减1
			{
				count++;
				if (count%distance <= size && count%distance >= 1)
				{
					fr >> prenum;
					data[0][i] = prenum;
					fr >> prenum;
					data[1][i] = prenum;
					fr >> prenum;
					data[2][i] = prenum;
					fr >> prenum;
					data[3][i] = prenum;
					fr >> prenum;
					data[4][i] = prenum;
					fr >> prenum;
					data[5][i] = prenum;
					fr >> prenum;
					data[6][i] = prenum;
					fr >> prenum;
					data[7][i] = prenum;
					fr >> prenum;
					data[8][i] = prenum;
					fr >> prenum;
					data[9][i] = prenum;
					fr >> prenum;
					data[10][i] = prenum;
					fr >> prenum;
					data[11][i] = prenum;
					fr >> prenum;
					data[12][i] = prenum;
					fr >> prenum;
					data[13][i] = prenum;
					fr >> prenum;
					data[14][i] = prenum;
					fr >> prenum;
					data[15][i] = prenum;
					fr >> prenum;
					data[16][i] = prenum;
					fr >> prenum;
					data[17][i] = prenum;
					fr >> prenum;
					data[18][i] = prenum;
					fr >> prenum;
					data[19][i] = prenum;
					fr >> prenum;
					data[20][i] = prenum;
					i++;
				}
			}
		}
		if (preread == '\n')
			rrow++;
	}

	fr.close();

	for (int j=0;j<21;j++)
	{
		for (i=0;i<size;i++)
			aver1[j][i] = data[j][i];
		for (i=0;i<size;i++)
			aver2[j][i] = data[j][i+15];
		for (i=0;i<size;i++)
			aver3[j][i] = data[j][i+30];
		for (i=0;i<size;i++)
			aver4[j][i] = data[j][i+45];
		for (i=0;i<size;i++)
			aver5[j][i] = data[j][i+60];
	}

	for (i=0;i<21;i++)
	{
		value[i][0] = average(aver1[i],size);
		value[i][1] = average(aver2[i],size);
		value[i][2] = average(aver3[i],size);
		value[i][3] = average(aver4[i],size);
		value[i][4] = average(aver5[i],size);
	}
}