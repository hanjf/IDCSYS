#include <iostream>
#include <fstream>

using namespace std;

double average(double value[],int size);
void ReadNowdata(double avevalue[21],double truevalue[21],int row)//读取当前数据，原始文件normal，由PAC导出
{
	char preread;
	double prenum;
	int i = 0;
	int rrow = 1;
	int line = 1;
	const int size = 2*15;//时间常数的2倍
	double data1[size];
	double data2[size];
	double data3[size];
	double data4[size];
	double data5[size];
	double data6[size];
	double data7[size];
	double data8[size];
	double data9[size];
	double data10[size];
	double data11[size];
	double data12[size];
	double data13[size];
	double data14[size];
	double data15[size];
	double data16[size];
	double data17[size];
	double data18[size];
	double data19[size];
	double data20[size];
	double data21[size];

	ifstream fr;
	fr.open("Readparameter.txt");
	if (fr.fail())
	{
		cout << "Input Readparameter.txt opening failed!" << endl;
		exit(1);
	}

	while (fr.get(preread))
	{
		if (preread == ',')
		{
			if (rrow > (row - size))
			{
				fr >> prenum;
				data1[i] = prenum;
				fr >> prenum;
				data2[i] = prenum;
				fr >> prenum;
				data3[i] = prenum;
				fr >> prenum;
				data4[i] = prenum;
				fr >> prenum;
				data5[i] = prenum;
				fr >> prenum;
				data6[i] = prenum;
				fr >> prenum;
				data7[i] = prenum;
				fr >> prenum;
				data8[i] = prenum;
				fr >> prenum;
				data9[i] = prenum;
				fr >> prenum;
				data10[i] = prenum;
				fr >> prenum;
				data11[i] = prenum;
				fr >> prenum;
				data12[i] = prenum;
				fr >> prenum;
				data13[i] = prenum;
				fr >> prenum;
				data14[i] = prenum;
				fr >> prenum;
				data15[i] = prenum;
				fr >> prenum;
				data16[i] = prenum;
				fr >> prenum;
				data17[i] = prenum;
				fr >> prenum;
				data18[i] = prenum;
				fr >> prenum;
				data19[i] = prenum;
				fr >> prenum;
				data20[i] = prenum;
				fr >> prenum;
				data21[i] = prenum;
				i++;
			}
		}
		if (preread == '\n')
			rrow++;
	}

	fr.close();

	//最新的滤波数据
	avevalue[0] = average(data1,size);
	avevalue[1] = average(data2,size);
	avevalue[2] = average(data3,size);
	avevalue[3] = average(data4,size);
	avevalue[4] = average(data5,size);
	avevalue[5] = average(data6,size);
	avevalue[6] = average(data7,size);
	avevalue[7] = average(data8,size);
	avevalue[8] = average(data9,size);
	avevalue[9] = average(data10,size);
	avevalue[10] = average(data11,size);
	avevalue[11] = average(data12,size);
	avevalue[12] = average(data13,size);
	avevalue[13] = average(data14,size);
	avevalue[14] = average(data15,size);
	avevalue[15] = average(data16,size);
	avevalue[16] = average(data17,size);
	avevalue[17] = average(data18,size);
	avevalue[18] = average(data19,size);
	avevalue[19] = average(data20,size);
	avevalue[20] = average(data21,size);
	//最新的实时数据
	truevalue[0] = data1[size-1];
	truevalue[1] = data2[size-1];
	truevalue[2] = data3[size-1];
	truevalue[3] = data4[size-1];
	truevalue[4] = data5[size-1];
	truevalue[5] = data6[size-1];
	truevalue[6] = data7[size-1];
	truevalue[7] = data8[size-1];
	truevalue[8] = data9[size-1];
	truevalue[9] = data10[size-1];
	truevalue[10] = data11[size-1];
	truevalue[11] = data12[size-1];
	truevalue[12] = data13[size-1];
	truevalue[13] = data14[size-1];
	truevalue[14] = data15[size-1];
	truevalue[15] = data16[size-1];
	truevalue[16] = data17[size-1];
	truevalue[17] = data18[size-1];
	truevalue[18] = data19[size-1];
	truevalue[19] = data20[size-1];
	truevalue[20] = data21[size-1];
}