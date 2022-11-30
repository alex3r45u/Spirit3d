using SpiritLauncher.MVVM.ViewModel;
using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using Wpf.Ui.Controls;

namespace SpiritLauncher
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : UiWindow
    {
        public MainWindow()
        {
            new MainWindowVM();
            InitializeComponent();
        }


        private void Window_Closing(object sender, ExitEventArgs e)
        {
            if (!Directory.Exists(System.IO.Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.LocalApplicationData), "SpiritLauncher")))
            {
                Directory.CreateDirectory(System.IO.Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.LocalApplicationData), "SpiritLauncher"));
            }

            File.WriteAllText(System.IO.Path.Combine(System.IO.Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.LocalApplicationData), "SpiritLauncher"), "Projects.json"), MainWindowVM.Instance.HomeVM.Serialize());
        }

        // public object RootFrame { get; internal set; }
    }
}
