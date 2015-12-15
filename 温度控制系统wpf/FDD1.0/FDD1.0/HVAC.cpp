#include "HVAC.H"
#include <cmath>
#include <iostream>
#include <fstream>
#include <time.h>
#include <stdio.h>
#include <string>

using namespace std;

int ReaddataFileChange(char* filename);
int ReadparameterFileChange(char* filename);
void Readdata(double value[21][120],int row);
void Readparameter(double value[21][5],int distance,int row);
void forecast(double x[5], int time, double value[2]);
double average(double value[],int size);
double variance(double value[],int size);
void ReadNowdata(double avevalue[21],double truevalue[21],int row);
void WriteFile(double value[21],char* filename);

int HVAC::number = 0;

HVAC::HVAC(double d[20],int Distance,int Step)
{
	strcpy_s(filenormal,"data\\normal00.txt");
	strcpy_s(filefault,"data\\fault00.csv");
	strcpy_s(fileright,"data\\right00.csv");
	filenormal[11] = '0'+number/10;
	filefault[10] = '0'+number/10;
	fileright[10] = '0'+number/10;
	filenormal[12] = '0'+number%10;
	filefault[11] = '0'+number%10;
	filefault[11] = '0'+number%10;
	Eva_f_in_dt = d[0];
	Eva_f_out_dt = d[1];
	Eva_f_in_dp = d[2];
	Eva_f_out_dp = d[3];
	Eva_w_in_dt = d[4];
	Eva_w_out_dt = d[5];
	Con_f_in_dt = d[6];
	Con_f_out_dt = d[7];
	Con_f_in_dp = d[8];
	Con_f_out_dp = d[9];
	Con_w_in_dt = d[10];
	Con_w_out_dt = d[11];
	Exp_in_dt = d[12];
	Exp_out_dt = d[13];
	Exp_in_dp = d[14];
	Exp_out_dp = d[15];
	Com_in_dt = d[16];
	Com_out_dt = d[17];
	Com_in_dp = d[18];
	Com_out_dp = d[19];
	distance = Distance;
	step = Step;
	number++;
	//Evaporator NowEvap();
}

