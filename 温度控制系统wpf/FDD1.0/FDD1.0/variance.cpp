#include <cmath>
double average(double value[],int size);
double variance(double value[],int size)
{
	double ave;
	double ans;
	int i;

	//��ƽ��ֵ
	ave = average(value,size);	

	//���׼��
	ans = 0;
	for(i = 0; i < size; i++)
	{
		ans = ans + (value[i] - ave)*(value[i] - ave);
	}
	ans = sqrt(ans/(size-1));
	
	return ans;
}