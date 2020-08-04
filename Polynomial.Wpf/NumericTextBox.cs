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
                var hasMoreThanOneMinusSign = false;
                var hasMoreThanOneDecimalSign = false;
                foreach (char charItem in e.Text)
                {
                    hasMoreThanOneMinusSign = e.Text == "-" && tBox.Text.Contains("-");
                    hasMoreThanOneDecimalSign = (",.").Contains(e.Text) && (tBox.Text.Contains(",") || tBox.Text.Contains("."));
                    var textBoxContentIsValid = Double.TryParse(tBox.Text, out double res);
                    textBoxContentIsValid = textBoxContentIsValid || (".").Contains(tBox.Text) || (",").Contains(tBox.Text) || ("-").Contains(tBox.Text);
                    textBoxContentIsValid = textBoxContentIsValid || ("-.").Contains(tBox.Text) || ("-,").Contains(tBox.Text);
                    var newCharacterIsValid = true;
                    newCharacterIsValid = newCharacterIsValid && textBoxContentIsValid;
                    newCharacterIsValid = newCharacterIsValid && ("0123456789,.-").Contains(e.Text);
                    e.Handled = !newCharacterIsValid || hasMoreThanOneMinusSign || hasMoreThanOneDecimalSign;
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