void HVAC::Standard()
{
	cout << "RunStandard" << endl;
//用于计算标准状态向量的数据数组(历史数据)
	const int amount = 120;
	double StandardVal[21][amount];
//标准
	Evaporator R_Evap[amount];
	Condenser R_Cond[amount];
	Compressor R_Comp[amount];
	ExpansionValue R_Expa[amount];
	Tunnel T_C_C[amount];
	Tunnel T_C_E[amount];
	Tunnel T_E_E[amount];
	Tunnel T_E_C[amount];
	double data_Eva_CP1[amount-1];
	double data_Eva_CP2[amount-1];
	double data_Eva_m[amount-1];
	double data_Con_CP1[amount-1];
	double data_Con_CP2[amount-1];
	double data_Con_m[amount-1];
	double data_Exp[amount-1];
	double data_Exp_CP[amount-1];
	double data_Com[amount-1];
	double data_Com_CP[amount-1];
	double data_TCC_CP[amount-1];
	double data_TCC_m[amount-1];
	double data_TCE_CP[amount-1];
	double data_TCE_m[amount-1];
	double data_TEE_CP[amount-1];
	double data_TEE_m[amount-1];
	double data_TEC_CP[amount-1];
	double data_TEC_m[amount-1];
//文件行数
	int rigfilerow;
//循环变量
	int i;
	const int x = 3;//标准倍数
//文件转换
	rigfilerow = ReaddataFileChange(fileright);
//读取历史数据并计算域值
	if (rigfilerow >= amount)
	{
		Readdata(StandardVal,rigfilerow);
		for (i = 0;i < amount;i++)
		{
			if (i == 0)
			{
				Evaporator Evap(StandardVal[0][i],StandardVal[1][i],StandardVal[4][i],StandardVal[5][i],StandardVal[2][i],StandardVal[3][i],Eva_f_in_dt,Eva_f_out_dt,Eva_w_in_dt,Eva_w_out_dt);
				R_Evap[i] = Evap;
				R_Evap[i].faultdetection();
				Condenser Cond(StandardVal[6][i],StandardVal[7][i],StandardVal[10][i],StandardVal[11][i],StandardVal[8][i],StandardVal[9][i],Con_f_in_dt,Con_f_out_dt,Con_w_in_dt,Con_w_out_dt);
				R_Cond[i] = Cond;
				R_Cond[i].faultdetection();
				ExpansionValue Expa(StandardVal[14][i],StandardVal[15][i],StandardVal[12][i],StandardVal[13][i],Exp_in_dp,Exp_out_dp);
				R_Expa[i] = Expa;
				R_Expa[i].faultdetection();
				Compressor Comp(StandardVal[18][i],StandardVal[19][i],StandardVal[16][i],StandardVal[17][i],Com_in_dt,Com_out_dt,StandardVal[20][i]);
				R_Comp[i] = Comp;
				R_Comp[i].faultdetection();
				Tunnel T1(StandardVal[17][i],StandardVal[8][i],Com_out_dp,Con_f_in_dp);
				T_C_C[i] = T1;
				T_C_C[i].faultdetection();
				Tunnel T2(StandardVal[9][i],StandardVal[12][i],Con_f_out_dp,Exp_in_dp);
				T_C_E[i] = T2;
				T_C_E[i].faultdetection();
				Tunnel T3(StandardVal[13][i],StandardVal[2][i],Exp_out_dp,Eva_f_in_dp);
				T_E_E[i] = T3;
				T_E_E[i].faultdetection();
				Tunnel T4(StandardVal[3][i],StandardVal[16][i],Eva_f_out_dp,Com_in_dp);
				T_E_C[i] = T4;
				T_E_C[i].faultdetection();
			}
			else 
			{
				Evaporator Evap(StandardVal[0][i],StandardVal[1][i],StandardVal[4][i],StandardVal[5][i],StandardVal[2][i],StandardVal[3][i],Eva_f_in_dt,Eva_f_out_dt,Eva_w_in_dt,Eva_w_out_dt,R_Evap[i-1].getModule(),R_Evap[i-1].getCP1(),R_Evap[i-1].getCP2());
				R_Evap[i] = Evap;
				R_Evap[i].faultdetection();
				Condenser Cond(StandardVal[6][i],StandardVal[7][i],StandardVal[10][i],StandardVal[11][i],StandardVal[8][i],StandardVal[9][i],Con_f_in_dt,Con_f_out_dt,Con_w_in_dt,Con_w_out_dt,R_Cond[i-1].getModule(),R_Cond[i-1].getCP1(),R_Cond[i-1].getCP2());
				R_Cond[i] = Cond;
				R_Cond[i].faultdetection();
				ExpansionValue Expa(StandardVal[14][i],StandardVal[15][i],StandardVal[12][i],StandardVal[13][i],Exp_in_dp,Exp_out_dp,R_Expa[i-1].getModule(),R_Expa[i-1].getCP());
				R_Expa[i] = Expa;
				R_Expa[i].faultdetection();
				Compressor Comp(StandardVal[18][i],StandardVal[19][i],StandardVal[16][i],StandardVal[17][i],Com_in_dt,Com_out_dt,StandardVal[20][i],R_Comp[i-1].getModule(),R_Comp[i-1].getCP());
				R_Comp[i] = Comp;
				R_Comp[i].faultdetection();
				Tunnel T1(StandardVal[17][i],StandardVal[8][i],Com_out_dp,Con_f_in_dp,T_C_C[i-1].getModule(),T_C_C[i-1].getCP());
				T_C_C[i] = T1;
				T_C_C[i].faultdetection();
				Tunnel T2(StandardVal[9][i],StandardVal[12][i],Con_f_out_dp,Exp_in_dp,T_C_E[i-1].getModule(),T_C_E[i-1].getCP());
				T_C_E[i] = T2;
				T_C_E[i].faultdetection();
				Tunnel T3(StandardVal[13][i],StandardVal[2][i],Exp_out_dp,Eva_f_in_dp,T_E_E[i-1].getModule(),T_E_E[i-1].getCP());
				T_E_E[i] = T3;
				T_E_E[i].faultdetection();
				Tunnel T4(StandardVal[3][i],StandardVal[16][i],Eva_f_out_dp,Com_in_dp,T_E_C[i-1].getModule(),T_E_C[i-1].getCP());
				T_E_C[i] = T4;
				T_E_C[i].faultdetection();
			}
		}

		for (i = 0;i < amount-1;i++)
		{
			data_Eva_CP1[i] = R_Evap[i+1].getCP1();
			data_Eva_CP2[i] = R_Evap[i+1].getCP2();
			data_Eva_m[i] = R_Evap[i+1].getModule();
			data_Con_CP1[i] = R_Cond[i+1].getCP1();
			data_Con_CP2[i] = R_Cond[i+1].getCP2();
			data_Con_m[i] = R_Cond[i+1].getModule();
			data_Exp[i] = R_Expa[i+1].getModule();
			data_Exp_CP[i] = R_Expa[i+1].getCP();
			data_Com[i] = R_Comp[i+1].getModule();
			data_Com_CP[i] = R_Comp[i+1].getCP();
			data_TCC_CP[i] = T_C_C[i+1].getCP();
			data_TCC_m[i] = T_C_C[i+1].getModule();
			data_TCE_CP[i] = T_C_E[i+1].getCP();
			data_TCE_m[i] = T_C_E[i+1].getModule();
			data_TEE_CP[i] = T_E_E[i+1].getCP();
			data_TEE_m[i] = T_E_E[i+1].getModule();
			data_TEC_CP[i] = T_E_C[i+1].getCP();
			data_TEC_m[i] = T_E_C[i+1].getModule();
		}

		Evap_CP1 = average(data_Eva_CP1,amount-1);
		Evap_CP2 = average(data_Eva_CP2,amount-1);
		Evap_module = sqrt((x*variance(data_Eva_CP1,amount-1))*(x*variance(data_Eva_CP1,amount-1)) + (x*variance(data_Eva_CP2,amount-1))*(x*variance(data_Eva_CP2,amount-1)));
		Cond_CP1 = average(data_Con_CP1,amount-1);
		Cond_CP2 = average(data_Con_CP2,amount-1);
		Cond_module = sqrt((x*variance(data_Con_CP1,amount-1))*(x*variance(data_Con_CP1,amount-1)) + (x*variance(data_Con_CP2,amount-1))*(x*variance(data_Con_CP2,amount-1)));
		Expa_CP = average(data_Exp_CP,amount-1);
		Expa_module = x*variance(data_Exp_CP,amount-1);
		Comp_CP = average(data_Com_CP,amount-1);
		Comp_module = x*variance(data_Com_CP,amount-1);
		TC_C_CP = average(data_TCC_CP,amount-1);
		TC_C_module = x*variance(data_TCC_CP,amount-1);
		TC_E_CP = average(data_TCE_CP,amount-1);
		TC_E_module = x*variance(data_TCE_CP,amount-1);
		TE_E_CP = average(data_TEE_CP,amount-1);
		TE_E_module = x*variance(data_TEE_CP,amount-1);
		TE_C_CP = average(data_TEC_CP,amount-1);
		TE_C_module = x*variance(data_TEC_CP,amount-1);
	}
	else 
	{
		Evap_CP1 = 0;
		Evap_CP2 = 0;
		Evap_module = 0;
		Cond_CP1 = 0;
		Cond_CP2 = 0;
		Cond_module = 0;
		Expa_CP = 0;
		Expa_module = 0;
		Comp_CP = 0;
		Comp_module = 0;
		TC_C_CP = 0;
		TC_C_module = 0;
		TC_E_CP = 0;
		TC_E_module = 0;
		TE_E_CP = 0;
		TE_E_module = 0;
		TE_C_CP = 0;
		TE_C_module = 0;
	}
	/*cout << Evap_CP1 << ',' << Evap_CP2 << ','<< Evap_module << endl;
	cout<< Cond_CP1 << ',' << Cond_CP2 << ',' << Cond_module << endl;
	cout<< Expa_CP << ',' << Expa_module << endl;
	cout<< Comp_CP << ',' << Comp_module << endl;
	cout<< TC_C_CP <<','<<TC_C_module<<','<<TC_E_CP<<','<<TC_E_module<<endl;
	cout<< TE_E_CP <<','<<TE_E_module<<','<<TE_C_CP<<','<<TE_C_module<<endl;*/
}

