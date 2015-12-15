double average(double value[],int size)
{
	double sum;
	double ave;
	int i;

	sum = 0.0;
	for(i = 0; i < size; i++)
	{
		sum = sum + value[i];
	}
	ave = sum/size;

	return ave;
}