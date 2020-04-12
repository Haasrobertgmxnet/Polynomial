using System;
using System.Text.RegularExpressions;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;

namespace Polynomial.Wpf
{
    /// <summary>
    /// Interaktionslogik für MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        Process p = new Process();

        public MainWindow()
        {
            InitializeComponent();

            txtBox1.Text = string.Empty;
        }

        private void OnPreviewTextInput(object sender, TextCompositionEventArgs e)
        {
            Regex regex = new Regex(@"(-?)(\d+)((.|,)?)(\d+)");
            e.Handled = !regex.IsMatch(e.Text);
        }

        private void NumberValidationTextBox(object sender, TextCompositionEventArgs e)
        {
            //Regex regex = new Regex(@"(-?)(\d+)((.|,)?)(\d+)");
            //Regex regex = new Regex("(-?)([0-9]+)((.|,)?)([0-9]+)");
            Regex regex = new Regex(@"^-?\d*\.{0,1}\d+$");
            var bl= regex.IsMatch(e.Text);
            e.Handled = !regex.IsMatch(e.Text);
            //foreach (char charItem in e.Text)
            //{
            //    e.Handled = !(Char.IsNumber(charItem) || 
            //        charItem.Equals('-') || 
            //        charItem.Equals('.') || 
            //        charItem.Equals(',') ||
            //        charItem.Equals('E') ||
            //        charItem.Equals('e'));
            //}
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            string s = txtBox2.Text;
            
            p.Do();
            MessageBox.Show(s + p.InString + p.OutString);
        }
    }
}