void HVAC::NowState()
{
	cout << "RunNowState" << endl;
//存放滤波数据和当前数据
	double AveVal[21];
	double TruVal[21];
//文件行数
	int norfilerow;
//文件转换
	norfilerow = ReadparameterFileChange(filenormal);

	if (norfilerow >= 180)
	{
//读取滤波数据和当前数据
		ReadNowdata(AveVal,TruVal,norfilerow);
		
//构造当前时刻的各设备对象
		
		NowEvap = Evaporator(AveVal[0],AveVal[1],AveVal[4],AveVal[5],AveVal[2],AveVal[3],Eva_f_in_dt,Eva_f_out_dt,Eva_w_in_dt,Eva_w_out_dt,Evap_module,Evap_CP1,Evap_CP2);
		NowCond = Condenser(AveVal[6],AveVal[7],AveVal[10],AveVal[11],AveVal[8],AveVal[9],Con_f_in_dt,Con_f_out_dt,Con_w_in_dt,Con_w_out_dt,Cond_module,Cond_CP1,Cond_CP2);
		NowExpa = ExpansionValue(AveVal[14],AveVal[15],AveVal[12],AveVal[13],Exp_in_dp,Exp_out_dp,Expa_module,Expa_CP);
		NowComp = Compressor(AveVal[18],AveVal[19],AveVal[16],AveVal[17],Com_in_dt,Com_out_dt,AveVal[20],Comp_module,Comp_CP);
		NowComp_Cond = Tunnel(AveVal[17],AveVal[8],Com_out_dp,Con_f_in_dp,TC_C_module,TC_C_CP);
		NowCond_Expa = Tunnel(AveVal[9],AveVal[12],Con_f_out_dp,Exp_in_dp,TC_E_module,TC_E_CP);
		NowExpa_Evap = Tunnel(AveVal[13],AveVal[2],Exp_out_dp,Eva_f_in_dp,TE_E_module,TE_E_CP);
		NowEvap_Comp = Tunnel(AveVal[3],AveVal[16],Eva_f_out_dp,Com_in_dp,TE_C_module,TE_C_CP);
//故障诊断
		NowEvap.faultdetection();
		NowCond.faultdetection();
		NowExpa.faultdetection();
		NowComp.faultdetection();
		NowComp_Cond.faultdetection();
		NowCond_Expa.faultdetection();
		NowExpa_Evap.faultdetection();
		NowEvap_Comp.faultdetection();
		NowEvap.runStateinfo();
		NowCond.runStateinfo();
		NowExpa.runStateinfo();
		NowComp.runStateinfo();
		NowComp_Cond.runStateinfo();
		NowCond_Expa.runStateinfo();
		NowExpa_Evap.runStateinfo();
		NowEvap_Comp.runStateinfo();
		
		if (NowEvap.getStateinfo() == 0 && NowCond.getStateinfo() == 0 && NowExpa.getStateinfo() == 0 && NowComp.getStateinfo() == 0 && NowComp_Cond.getStateinfo() == 0 && NowCond_Expa.getStateinfo() == 0 && NowExpa_Evap.getStateinfo() == 0 && NowEvap_Comp.getStateinfo() == 0)
		{
			nowstate = 0;//表示已经进行故障诊断计算且没有故障
			cout << "当前运行状态正常！" << endl;
		}
		else 
			nowstate = 1;//表示已经进行故障诊断计算并发生故障
		NowEvap.outputstateinfo();
		NowCond.outputstateinfo();
		NowExpa.outputstateinfo();
		NowComp.outputstateinfo();
		NowComp_Cond.outputstateinfo();
		NowCond_Expa.outputstateinfo();
		NowExpa_Evap.outputstateinfo();
		NowEvap_Comp.outputstateinfo();
	}
	else 
	{
		nowstate = -1;//表示没有进行故障诊断计算
		cout << "当前运行状态未检测！" << endl;
		cout << "当前数据量：" << norfilerow << endl; 
	}
	this->Now_Eva_f_in_T = TruVal[0];
	this->Now_Eva_f_out_T = TruVal[1];
	this->Now_Eva_f_in_P = TruVal[2];
	this->Now_Eva_f_out_P = TruVal[3];
	this->Now_Eva_w_in_T = TruVal[4];
	this->Now_Eva_w_out_T = TruVal[5];
	this->Now_Con_f_in_T = TruVal[6];
	this->Now_Con_f_out_T = TruVal[7];
	this->Now_Con_f_in_P = TruVal[8];
	this->Now_Con_f_out_P = TruVal[9];
	this->Now_Con_w_in_T = TruVal[10];
	this->Now_Con_w_out_T = TruVal[11];
	this->Now_Exp_in_P = TruVal[12];
	this->Now_Exp_out_P = TruVal[13];
	this->Now_Exp_in_T = TruVal[14];
	this->Now_Exp_out_T = TruVal[15];
	this->Now_Com_in_P = TruVal[16];
	this->Now_Com_out_P = TruVal[17];
	this->Now_Com_in_T = TruVal[18];
	this->Now_Com_out_T = TruVal[19];
	this->Now_Com_W = TruVal[20];
}

