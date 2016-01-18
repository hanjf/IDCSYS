#include "faultdesign.h"
#include <cmath>
#include <iostream>

using namespace std;

Evaporator::Evaporator()
{}

Evaporator::Evaporator(double Tfin,double Tfout,double Twin,double Twout,double Pin,double Pout,double dTfin,double dTfout,double dTwin,double dTwout)
{
	T_fluorin_in = Tfin;
	T_fluorin_out = Tfout;
	T_water_in = Twin;
	T_water_out = Twout;
	P_in = Pin;
	P_out = Pout;
	dt_Tfin = dTfin;
	dt_Tfout = dTfout;
	dt_Twin = dTwin;
	dt_Twout = dTwout;
	StandardCP1 = 0;
	StandardCP2 = 0;
}

Evaporator::Evaporator(double Tfin,double Tfout,double Twin,double Twout,double Pin,double Pout,double dTfin,double dTfout,double dTwin,double dTwout,double module,double CP1,double CP2)
{
	T_fluorin_in = Tfin;
	T_fluorin_out = Tfout;
	T_water_in = Twin;
	T_water_out = Twout;
	P_in = Pin;
	P_out = Pout;
	dt_Tfin = dTfin;
	dt_Tfout = dTfout;
	dt_Twin = dTwin;
	dt_Twout = dTwout;
	StandardModule = module;
	StandardCP1 = CP1;
	StandardCP2 = CP2;
}

void Evaporator::faultdetection()
{
	double tmax;
	double tmin;
	double temp;

	tmax = abs(T_water_in - T_fluorin_out);
	tmin = abs(T_water_out - T_fluorin_in);

	if (tmin > tmax)
	{
		temp = tmax;
		tmax = tmin;
		tmin = temp;
	}

	CP1 = (abs(T_water_in - T_water_out))/((tmax - tmin)/log(tmax/tmin));
	CP2 = (T_water_in - T_water_out)/(T_fluorin_out - T_fluorin_in);

	if (StandardCP1 == 0)
		StandardCP1 = CP1;
	if (StandardCP2 == 0)
		StandardCP2 = CP2;

	dCP1 = CP1 - StandardCP1;
	dCP2 = CP2 - StandardCP2;
	Module = sqrt(dCP1*dCP1 + dCP2*dCP2);

	if(StandardModule == 0)
		StandardModule = 10;

}

