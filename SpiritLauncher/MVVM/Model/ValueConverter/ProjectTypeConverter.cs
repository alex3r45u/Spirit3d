using SpiritLauncher.Core;
using System;
using System.Collections.Generic;
using System.Globalization;
using System.Text;
using System.Windows.Data;

namespace SpiritLauncher.MVVM.Model.ValueConverter
{
    public class ProjectTypeConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            string type = Enum.GetName(typeof(ProjectType), value);
            return $"{parameter}: {type}"; //TODO implementation
        }

        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            return null;
        }
    }
}
