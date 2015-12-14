using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace 温度控制系统wpf
{
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