void HVAC::ForecastState()
{
	cout << "RunForecastState" << endl;
//用于存放当前数据和滤波数据的数组(当前数据)
	double ForVal[21][5];
//存放预测数据和预测精度的数组(预测数据)
	double forecast_Eva_f_in_T[2];
	double forecast_Eva_f_out_T[2];
	double forecast_Eva_f_in_P[2];
	double forecast_Eva_f_out_P[2];
	double forecast_Eva_w_in_T[2];
	double forecast_Eva_w_out_T[2];
	double forecast_Con_f_in_T[2];
	double forecast_Con_f_out_T[2];
	double forecast_Con_f_in_P[2];
	double forecast_Con_f_out_P[2];
	double forecast_Con_w_in_T[2];
	double forecast_Con_w_out_T[2];
	double forecast_Exp_in_P[2];
	double forecast_Exp_out_P[2];
	double forecast_Exp_in_T[2];
	double forecast_Exp_out_T[2];
	double forecast_Com_in_P[2];
	double forecast_Com_out_P[2];
	double forecast_Com_in_T[2];
	double forecast_Com_out_T[2];
	double forecast_Com_W[2];
//文件行数
	int norfilerow;
//文件转换
	norfilerow = ReadparameterFileChange(filenormal);

	if (norfilerow >= 900)
	{
		Readparameter(ForVal,distance,norfilerow);
		for(int m=0;m<5;m++)
			cout << ForVal[0][m] << endl;
//预测数据
		forecast(ForVal[0],step,forecast_Eva_f_in_T);
		forecast(ForVal[1],step,forecast_Eva_f_out_T);
		forecast(ForVal[2],step,forecast_Eva_f_in_P);
		forecast(ForVal[3],step,forecast_Eva_f_out_P);
		forecast(ForVal[4],step,forecast_Eva_w_in_T);
		forecast(ForVal[5],step,forecast_Eva_w_out_T);
		forecast(ForVal[6],step,forecast_Con_f_in_T);
		forecast(ForVal[7],step,forecast_Con_f_out_T);
		forecast(ForVal[8],step,forecast_Con_f_in_P);
		forecast(ForVal[9],step,forecast_Con_f_out_P);
		forecast(ForVal[10],step,forecast_Con_w_in_T);
		forecast(ForVal[11],step,forecast_Con_w_out_T);
		forecast(ForVal[12],step,forecast_Exp_in_P);
		forecast(ForVal[13],step,forecast_Exp_out_P);
		forecast(ForVal[14],step,forecast_Exp_in_T);
		forecast(ForVal[15],step,forecast_Exp_out_T);
		forecast(ForVal[16],step,forecast_Com_in_P);
		forecast(ForVal[17],step,forecast_Com_out_P);
		forecast(ForVal[18],step,forecast_Com_in_T);
		forecast(ForVal[19],step,forecast_Com_out_T);
		forecast(ForVal[20],step,forecast_Com_W);
//构造预测时刻的各设备对象
		ForEvap = Evaporator(forecast_Eva_f_in_T[0],forecast_Eva_f_out_T[0],forecast_Eva_w_in_T[0],forecast_Eva_w_out_T[0],forecast_Eva_f_in_P[0],forecast_Eva_f_out_P[0],Eva_f_in_dt,Eva_f_out_dt,Eva_w_in_dt,Eva_w_out_dt,Evap_module,Evap_CP1,Evap_CP2);
		ForCond = Condenser(forecast_Con_f_in_T[0],forecast_Con_f_out_T[0],forecast_Con_w_in_T[0],forecast_Con_w_out_T[0],forecast_Con_f_in_P[0],forecast_Con_f_out_P[0],Con_f_in_dt,Con_f_out_dt,Con_w_in_dt,Con_w_out_dt,Cond_module,Cond_CP1,Cond_CP2);
		ForExpa = ExpansionValue(forecast_Exp_in_T[0],forecast_Exp_out_T[0],forecast_Exp_in_P[0],forecast_Exp_out_P[0],Exp_in_dp,Exp_out_dp,Expa_module,Expa_CP);
		ForComp = Compressor(forecast_Com_in_T[0],forecast_Com_out_T[0],forecast_Com_in_P[0],forecast_Com_out_P[0],Com_in_dt,Com_out_dt,forecast_Com_W[0],Comp_module,Comp_CP);
		ForComp_Cond = Tunnel(forecast_Com_out_P[0],forecast_Con_f_in_P[0],Com_out_dp,Con_f_in_dp,TC_C_module,TC_C_CP);
		ForCond_Expa = Tunnel(forecast_Con_f_out_P[0],forecast_Exp_in_P[0],Con_f_out_dp,Exp_in_dp,TC_E_module,TC_E_CP);
		ForExpa_Evap = Tunnel(forecast_Exp_out_P[0],forecast_Eva_f_in_P[0],Exp_out_dp,Eva_f_in_dp,TE_E_module,TE_E_CP);
		ForEvap_Comp = Tunnel(forecast_Eva_f_out_P[0],forecast_Com_in_P[0],Eva_f_out_dp,Com_in_dp,TE_C_module,TE_C_CP);
//故障预判
		ForEvap.faultdetection();
		ForCond.faultdetection();
		ForExpa.faultdetection();
		ForComp.faultdetection();
		ForComp_Cond.faultdetection();
		ForCond_Expa.faultdetection();
		ForExpa_Evap.faultdetection();
		ForEvap_Comp.faultdetection();
		ForEvap.runStateinfo();
		ForCond.runStateinfo();
		ForExpa.runStateinfo();
		ForComp.runStateinfo();
		ForComp_Cond.runStateinfo();
		ForCond_Expa.runStateinfo();
		ForExpa_Evap.runStateinfo();
		ForEvap_Comp.runStateinfo();
		
		if (ForEvap.getStateinfo() == 0 && ForCond.getStateinfo() == 0 && ForExpa.getStateinfo() == 0 && ForComp.getStateinfo() == 0 && ForComp_Cond.getStateinfo() == 0 && ForCond_Expa.getStateinfo() == 0 && ForExpa_Evap.getStateinfo() == 0 && ForEvap_Comp.getStateinfo() == 0)
		{
			forecaststate = 0;//表示已经进行故障预判计算且没有故障
			cout << "预测运行状态正常！" << endl;
		}
		else 
			forecaststate = 1;//表示已经进行故障预判计算且发生故障
		ForEvap.outputstateinfo();
		ForCond.outputstateinfo();
		ForExpa.outputstateinfo();
		ForComp.outputstateinfo();
		ForComp_Cond.outputstateinfo();
		ForCond_Expa.outputstateinfo();
		ForExpa_Evap.outputstateinfo();
		ForEvap_Comp.outputstateinfo();
	}
	else 
	{
		forecaststate = -1;//表示没有进行故障预判计算
		cout << "预测运行状态未检测" << endl;
		cout << "当前数据量：" << norfilerow << endl;
	}
	ofstream fout;
	fout.open("accuracy.txt");

	if (fout.fail())
	{
		cout << "Opening file accuracy.txt failed!" << endl;
		exit(1);
	}

	fout << forecast_Eva_f_in_T[1] << ' ';
	fout << forecast_Eva_f_out_T[1] << ' ';
	fout << forecast_Eva_f_in_P[1] << ' ';
	fout << forecast_Eva_f_out_P[1] << ' ';
	fout << forecast_Eva_w_in_T[1] << ' ';
	fout << forecast_Eva_w_out_T[1] << ' ';
	fout << forecast_Con_f_in_T[1] << ' ';
	fout << forecast_Con_f_out_T[1] << ' ';
	fout << forecast_Con_f_in_P[1] << ' ';
	fout << forecast_Con_f_out_P[1] << ' ';
	fout << forecast_Con_w_in_T[1] << ' ';
	fout << forecast_Con_w_out_T[1] << ' ';
	fout << forecast_Exp_in_P[1] << ' ';
	fout << forecast_Exp_out_P[1] << ' ';
	fout << forecast_Exp_in_T[1] << ' ';
	fout << forecast_Exp_out_T[1] << ' ';
	fout << forecast_Com_in_P[1] << ' ';
	fout << forecast_Com_out_P[1] << ' ';
	fout << forecast_Com_in_T[1] << ' ';
	fout << forecast_Com_out_T[1] << ' ';
	fout << forecast_Com_W[1];

	fout.close();
}