void Evaporator::runStateinfo()
{
	double ModuleMax;
	double ModuleMin;
	double CP_max[2];
	double CP_min[2];
	double d_CP_max[2];
	double d_CP_min[2];

	if ((T_water_in - T_fluorin_out) > (T_water_out - T_fluorin_in))
	{
		CP_max[0] = (T_water_in+dt_Twin-T_water_out+dt_Twout)*(log(T_water_in+dt_Twin-T_fluorin_out+dt_Tfout) - log(T_water_out-dt_Twout-T_fluorin_in-dt_Tfin))/((T_water_in-T_fluorin_out) - (T_water_out-T_fluorin_in));
		CP_min[0] = (T_water_in-dt_Twin-T_water_out-dt_Twout)*(log(T_water_in-dt_Twin-T_fluorin_out-dt_Tfout) - log(T_water_out+dt_Twout-T_fluorin_in+dt_Tfin))/((T_water_in-T_fluorin_out) - (T_water_out-T_fluorin_in));
	}
	else
	{
		CP_max[0] = (T_water_in+dt_Twin-T_water_out+dt_Twout)*(log(T_water_out+dt_Twout-T_fluorin_in+dt_Tfin) - log(T_water_in-dt_Twin-T_fluorin_out-dt_Tfout))/((T_water_out-T_fluorin_in) - (T_water_in-T_fluorin_out));
		CP_min[0] = (T_water_in-dt_Twin-T_water_out-dt_Twout)*(log(T_water_out-dt_Twout-T_fluorin_in-dt_Tfin) - log(T_water_in+dt_Twin-T_fluorin_out+dt_Tfout))/((T_water_out-T_fluorin_in) - (T_water_in-T_fluorin_out));
	}

	CP_max[1] = (T_water_in+dt_Twin-T_water_out+dt_Twout)/(T_fluorin_out-dt_Tfout-T_fluorin_in-dt_Tfin);
	CP_min[1] = (T_water_in-dt_Twin-T_water_out-dt_Twout)/(T_fluorin_out+dt_Tfout-T_fluorin_in+dt_Tfin);

	d_CP_max[0] = CP_max[0] - CP1;
	d_CP_min[0] = CP_min[0] - CP1;
	d_CP_max[1] = CP_max[1] - CP2;
	d_CP_min[1] = CP_min[1] - CP2;

	if (dCP1 >= 0 && dCP2 >= 0)
	{
		ModuleMax = StandardModule + sqrt(d_CP_max[0]*d_CP_max[0] + d_CP_max[1]*d_CP_max[1]);
		ModuleMin = StandardModule - sqrt(d_CP_min[0]*d_CP_min[0] + d_CP_min[1]*d_CP_min[1]);
	}
	else if (dCP1 >= 0 && dCP2 < 0)
	{
		ModuleMax = StandardModule + sqrt(d_CP_max[0]*d_CP_max[0] + d_CP_min[1]*d_CP_min[1]);
		ModuleMin = StandardModule - sqrt(d_CP_min[0]*d_CP_min[0] + d_CP_max[1]*d_CP_max[1]);
	}
	else if (dCP1 < 0 && dCP2 < 0)
	{
		ModuleMax = StandardModule + sqrt(d_CP_min[0]*d_CP_min[0] + d_CP_min[1]*d_CP_min[1]);
		ModuleMin = StandardModule - sqrt(d_CP_max[0]*d_CP_max[0] + d_CP_max[1]*d_CP_max[1]);
	}
	else
	{
		ModuleMax = StandardModule + sqrt(d_CP_min[0]*d_CP_min[0] + d_CP_max[1]*d_CP_max[1]);
		ModuleMin = StandardModule - sqrt(d_CP_max[0]*d_CP_max[0] + d_CP_min[1]*d_CP_min[1]);
	}

	if (ModuleMin <= 0)
		ModuleMin = StandardModule;

	if (Module < ModuleMin)
		degree = 0;
	else if (Module > ModuleMax)
		degree = 1;
	else
		degree = (Module - ModuleMin)/(ModuleMax - ModuleMin);

	if (degree > 0)
	{
		if (dCP1 > 0  && dCP2 > 0)
			stateinfo = 1;//冷冻水不足
		else if (dCP1 < 0 && abs(dCP2) <= abs(d_CP_min[1]))
			stateinfo = 2;//蒸发器结垢
		else if (dCP2 < 0 && abs(dCP1) <= abs(d_CP_min[0]))
			stateinfo = 3;//制冷剂不足
		else 
			stateinfo = 4;//未知错误
	}
	else 
		stateinfo = 0;

	cout << "Evaporator" << endl;
	cout << "StandardModule=" << StandardModule << endl;
	cout << "ModuleMax=" << ModuleMax << ',' << "ModuleMin=" << ModuleMin << endl;
	cout << "Space=(" << dCP1 << ',' << dCP2 << ")" << endl;
	cout << "Module=" << Module << endl;
	cout << "Twin=" << T_water_in << ',' << "Twout=" << T_water_out << endl;
	cout << "Tfin=" << T_fluorin_in << ',' << "Tfout=" << T_fluorin_out << endl;
	cout << ' ' << endl;
}

void Evaporator::outputstateinfo()
{
	cout << "蒸发器state:" << stateinfo << endl;
	cout << "状态信息:" << endl;
	
	if (stateinfo == 0)
	{
		cout << "蒸发器运行正常!" << endl;
		cout << endl;
	}
	else if (stateinfo == 1)
		cout << "冷冻水不足!" << endl;
	else if (stateinfo == 2)
		cout << "蒸发器结垢!" << endl;
	else if (stateinfo == 3)
		cout << "制冷剂不足!" << endl;
	else 
	{
		cout << "未知错误!" << endl;
		cout << "状态向量:" << "(" << dCP1 << "," << dCP2 << ")" << endl;
	}

	if (stateinfo != 0)
	{
		cout << "隶属度:" << degree << endl;
		cout << endl;
	}
}

Condenser::Condenser()
{}

Condenser::Condenser(double Tfin, double Tfout, double Twin, double Twout, double Pin, double Pout, double dTfin, double dTfout, double dTwin, double dTwout)
{
	T_fluorin_in = Tfin;
	T_fluorin_out = Tfout;
	T_water_in = Twin;
	T_water_out = Twout;
	P_in = Pin;
	P_out = Pout;
	dt_Tfin = dTfin;
	dt_Tfout = dTfout;
	dt_Twin = dTwin;
	dt_Twout = dTwout;
	StandardCP1 = 0;
	StandardCP2 = 0;
}

