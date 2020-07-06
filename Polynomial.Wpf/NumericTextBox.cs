using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;

namespace Polynomial.Wpf
{
    public class NumericTextBox : UserControl
    {
        

        public static readonly DependencyProperty IsEnabledProperty = DependencyProperty.RegisterAttached("IsEnabled", typeof(bool), typeof(NumericTextBox), new PropertyMetadata(PropertyChanged));

        private static void PropertyChanged(DependencyObject dependencyObject, DependencyPropertyChangedEventArgs dependencyPropertyChangedEventArgs)
        {
            TextBox textBox = (TextBox)dependencyObject;
            textBox.PreviewTextInput += OnPreviewTextInput;
        }

        private static void OnPreviewTextInput(object sender, System.Windows.Input.TextCompositionEventArgs e)
        {
            var tBox = sender as TextBox;
            if (GetIsEnabled((TextBox)sender))
            {
                foreach (char charItem in e.Text)
                {
                    bool bl = true;
                    bl = bl && Double.TryParse(tBox.Text == string.Empty?"0": tBox.Text, out double res);
                    bl = bl && ("0123456789,.-").Contains(e.Text);
                    e.Handled = !bl;
                    //string s = tBox.Text + e.Text;
                    //string s = tBox.Text;// + charItem;
                    //string s = charItem + tBox.Text;
                    //e.Handled = !(Double.TryParse(s, out double res) || s == "-");
                    //e.Handled = !(Double.TryParse(s, out double res)) && s == "-";
                }
            }
        }

        public static bool GetIsEnabled(TextBox textBox)
        {
            return (bool)textBox.GetValue(IsEnabledProperty);
        }

        public static void SetIsEnabled(TextBox textBox, bool isEnabled)
        {
            textBox.SetValue(IsEnabledProperty, isEnabled);
        }
    }
}
