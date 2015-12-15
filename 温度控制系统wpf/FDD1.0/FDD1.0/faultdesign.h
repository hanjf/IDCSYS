#ifndef FAULTDESIGN_H
#define FAULTDESIGN_H

class Evaporator
{
public:
	Evaporator();
	Evaporator(double Tfin,double Tfout,double Twin,double Twout,double Pin,double Pout,double dTfin,double dTfout,double dTwin,double dTwout);
	Evaporator(double Tfin,double Tfout,double Twin,double Twout,double Pin,double Pout,double dTfin,double dTfout,double dTwin,double dTwout,double module,double CP1,double CP2);
	void outputstateinfo();//输出状态信息
	void faultdetection();//计算状态向量
	void runStateinfo();//运行状态检测函数，并计算隶属度
	double getfluorinTin() {return T_fluorin_in;}
	double getfluorinTout() {return T_fluorin_out;}
	double getwaterTin() {return T_water_in;}
	double getwaterTout() {return T_water_out;}
	double getPin() {return P_in;}
	double getPout() {return P_out;}
	double getModule() {return Module;}
	double getCP1() {return CP1;}
	double getCP2() {return CP2;}
	double getdCP1() {return dCP1;}
	double getdCP2() {return dCP2;}
	int getStateinfo() {return stateinfo;}
	double getDegree() {return degree;}
private:
	double T_fluorin_in;
	double T_fluorin_out;
	double T_water_in;
	double T_water_out;
	double P_in;//氟侧进口压力
	double P_out;//氟侧出口压力
	double dt_Tfin;//氟侧进口温度测量精度
	double dt_Tfout;//氟侧出口温度测量精度
	double dt_Twin;//水侧进口温度测量精度
	double dt_Twout;//水侧出口温度测量精度
	double StandardModule;
	double StandardCP1;
	double StandardCP2;
	double Module;
	double CP1;
	double CP2;
	double dCP1;
	double dCP2;
	int stateinfo;
	double degree;
};

class Condenser
{
public:
	Condenser();
	Condenser(double Tfin,double Tfout,double Twin,double Twout,double Pin,double Pout,double dTfin,double dTfout,double dTwin,double dTwout);
	Condenser(double Tfin,double Tfout,double Twin,double Twout,double Pin,double Pout,double dTfin,double dTfout,double dTwin,double dTwout,double module,double CP1,double CP2);
	void outputstateinfo();
	void faultdetection();
	void runStateinfo();
	double getfluorinTin() {return T_fluorin_in;}
	double getfluorinTout() {return T_fluorin_out;}
	double getwaterTin() {return T_water_in;}
	double getwaterTout() {return T_water_out;}
	double getPin() {return P_in;}
	double getPout() {return P_out;}
	double getModule() {return Module;}
	double getCP1() {return CP1;}
	double getCP2() {return CP2;}
	double getdCP1() {return dCP1;}
	double getdCP2() {return dCP2;}
	int getStateinfo() {return stateinfo;}
	double getDegree() {return degree;}
private:
	double T_fluorin_in;
	double T_fluorin_out;
	double T_water_in;
	double T_water_out;
	double P_in;//氟侧进口压力
	double P_out;//氟侧出口压力
	double dt_Tfin;//氟侧进口温度测量精度
	double dt_Tfout;//氟侧出口温度测量精度
	double dt_Twin;//水侧进口温度测量精度
	double dt_Twout;//水侧出口温度测量精度
	double StandardModule;
	double StandardCP1;
	double StandardCP2;
	double Module;
	double CP1;
	double CP2;
	double dCP1;
	double dCP2;
	int stateinfo;
	double degree;
};

class ExpansionValue
{
public:
	ExpansionValue();
	ExpansionValue(double Tin,double Tout,double Pin,double Pout,double dPin,double dPout);
	ExpansionValue(double Tin,double Tout,double Pin,double Pout,double dPin,double dPout,double module,double cp);
	void outputstateinfo();
	void faultdetection();
	void runStateinfo();
	double getTin() {return T_in;}
	double getTout() {return T_out;}
	double getPin() {return P_in;}
	double getPout() {return P_out;}
	double getCP() {return CP;}
	double getdCP() {return dCP;}
	double getModule() {return Module;}
	int getStateinfo() {return stateinfo;}
	double getDegree() {return degree;}
private:
	double T_in;
	double T_out;
	double P_in;
	double P_out;
	double dP_in;
	double dP_out;
	double StandardModule;
	double StandardCP;
	double CP;
	double dCP;
	double Module;
	int stateinfo;
	double degree;
};

class Compressor
{
public:
	Compressor();
	Compressor(double Tin,double Tout,double Pin,double Pout,double dTin,double dTout,double w);
	Compressor(double Tin,double Tout,double Pin,double Pout,double dTin,double dTout,double w,double module,double cp);
	void outputstateinfo();
	void faultdetection();
	void runStateinfo();
	double getTin() {return T_in;}
	double getTout() {return T_out;}
	double getPin() {return P_in;}
	double getPout() {return P_out;}
	double getW() {return W;}
	double getCP() {return CP;}
	double getdCP() {return dCP;}
	double getModule() {return Module;}
	int getStateinfo() {return stateinfo;}
	double getDegree() {return degree;}
private:
	double T_in;
	double T_out;
	double P_in;
	double P_out;
	double dT_in;
	double dT_out;
	double W;
	double StandardModule;
	double StandardCP;
	double CP;
	double dCP;
	double Module;
	int stateinfo;
	double degree;
};

class Tunnel
{
public:
	Tunnel();
	Tunnel(double Pin,double Pout,double dPin,double dPout);
	Tunnel(double Pin,double Pout,double dPin,double dPout,double module,double cp);
	void outputstateinfo();
	void faultdetection();
	void runStateinfo();
	double getPin() {return P_in;}
	double getPout() {return P_out;}
	double getCP() {return CP;}
	double getdCP() {return dCP;}
	double getModule() {return Module;}
	int getStateinfo() {return stateinfo;}
	double getDegree() {return degree;}
private:
	double P_in;
	double P_out;
	double dP_in;
	double dP_out;
	double StandardModule;
	double StandardCP;
	double CP;
	double dCP;
	double Module;
	int stateinfo;
	double degree;
};



#endif