Condenser::Condenser(double Tfin, double Tfout, double Twin, double Twout, double Pin, double Pout, double dTfin, double dTfout, double dTwin, double dTwout, double module, double CP1, double CP2)
{
	T_fluorin_in = Tfin;
	T_fluorin_out = Tfout;
	T_water_in = Twin;
	T_water_out = Twout;
	P_in = Pin;
	P_out = Pout;
	dt_Tfin = dTfin;
	dt_Tfout = dTfout;
	dt_Twin = dTwin;
	dt_Twout = dTwout;
	StandardModule = module;
	StandardCP1 = CP1;
	StandardCP2 = CP2;
}

void Condenser::faultdetection()
{
	double tmax;
	double tmin;
	double temp;

	tmax = abs(T_fluorin_in - T_water_out);
	tmin = abs(T_fluorin_out - T_water_in);

	if (tmin > tmax)
	{
		temp = tmax;
		tmax = tmin;
		tmin = temp;
	}

	CP1 = (abs(T_water_out - T_water_in))/((tmax - tmin)/log(tmax/tmin));
	CP2 = (T_water_out - T_water_in)/(T_fluorin_in - T_fluorin_out);

	if (StandardCP1 == 0)
		StandardCP1 = CP1;
	if (StandardCP2 == 0)
		StandardCP2 = CP2;

	dCP1 = CP1 - StandardCP1;
	dCP2 = CP2 - StandardCP2;
	Module = sqrt(dCP1*dCP1 + dCP2*dCP2);
	
	if (StandardModule == 0)
		StandardModule = 10;
}

