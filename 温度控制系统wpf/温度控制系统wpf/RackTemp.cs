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
         public readdata(string[] args)
        {
            string oldValue = string.Empty, newValue = string.Empty;
            using (StreamReader read = new StreamReader(@"C:\Users\jack\Source\Repos\IDCSYS\温度控制系统wpf\温度控制系统wpf\bin\Debug\data.txt", true))
            {
                do
                {
                    newValue = read.ReadLine();
                    oldValue = newValue != null ? newValue : oldValue;
                } while (newValue != null);
            }
            //Console.WriteLine(oldValue);
            //string[] temp = new string[30];
            double[] tempdata = new double[30];
            string[] temp = oldValue.Split(new char[2] { ' ',','});
            for (int i = 2; i < 30; i++)
            {
                while (temp[i] != null);
                {
                    tempdata[i] = Convert.ToDouble(temp[i]);
                }
            }
           // double temp = Convert.ToDouble(oldValue);
           // double tempdata = Double.

        }
    }
    class RackTemp
    {
        public int[,] rackt = new int[5,4];
        public RackTemp()
        {
            Random r = new Random();
             for (int i = 0;i< 5;i++)
             {
                 for (int j = 0;j <4;j++)
                 {
                     rackt[i,j] = r.Next(20,30);
                 }
             }
        }


    }
}