void HVAC::Run()
{
	struct tm *oldtime;
	struct tm *newtime;
	int oldh,oldm,newh,newm,olds,news;
	time_t long_time;
	time (&long_time);
	oldtime = localtime(&long_time);
	oldh = oldtime->tm_hour;
	oldm = oldtime->tm_min;
	olds = oldtime->tm_sec;
//	do
//	{
		time (&long_time);
		newtime = localtime(&long_time);
		newh = newtime->tm_hour;
		newm = newtime->tm_min;
		news = newtime->tm_sec;
//		if ((newm == oldm && news > olds) || newm != oldm)
//		{
			this->Standard();
			cout << "**************************" << endl;
			this->NowState();
			cout << "**************************" << endl;
			this->PutData();
			olds = news;
//		}
//		if (newh == oldh && newm - oldm >= 1)
//		{
			oldh = newh;
			oldm = newm;
			this->ForecastState();
//		}
		if (newh - oldh == 1 && newm + 60 - oldm >= 1)
		{
			oldh = newh;
			oldm = newm;
			this->ForecastState();
		}
		if (newh < oldh && newm + 60 - oldm >= 1)
		{
			oldh = newh;
			oldm = newm;
			this->ForecastState();
		}
		this->OutputInfo();
		this->OupputData();
		cout << oldh << ':' << oldm << ':' << olds << endl;
		cout << newh << ':' << newm << ':' << news << endl;
//	}while (true);
}