void Condenser::runStateinfo()
{
	double ModuleMax;
	double ModuleMin;
	double StandarddCP1;
	double StandarddCP2;
	double CP_max[2];
	double CP_min[2];
	double d_CP_max[2];
	double d_CP_min[2];

	if ((T_fluorin_in - T_water_out) > (T_fluorin_out - T_water_in))
	{
		CP_max[0] = (T_water_out+dt_Twout-T_water_in+dt_Twin)*(log(T_fluorin_in+dt_Tfin-T_water_out+dt_Twout) - log(T_fluorin_out-dt_Tfout-T_water_in-dt_Twin))/((T_fluorin_in-T_water_out) - (T_fluorin_out-T_water_in));
		CP_min[0] = (T_water_out-dt_Twout-T_water_in-dt_Twin)*(log(T_fluorin_in-dt_Tfin-T_water_out-dt_Twout) - log(T_fluorin_out+dt_Tfout-T_water_in+dt_Twin))/((T_fluorin_in-T_water_out) - (T_fluorin_out-T_water_in));
	}
	else
	{
		CP_max[0] = (T_water_out+dt_Twout-T_water_in+dt_Twin)*(log(T_fluorin_out+dt_Tfout-T_water_in+dt_Twin) - log(T_fluorin_in-dt_Tfin-T_water_out-dt_Twout))/((T_fluorin_out-T_water_in) - (T_fluorin_in-T_water_out));
		CP_min[0] = (T_water_out-dt_Twout-T_water_in-dt_Twin)*(log(T_fluorin_out-dt_Tfout-T_water_in-dt_Twin) - log(T_fluorin_in+dt_Tfin-T_water_out+dt_Twout))/((T_fluorin_out-T_water_in) - (T_fluorin_in-T_water_out));
	}

	CP_max[1] = (T_water_out+dt_Twout-T_water_in-dt_Twin)/(T_fluorin_in-dt_Tfin-T_fluorin_out-dt_Tfout);
	CP_min[1] = (T_water_out-dt_Twout-T_water_in-dt_Twin)/(T_fluorin_in+dt_Tfin-T_fluorin_out+dt_Tfout);

	d_CP_max[0] = CP_max[0] - CP1;
	d_CP_min[0] = CP_min[0] - CP1;
	d_CP_max[1] = CP_max[1] - CP2;
	d_CP_min[1] = CP_min[1] - CP2;

	if (abs(d_CP_max[0]) > abs(d_CP_min[0]))
		StandarddCP1 = abs(d_CP_min[0]);
	else
		StandarddCP1 = abs(d_CP_max[0]);

	if (abs(d_CP_max[1]) > abs(d_CP_min[1]))
		StandarddCP2 = abs(d_CP_min[1]);
	else
		StandarddCP2 = abs(d_CP_max[1]);

	if (dCP1 >= 0 && dCP2 >= 0)
	{
		ModuleMax = StandardModule + sqrt(d_CP_max[0]*d_CP_max[0] + d_CP_max[1]*d_CP_max[1]);
		ModuleMin = StandardModule - sqrt(d_CP_min[0]*d_CP_min[0] + d_CP_min[1]*d_CP_min[1]);
	}
	else if (dCP1 >= 0 && dCP2 < 0)
	{
		ModuleMax = StandardModule + sqrt(d_CP_max[0]*d_CP_max[0] + d_CP_min[1]*d_CP_min[1]);
		ModuleMin = StandardModule - sqrt(d_CP_min[0]*d_CP_min[0] + d_CP_max[1]*d_CP_max[1]);
	}
	else if (dCP1 < 0 && dCP2 < 0)
	{
		ModuleMax = StandardModule + sqrt(d_CP_min[0]*d_CP_min[0] + d_CP_min[1]*d_CP_min[1]);
		ModuleMin = StandardModule - sqrt(d_CP_max[0]*d_CP_max[0] + d_CP_max[1]*d_CP_max[1]);
	}
	else
	{
		ModuleMax = StandardModule + sqrt(d_CP_min[0]*d_CP_min[0] + d_CP_max[1]*d_CP_max[1]);
		ModuleMin = StandardModule - sqrt(d_CP_max[0]*d_CP_max[0] + d_CP_min[1]*d_CP_min[1]);
	}

	if (ModuleMin <= 0)
		ModuleMin = StandardModule;

	if (Module < ModuleMin)
		degree = 0;
	else if (Module > ModuleMax)
		degree = 1;
	else 
		degree = (Module - ModuleMin)/(ModuleMax - ModuleMin);

	if (degree > 0)
	{
		if (dCP1 > 0 && dCP2 > 0)
			stateinfo = 1;//冷却水不足
		else if (dCP1 < 0 && abs(dCP2) <= StandarddCP2)
			stateinfo = 2;//冷凝器结垢
		else if (dCP2 < 0 && abs(dCP1) <= StandarddCP1)
			stateinfo = 3;//制冷剂不足
		else 
			stateinfo = 4;//未知错误
	}
	else 
		stateinfo = 0;

	cout << "Condenser" << endl;
	cout << "StandardModule=" << StandardModule << endl;
	cout << "ModuleMax=" << ModuleMax << ',' << "ModuleMin=" << ModuleMin << endl;
	cout << "StandarddCP2=" << StandarddCP2 << endl;
	cout << "Space=(" << dCP1 << ',' << dCP2 << ")" << endl;
	cout << "Module=" << Module << endl;
	cout << "Twin=" << T_water_in << ',' << "Twout=" << T_water_out << endl;
	cout << "Tfin=" << T_fluorin_in << ',' << "Tfout=" << T_fluorin_out << endl;
	cout << ' ' << endl;
}

void Condenser::outputstateinfo()
{
	cout << "冷凝器state:" << stateinfo << endl;
	cout << "状态信息:" << endl;
	
	if (stateinfo == 0)
	{
		cout << "冷凝器运行正常!" << endl;
		cout << endl;
	}
	else if (stateinfo == 1)
		cout << "冷却水不足!" << endl;
	else if (stateinfo == 2)
		cout << "冷凝器结垢!" << endl;
	else if (stateinfo == 3)
		cout << "制冷剂不足!" << endl;
	else 
	{
		cout << "未知错误!" << endl;
		cout << "状态向量:" << "(" << dCP1 << "," << dCP2 << ")" << endl;
	}

	if (stateinfo != 0)
	{
		cout << "隶属度:" << degree << endl;
		cout << endl;
	}
}

ExpansionValue::ExpansionValue()
{}

ExpansionValue::ExpansionValue(double Tin, double Tout, double Pin, double Pout, double dPin, double dPout)
{
	T_in = Tin;
	T_out = Tout;
	P_in = Pin;
	P_out = Pout;
	dP_in = dPin;
	dP_out = dPout;
	StandardCP = 0;
}

