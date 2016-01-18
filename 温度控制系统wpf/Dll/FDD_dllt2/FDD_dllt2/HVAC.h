#ifndef HVAC_H
#define HCAC_H
#include "faultdesign.h"

class HVAC
{
public:
	Evaporator NowEvap;
	Evaporator ForEvap;
	Condenser NowCond;
	Condenser ForCond;
	Compressor NowComp;
	Compressor ForComp;
	ExpansionValue NowExpa;
	ExpansionValue ForExpa;
	Tunnel NowComp_Cond;
	Tunnel NowCond_Expa;
	Tunnel NowExpa_Evap;
	Tunnel NowEvap_Comp;
	Tunnel ForComp_Cond;
	Tunnel ForCond_Expa;
	Tunnel ForExpa_Evap;
	Tunnel ForEvap_Comp;
	HVAC(double d[20],int Distance,int Step);
	void Standard();//计算标准故障向量
	void NowState();//计算当前运行状态
	void ForecastState();//预测未来运行状态
	void Run();//运行故障诊断与预警
	void PutData();//写入数据
	void OutputInfo();//输出当前状态信息
	void OupputData();//输出数据信息
	int getdistance() {return distance;}
	int getstep() {return step;}
	double getEavfinT() {return Now_Eva_f_in_T;}
	double getEvafoutT() {return Now_Eva_f_out_T;}
	double getEvafinP() {return Now_Eva_f_in_P;}
	double getEvafoutP() {return Now_Eva_f_out_P;}
	double getEvawinT() {return Now_Eva_w_in_T;}
	double getEvawoutT() {return Now_Eva_w_out_T;}
	double getConfinT() {return Now_Con_f_in_T;}
	double getConfoutT() {return Now_Con_f_out_T;}
	double getConfinP() {return Now_Con_f_in_P;}
	double getConfoutP() {return Now_Con_f_out_P;}
	double getConwinT() {return Now_Con_w_in_T;}
	double getConwoutT() {return Now_Con_w_out_T;}
	double getExpinP() {return Now_Exp_in_P;}
	double getExpoutP() {return Now_Exp_out_P;}
	double getExpinT() {return Now_Exp_in_T;}
	double getExpoutT() {return Now_Exp_out_T;}
	double getCominP() {return Now_Com_in_P;}
	double getComoutP() {return Now_Com_out_P;}
	double getCominT() {return Now_Com_in_T;}
	double getComoutT() {return Now_Com_out_T;}
	double getComW() {return Now_Com_W;}
	int getNowstate() {return nowstate;}
	int getForecastState() {return forecaststate;}
private:
	static int number;
	char filenormal[40];
	char filefault[40];
	char fileright[40];
	int distance;//预测时间间隔
	int step;//预测时长，分钟为单位
//传感器精度
	double Eva_f_in_dt;
	double Eva_f_out_dt;
	double Eva_f_in_dp;
	double Eva_f_out_dp;
	double Eva_w_in_dt;
	double Eva_w_out_dt;
	double Con_f_in_dt;
	double Con_f_out_dt;
	double Con_f_in_dp;
	double Con_f_out_dp;
	double Con_w_in_dt;
	double Con_w_out_dt;
	double Exp_in_dt;
	double Exp_out_dt;
	double Exp_in_dp;
	double Exp_out_dp;
	double Com_in_dt;
	double Com_out_dt;
	double Com_in_dp;
	double Com_out_dp;
//标准
	double Evap_CP1;
	double Evap_CP2;
	double Evap_module;
	double Cond_CP1;
	double Cond_CP2;
	double Cond_module;
	double Expa_CP;
	double Expa_module;
	double Comp_CP;
	double Comp_module;
	double TC_C_CP;
	double TC_C_module;
	double TC_E_CP;
	double TC_E_module;
	double TE_E_CP;
	double TE_E_module;
	double TE_C_CP;
	double TE_C_module;
//当前时刻参数
	double Now_Eva_f_in_T;
	double Now_Eva_f_out_T;
	double Now_Eva_f_in_P;
	double Now_Eva_f_out_P;
	double Now_Eva_w_in_T;
	double Now_Eva_w_out_T;
	double Now_Con_f_in_T;
	double Now_Con_f_out_T;
	double Now_Con_f_in_P;
	double Now_Con_f_out_P;
	double Now_Con_w_in_T;
	double Now_Con_w_out_T;
	double Now_Exp_in_P;
	double Now_Exp_out_P;
	double Now_Exp_in_T;
	double Now_Exp_out_T;
	double Now_Com_in_P;
	double Now_Com_out_P;
	double Now_Com_in_T;
	double Now_Com_out_T;
	double Now_Com_W;
//运行状态
	int nowstate;
	int forecaststate;
};

#endif