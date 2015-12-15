#include "faultdesign.h"
#include "HVAC.h"

void main()
{
	double d[20];//存放传感器精度
	int distance;//预测时间间隔
	int STEP;//预测时长（单位：分钟）
	d[0] = 0.1;
	d[1] = 0.1;
	d[2] = 0.00375;//MPa
	d[3] = 0.00375;
	d[4] = 0.1;
	d[5] = 0.1;
	d[6] = 0.1;
	d[7] = 0.1;
	d[8] = 0.01125;
	d[9] = 0.01125;
	d[10] = 0.1;
	d[11] = 0.1;
	d[12] = 0.1;
	d[13] = 0.1;
	d[14] = 0.01125;
	d[15] = 0.00375;
	d[16] = 0.1;
	d[17] = 0.1;
	d[18] = 0.00375;
	d[19] = 0.01125;
	distance = 60;
	STEP = 60;
	HVAC HVAC01(d,distance,STEP);
	HVAC01.Run();
}