ExpansionValue::ExpansionValue(double Tin, double Tout, double Pin, double Pout, double dPin, double dPout, double module, double cp)
{
	T_in = Tin;
	T_out = Tout;
	P_in = Pin;
	P_out = Pout;
	dP_in = dPin;
	dP_out = dPout;
	StandardCP = cp;
	StandardModule = module;
}

void ExpansionValue::faultdetection()
{
	CP = P_in - P_out;
	
	if (StandardCP == 0)
		StandardCP = CP;
	
	dCP = CP - StandardCP;
	Module = abs(dCP);

	if (StandardModule == 0)
		StandardModule = 10;
}

void ExpansionValue::runStateinfo()
{
	double ModuleMax;
	double ModuleMin;
	double CP_max;
	double CP_min;
	double d_CP_max;
	double d_CP_min;

	CP_max = P_in + dP_in - P_out + dP_out;
	CP_min = P_in - dP_in - P_out - dP_out;

	d_CP_max = CP_max - CP;
	d_CP_min = CP_min - CP;

	if (dCP >= 0)
	{
		ModuleMax = StandardModule + d_CP_max;
		ModuleMin = StandardModule + d_CP_min;
	}
	else 
	{
		ModuleMax = StandardModule - d_CP_min;
		ModuleMin = StandardModule - d_CP_max;
	}

	if (ModuleMin <= 0)
		ModuleMin = StandardModule;

	if (Module < ModuleMin)
		degree = 0;
	else if (Module > ModuleMax)
		degree = 1;
	else 
		degree = (Module - ModuleMin)/(ModuleMax - ModuleMin);

	if (degree > 0)
	{
		if (dCP > 0)
			stateinfo = 1;//开度过大
		else 
			stateinfo = 2;//开度过小
	}
	else 
		stateinfo = 0;

	cout << "ExpansionValue" << endl;
	cout << "StandardModule=" << StandardModule << endl;
	cout << "ModuleMax=" << ModuleMax << ',' << "ModuleMin=" << ModuleMin << endl;
	cout << "dCP=" << dCP << endl;
	cout << "Module=" << Module << endl;
	cout << "Pin=" << P_in << ',' << "Pout=" << P_out << endl;
	cout << ' ' << endl;
}

void ExpansionValue::outputstateinfo()
{
	cout << "膨胀阀state:" << stateinfo << endl;
	cout << "状态信息:" << endl;
	
	if (stateinfo == 0)
	{
		cout << "膨胀阀运行正常!" << endl;
		cout << endl;
	}
	else if (stateinfo == 1)
		cout << "膨胀阀开度过大!" << endl;
	else 
		cout << "膨胀阀开度过小!" << endl;
	
	if (stateinfo != 0)
	{
		cout << "隶属度:" << degree << endl;
		cout << endl;
	}
}

Compressor::Compressor()
{}

Compressor::Compressor(double Tin, double Tout, double Pin, double Pout, double dTin, double dTout, double w)
{
	T_in = Tin;
	T_out = Tout;
	P_in = Pin;
	P_out = Pout;
	dT_in = dTin;
	dT_out = dTout;
	W = w;
	StandardCP = 0;
}

Compressor::Compressor(double Tin, double Tout, double Pin, double Pout, double dTin, double dTout, double w, double module, double cp)
{
	T_in = Tin;
	T_out = Tout;
	P_in = Pin;
	P_out = Pout;
	dT_in = dTin;
	dT_out = dTout;
	W = w;
	StandardCP = cp;
	StandardModule = module;
}

void Compressor::faultdetection()
{
	CP = W/(T_out - T_in);

	if (StandardCP == 0)
		StandardCP = CP;
	
	dCP = CP - StandardCP;
	Module = abs(dCP);

	if (StandardModule == 0)
		StandardModule = 10;
}

