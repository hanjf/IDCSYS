using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Threading;

namespace 温度控制系统wpf
{
    /// <summary>
    /// MainWindow.xaml 的交互逻辑
    /// </summary>
    public partial class MainWindow : Window
    {
        private DispatcherTimer timer = new DispatcherTimer();
        public MainWindow()
        {
            InitializeComponent();
            timer.Interval = new TimeSpan(10000000);
            timer.Tick += timer_Tick;
            timer.Start();
            binding(); 
            
        }

        void timer_Tick(object sender, EventArgs e)
        {
            binding();
        }
        void binding()
        {
            RackTemp temp = new RackTemp();
            t11.Content = temp.rackt[0,0].ToString();
            t12.Content = temp.rackt[0,1].ToString();
            t13.Content = temp.rackt[0,2].ToString();
            t14.Content = temp.rackt[0,3].ToString();
            t15.Content = temp.rackt[1,0].ToString();
            t21.Content = temp.rackt[1,1].ToString();
            t22.Content = temp.rackt[1,2].ToString();
            t23.Content = temp.rackt[1,3].ToString();
            t24.Content = temp.rackt[2,0].ToString();
            t25.Content = temp.rackt[2,1].ToString();
            t31.Content = temp.rackt[2,2].ToString();
            t32.Content = temp.rackt[2,3].ToString();
            t33.Content = temp.rackt[3,0].ToString();
            t34.Content = temp.rackt[3,1].ToString();
            t35.Content = temp.rackt[3,2].ToString();
            t41.Content = temp.rackt[3,3].ToString();
            t42.Content = temp.rackt[4,0].ToString();
            t43.Content = temp.rackt[4,1].ToString();
            t44.Content = temp.rackt[4,2].ToString();
            t45.Content = temp.rackt[4,3].ToString();

        }

        private void t11_Click(object sender, RoutedEventArgs e)
        {
           t11 tf11 = new t11();
            tf11.ShowDialog();
        }

        private void t12_Click(object sender, RoutedEventArgs e)
        {
            t11 tf12 = new t11();
            tf12.ShowDialog();
        }
       

        private void t13_Click_1(object sender, RoutedEventArgs e)
        {
            t11 tf13 = new t11();
            tf13.ShowDialog();
        }

        private void t14_Click(object sender, RoutedEventArgs e)
        {
            t11 tf14 = new t11();
            tf14.ShowDialog();
        }

        private void t15_Click(object sender, RoutedEventArgs e)
        {
            t11 tf15 = new t11();
            tf15.ShowDialog();
        }

        private void t21_Click(object sender, RoutedEventArgs e)
        {
            t11 tf21 = new t11();
            tf21.ShowDialog();
        }

        private void t22_Click(object sender, RoutedEventArgs e)
        {
            t11 tf22 = new t11();
            tf22.ShowDialog();
        }

        private void t23_Click(object sender, RoutedEventArgs e)
        {
            t11 tf23 = new t11();
            tf23.ShowDialog();
        }

        private void t24_Click(object sender, RoutedEventArgs e)
        {
            t11 tf24 = new t11();
            tf24.ShowDialog();
        }

        private void t25_Click(object sender, RoutedEventArgs e)
        {
            t11 tf25 = new t11();
            tf25.ShowDialog();
        }

        private void t31_Click(object sender, RoutedEventArgs e)
        {
            t11 tf31 = new t11();
            tf31.ShowDialog();
        }

        private void t32_Click(object sender, RoutedEventArgs e)
        {
            t11 tf32 = new t11();
            tf32.ShowDialog();
        }

        private void t33_Click(object sender, RoutedEventArgs e)
        {
            t11 tf33 = new t11();
            tf33.ShowDialog();
        }

        private void t34_Click(object sender, RoutedEventArgs e)
        {
            t11 tf34 = new t11();
            tf34.ShowDialog();
        }

        private void t35_Click(object sender, RoutedEventArgs e)
        {
            t11 tf35 = new t11();
            tf35.ShowDialog();
        }

        private void t41_Click(object sender, RoutedEventArgs e)
        {
            t11 tf41 = new t11();
            tf41.ShowDialog();
        }

        private void t42_Click(object sender, RoutedEventArgs e)
        {
            t11 tf42 = new t11();
            tf42.ShowDialog();
        }

        private void t43_Click(object sender, RoutedEventArgs e)
        {
            t11 tf43 = new t11();
            tf43.ShowDialog();
        }

        private void t44_Click(object sender, RoutedEventArgs e)
        {
            t11 tf44 = new t11();
            tf44.ShowDialog();
        }

        private void t45_Click(object sender, RoutedEventArgs e)
        {
            t11 tf45 = new t11();
            tf45.ShowDialog();
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            refrig refrig1 = new refrig();
            refrig1.ShowDialog();

        }

        private void Button_Click_1(object sender, RoutedEventArgs e)
        {
            refrig refrig2 = new refrig();
            refrig2.ShowDialog();
        }

        private void Button_Click_2(object sender, RoutedEventArgs e)
        {
            cooler cooler1 = new cooler();
            cooler1.ShowDialog();
        }

        private void Button_Click_3(object sender, RoutedEventArgs e)
        {
            ups ups1 = new ups();
            ups1.ShowDialog();
        }

    }
}
