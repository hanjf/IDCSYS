#include <cmath>
using namespace std;
double Addup(int n,double x[]);
double variance(double value[],int size);
double average(double value[],int size);
void XD(double value[5]);
void forecast(double x[5], int time, double value[2])
{
	double x_sum[5];//累加处理后的参数
	double Y[4];
	double B[4][2];
	double A[4][4];
	double A_determinant;//A的行列式
	double IA[4][4];
	double c,u;
	double for_x_sum[5];//累加处理后的预测值
	double for_x[5];//参数的模型计算值
	double eps[5];//残差值
	double fort_x;//预测值
	double deviation[5];//相对误差
	double ad;//平均相对误差
	double final_ad = 0;//最终平均相对误差
	int i,k;

	XD(x);
	XD(x);

	//预测参数
	for(k = 1; k <= time; k++)
	{
		//预处理
		for(i = 1; i <= 4; i++)
		{
			if(abs(x[i] - x[i-1]) < 1e-10)
				x[i] = x[i] + x[i]/1000;
		}

		//进行累加处理
		for(i = 1; i <= 5; i++)
		{
			x_sum[i-1] = Addup(i,x);
		}

		for(i = 1; i <= 4; i++)
		{
			Y[i-1] = x[i];
			B[i-1][0] = -(x_sum[i-1] + x_sum[i])/2.0;
			B[i-1][1] = 1.0;
		}

		A[0][0] = B[0][0]*B[0][0] + B[1][0]*B[1][0] + B[2][0]*B[2][0] + B[3][0]*B[3][0];
		A[0][1] = B[0][0]*B[0][1] + B[1][0]*B[1][1] + B[2][0]*B[2][1] + B[3][0]*B[3][1];
		A[1][0] = B[0][1]*B[0][0] + B[1][1]*B[1][0] + B[2][1]*B[2][0] + B[3][1]*B[3][0];
		A[1][1] = B[0][1]*B[0][1] + B[1][1]*B[1][1] + B[2][1]*B[2][1] + B[3][1]*B[3][1];

		A_determinant = A[0][0]*A[1][1] - A[0][1]*A[1][0];

		IA[0][0] = A[1][1]/A_determinant;
		IA[0][1] = -A[0][1]/A_determinant;
		IA[1][0] = -A[1][0]/A_determinant;
		IA[1][1] = A[0][0]/A_determinant;

		c = (IA[0][0]*B[0][0] + IA[0][1]*B[0][1])*Y[0] + (IA[0][0]*B[1][0] + IA[0][1]*B[1][1])*Y[1] + (IA[0][0]*B[2][0] + IA[0][1]*B[2][1])*Y[2] + (IA[0][0]*B[3][0] + IA[0][1]*B[3][1])*Y[3];
		u = (IA[1][0]*B[0][0] + IA[1][1]*B[0][1])*Y[0] + (IA[1][0]*B[1][0] + IA[1][1]*B[1][1])*Y[1] + (IA[1][0]*B[2][0] + IA[1][1]*B[2][1])*Y[2] + (IA[1][0]*B[3][0] + IA[1][1]*B[3][1])*Y[3];
		
		for (i = 0;i < 5;i++)
		{
			for_x_sum[i] = (x[0] - u/c)*pow(2.71828,-c*(i+1)) + u/c;
		}

		//计算参数的模型计算值
		for_x[0] = x[0];
		for_x[1] = for_x_sum[0] - x[0];
		for (i = 2;i < 5;i++)
		{
			for_x[i] = for_x_sum[i] - for_x_sum[i-1];
		}

		// 计算模型的残差值
		for (i = 0;i < 5;i++)
		{
			eps[i] = x[i] - for_x[i];
		}

		fort_x = for_x_sum[4] - x_sum[4];

		for (i = 0;i < 5;i++)
			deviation[i] = eps[i]/x[i];

		ad = abs(average(deviation,5));

		if (ad > final_ad)
			final_ad = ad;

		//用新得到的预测参数代替最老的一个历史参数
		for (i = 1; i <= 4; i++)
		{
			x[i-1] = x[i];
		}

		x[4] = fort_x;
	}

	value[1] = final_ad;

	value[0] = fort_x;
}