void Compressor::runStateinfo()
{
	double ModuleMax;
	double ModuleMin;
	double CP_max;
	double CP_min;
	double d_CP_max;
	double d_CP_min;

	CP_max = W/(T_out - dT_out - T_in - dT_in);
	CP_min = W/(T_out + dT_out - T_in + dT_in);

	d_CP_max = CP_max - CP;
	d_CP_min = CP_min - CP;

	if (dCP >= 0)
	{
		ModuleMax = StandardModule + d_CP_max;
		ModuleMin = StandardModule + d_CP_min;
	}
	else
	{
		ModuleMax = StandardModule - d_CP_min;
		ModuleMin = StandardModule - d_CP_max;
	}

	if (ModuleMin <= 0)
		ModuleMin = StandardModule;

	if (Module < ModuleMin)
		degree = 0;
	else if (Module > ModuleMax)
		degree = 1;
	else 
		degree = (Module - ModuleMin)/(ModuleMax - ModuleMin);

	if (degree > 0)
	{
		if (dCP < 0)
			stateinfo = 1;
		else 
			stateinfo = 2;
	}
	else 
		stateinfo = 0;
	
	cout << "Compressor" << endl;
	cout << "StandardModule=" << StandardModule << endl;
	cout << "ModuleMax=" << ModuleMax << ',' << "ModuleMin=" << ModuleMin << endl;
	cout << "dCP=" << dCP << endl;
	cout << "Module=" << Module << endl;
	cout << "Tin=" << T_in << ',' << "Tout=" << T_out << endl;
	cout << ' ' << endl;
}

void Compressor::outputstateinfo()
{
	cout << "压缩机state:" << stateinfo << endl;
	cout << "状态信息:" << endl;

	if (stateinfo == 0)
	{
		cout << "压缩机运行正常!" << endl;
		cout << endl;
	}
	else if (stateinfo == 1)
		cout << "压缩机吸排气泄露!" << endl;
	else 
		cout << "未知压缩机故障!" << endl;

	if (stateinfo != 0)
	{
		cout << "隶属度:" << degree << endl;
		cout << endl;
	}
}

Tunnel::Tunnel()
{}

Tunnel::Tunnel(double Pin, double Pout, double dPin, double dPout)
{
	P_in = Pin;
	P_out = Pout;
	dP_in = dPin;
	dP_out = dPout;
	StandardCP = 0;
}

Tunnel::Tunnel(double Pin, double Pout, double dPin, double dPout, double module ,double cp)
{
	P_in = Pin;
	P_out = Pout;
	dP_in = dPin;
	dP_out = dPout;
	StandardModule = module;
	StandardCP = cp;
}

void Tunnel::faultdetection()
{
	CP = P_out - P_in;

	if (StandardCP == 0)
		StandardCP = CP;

	dCP= CP - StandardCP;
	Module = abs(dCP);

	if (StandardModule == 0)
		StandardModule = 10;
}

void Tunnel::runStateinfo()
{
	double ModuleMax;
	double ModuleMin;
	double CP_max;
	double CP_min;
	double d_CP_max;
	double d_CP_min;

	CP_max = P_out + dP_out - P_in + dP_in;
	CP_min = P_out - dP_out - P_in - dP_in;

	d_CP_max = CP_max - CP;
	d_CP_min = CP_min - CP;

	if (dCP >= 0)
	{
		ModuleMax = StandardModule + d_CP_max;
		ModuleMin = StandardModule + d_CP_min;
	}
	else 
	{
		ModuleMax = StandardModule - d_CP_min;
		ModuleMin = StandardModule - d_CP_max;
	}

	if (ModuleMin <= 0)
		ModuleMin = StandardModule;
	
	if (Module < ModuleMin)
		degree = 0;
	else if (Module > ModuleMax)
		degree = 1;
	else
		degree = (Module - ModuleMin)/(ModuleMax - ModuleMin);

	if (degree > 0)
	{
		if (dCP < 0)
			stateinfo = 1;
		else 
			stateinfo = 2;
	}
	else 
		stateinfo = 0;

	cout << "Tunnel" << endl;
	cout << "StandardModule=" << StandardModule << endl;
	cout << "ModuleMax=" << ModuleMax << ',' << "ModuleMin=" << ModuleMin << endl;
	cout << "dCP=" << dCP << endl;
	cout << "Module=" << Module << endl;
	cout << "Pin=" << P_in << ',' << "Pout=" << P_out << endl;
	cout << ' ' << endl;
}

void Tunnel::outputstateinfo()
{
	cout << "管道state：" << stateinfo << endl;
	cout << "状态信息：" << endl;

	if (stateinfo == 0)
	{
		cout << "管道正常！" << endl;
		cout << endl;
	}
	else if (stateinfo == 1)
		cout << "管道堵塞！" << endl;
	else
		cout << "未知错误！" << endl;

	if (stateinfo != 0)
	{
		cout << "隶属度：" << degree << endl;
		cout << endl;
	}
}