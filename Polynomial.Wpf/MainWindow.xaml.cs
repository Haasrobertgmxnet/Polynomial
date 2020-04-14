using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text.RegularExpressions;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;

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

            //txtBox1.Text = string.Empty;

            //TextBox c = FindChild(this, "txtBox1");

        }

        private void OnPreviewTextInput(object sender, TextCompositionEventArgs e)
        {
            //Regex regex = new Regex(@"(-?)(\d+)((.|,)?)(\d+)");
            //e.Handled = !regex.IsMatch(e.Text);
        }

        private void NumberValidationTextBox(object sender, TextCompositionEventArgs e)
        {
            //Regex regex = new Regex(@"(-?)(\d+)((.|,)?)(\d+)");
            //Regex regex = new Regex("(-?)([0-9]+)((.|,)?)([0-9]+)");
            //Regex regex = new Regex(@"^-?\d*\.{0,1}\d+$");
            //var bl= regex.IsMatch(e.Text);
            //e.Handled = !regex.IsMatch(e.Text);
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

        void FillDictionary(object obj)
        {
            string s1 = "TextBox";
            string s2 = obj.GetType().Name;
            if (s1 == s2)
            {
                string key = (obj as TextBox).Name;
                if (key.IndexOf("coefficient") >= 0)
                {
                    double res;
                    Double.TryParse((obj as TextBox).Text, out res);
                    p.Coefficients[key] = res;
                }
            }
            DependencyObject dobj = obj as DependencyObject;
            if (dobj != null)
            {
                for (int i = 0; i < VisualTreeHelper.GetChildrenCount(dobj); i++)
                {
                    FillDictionary(VisualTreeHelper.GetChild(dobj, i));
                }
            }
        }

        private void ButtonCalculate_Click(object sender, RoutedEventArgs e)
        {
            FillDictionary(this.InputCoefficients);
            p.Do();
            MessageBox.Show(p.InString + p.OutString);
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            p.Do();
            MessageBox.Show(p.InString + p.OutString);
        }

        private void AppExit(string message = "Programm wird beendet")
        {
            if (message != "NoMessage")
            {
                MessageBox.Show(message, "Programm Info");
            }
            Application.Current.Shutdown();
        }

        private void ButtonExit_Click(object sender, RoutedEventArgs e)
        {
            AppExit();
        }
    }
}
