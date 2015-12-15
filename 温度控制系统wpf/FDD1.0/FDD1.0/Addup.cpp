double Addup(int n,double x[])
{
	double ans;

	if(n <= 0)
	{
		ans = -1;
		return ans;
	}
	else
		if(n <= 1)
		{
			ans = x[0];
			return ans;
		}

	ans = x[n-1] + Addup(n-1,x);
	return ans;
}