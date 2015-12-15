void XD(double value[5])
{
	double Rvalue[5];

	Rvalue[0] = (value[0] + value[1] + value[2] + value[3] + value[4])/5;
	Rvalue[1] = (value[1] + value[2] + value[3] + value[4])/4;
	Rvalue[2] = (value[2] + value[3] + value[4])/3;
	Rvalue[3] = (value[3] + value[4])/2;
	Rvalue[4] = value[4];

	for (int i = 0;i < 5; i++)
		value[i] = Rvalue[i];
}