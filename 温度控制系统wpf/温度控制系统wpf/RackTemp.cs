using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

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
