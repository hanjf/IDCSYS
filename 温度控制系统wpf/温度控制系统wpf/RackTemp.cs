using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Text.RegularExpressions;

namespace 温度控制系统wpf
{
    class readdata
    {
        //double[] tempdata = new double[30];
         public static double readdata1(int i)
        {
            string oldValue = string.Empty, newValue = string.Empty;
            try
            {
                using (StreamReader read = new StreamReader(@"C:\Users\jack\Source\Repos\IDCSYS\温度控制系统wpf\温度控制系统wpf\bin\Debug\data.txt", true))


                {
                    do
                    {
                        newValue = read.ReadLine();
                        oldValue = newValue != null ? newValue : oldValue;
                    } while (newValue != null);
                }
            } 
            catch (Exception e)
            {
            }
            //Console.WriteLine(oldValue);
            //string[] temp = new string[30];
            //double[] tempdata = new double[30];
            double[] tempdata = new double[30];
            string[] temp = oldValue.Split(new char[1] { ','});
            for (int j = 1; j < 22; j++)
            {
                if (temp[j] != null)
                {
                     tempdata[j] = Convert.ToDouble(temp[j]);
                }
            }
            // double temp = Convert.ToDouble(oldValue);
            // double tempdata = Double.
            return tempdata[i];
        }
    }
    class RackTemp
    {
        public double [,] rackt = new double [5,4];
        public RackTemp()
        {
            //Random r = new Random();
            //readdata t = new readdata();
             for (int i = 0;i< 5;i++)
             {
                 for (int j = 0;j <4;j++)
                 {
                    //rackt[i,j] = r.Next(20,30);
                    int k = i + j + 1;
                    rackt[i, j] = readdata.readdata1(k);
                 }
             }
        }


    }
}
