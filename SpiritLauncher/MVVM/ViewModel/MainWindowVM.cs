using System;
using System.Collections.Generic;
using System.Text;

namespace SpiritLauncher.MVVM.ViewModel
{
    public class MainWindowVM : ObservableObject
    {
        public HomeVM HomeVM {get; private set;}
        public SettingsVM SettingsVM {get; private set;}
        public AddVM AddVM {get; private set;}
        public static MainWindowVM Instance { get; private set; }

        public MainWindowVM()
        {
            Instance = this;
            HomeVM = new HomeVM();
            AddVM = new AddVM();
            SettingsVM = new SettingsVM();
        }
    }
}