void HVAC::PutData()
{
	double value[21];

	if (this->nowstate == 0)
	{
		value[0] = this->Now_Eva_f_in_T;
		value[1] = this->Now_Eva_f_out_T;
		value[2] = this->Now_Eva_f_in_P;
		value[3] = this->Now_Eva_f_out_P;
		value[4] = this->Now_Eva_w_in_T;
		value[5] = this->Now_Eva_w_out_T;
		value[6] = this->Now_Con_f_in_T;
		value[7] = this->Now_Con_f_out_T;
		value[8] = this->Now_Con_f_in_P;
		value[9] = this->Now_Con_f_out_P;
		value[10] = this->Now_Con_w_in_T;
		value[11] = this->Now_Con_w_out_T;
		value[12] = this->Now_Exp_in_P;
		value[13] = this->Now_Exp_out_P;
		value[14] = this->Now_Exp_in_T;
		value[15] = this->Now_Exp_out_T;
		value[16] = this->Now_Com_in_P;
		value[17] = this->Now_Com_out_P;
		value[18] = this->Now_Com_in_T;
		value[19] = this->Now_Com_out_T;
		value[20] = this->Now_Com_W;
		WriteFile(value,fileright);
	}
}

void HVAC::OutputInfo()
{
	ofstream fout;
	fout.open("stateinfo.txt");
	if (fout.fail())
	{
		cout << "Output file stateinfo.txt opening failed!" << endl;
		exit(1);
	}

	fout << this->NowEvap.getdCP1() << ' ';
	fout << this->NowEvap.getdCP2() << ' ';
	fout << this->NowEvap.getModule() << ' ';
	fout << this->NowEvap.getDegree() << ' ';
	fout << this->NowEvap.getStateinfo() << ' ';
	fout << this->ForEvap.getdCP1() << ' ';
	fout << this->ForEvap.getdCP2() << ' ';
	fout << this->ForEvap.getModule() << ' ';
	fout << this->ForEvap.getDegree() << ' ';
	fout << this->ForEvap.getStateinfo() << ' ';
	fout << this->NowCond.getdCP1() << ' ';
	fout << this->NowCond.getdCP2() << ' ';
	fout << this->NowCond.getModule() << ' ';
	fout << this->NowCond.getDegree() << ' ';
	fout << this->NowCond.getStateinfo() << ' ';
	fout << this->ForCond.getdCP1() << ' ';
	fout << this->ForCond.getdCP2() << ' ';
	fout << this->ForCond.getModule() << ' ';
	fout << this->ForCond.getDegree() << ' ';
	fout << this->ForCond.getStateinfo() << ' ';
	fout << this->NowExpa.getdCP() << ' ';
	fout << this->NowExpa.getModule() << ' ';
	fout << this->NowExpa.getDegree() << ' ';
	fout << this->NowExpa.getStateinfo() << ' ';
	fout << this->ForExpa.getdCP() << ' ';
	fout << this->ForExpa.getModule() << ' ';
	fout << this->ForExpa.getDegree() << ' ';
	fout << this->ForExpa.getStateinfo() << ' ';
	fout << this->NowComp.getdCP() << ' ';
	fout << this->NowComp.getModule() << ' ';
	fout << this->NowComp.getDegree() << ' ';
	fout << this->NowComp.getStateinfo() << ' ';
	fout << this->ForComp.getdCP() << ' ';
	fout << this->ForComp.getModule() << ' ';
	fout << this->ForComp.getDegree() << ' ';
	fout << this->ForComp.getStateinfo() << ' ';
	fout << this->NowComp_Cond.getDegree() << ' ';
	fout << this->NowCond_Expa.getDegree() << ' ';
	fout << this->NowExpa_Evap.getDegree() << ' ';
	fout << this->NowEvap_Comp.getDegree() << ' ';
	fout << this->ForComp_Cond.getDegree() << ' ';
	fout << this->ForCond_Expa.getDegree() << ' ';
	fout << this->ForExpa_Evap.getDegree() << ' ';
	fout << this->ForEvap_Comp.getDegree() << ' ';
	fout << this->nowstate << ' ';
	fout << this->forecaststate << ' ';
	fout << this->step;

	fout.close();
}

void HVAC::OupputData()
{
	ofstream fout;
	fout.open("datainfo.txt");
	if (fout.fail())
	{
		cout << "Output file datainfo.txt opening failed!" << endl;
		exit(1);
	}

	fout << this->ForEvap.getfluorinTin() << ' ';
	fout << this->ForEvap.getfluorinTout() << ' ';
	fout << this->ForEvap.getwaterTin() << ' ';
	fout << this->ForEvap.getwaterTout() << ' ';
	fout << this->ForEvap.getPin() << ' ';
	fout << this->ForEvap.getPout() << ' ';
	fout << this->ForCond.getfluorinTin() << ' ';
	fout << this->ForCond.getfluorinTout() << ' ';
	fout << this->ForCond.getwaterTin() << ' ';
	fout << this->ForCond.getwaterTout() << ' ';
	fout << this->ForCond.getPin() << ' ';
	fout << this->ForCond.getPout() << ' ';
	fout << this->ForExpa.getTin() << ' ';
	fout << this->ForExpa.getTout() << ' ';
	fout << this->ForExpa.getPin() << ' ';
	fout << this->ForExpa.getPout() << ' ';
	fout << this->ForComp.getTin() << ' ';
	fout << this->ForComp.getTout() << ' ';
	fout << this->ForComp.getPin() << ' ';
	fout << this->ForComp.getPout();

	fout.close();
}