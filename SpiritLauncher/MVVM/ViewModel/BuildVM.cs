using Microsoft.Win32;
using SpiritLauncher.Core;
using System;
using System.Collections.Generic;
using System.Text;

namespace SpiritLauncher.MVVM.ViewModel
{
    public class BuildVM : ObservableObject
    {

        private static PlatformType GetTypeOfName(string projectTypeName)
        {
            switch (projectTypeName)
            {
                case "Android":
                    return PlatformType.Android;
                case "IOS":
                    return PlatformType.IOS;
                case "Windows":
                    return PlatformType.Windows;
                case "Linux":
                    return PlatformType.Linux;
                default:
                    throw new Exception();
            }
        }
        private List<string> _platformTypes;
        public List<string> PlatformTypes
        {
            get => _platformTypes;
            set
            {
                _platformTypes = value;
                RaisePropertyChanged();
            }
        }
        private int _index = 0;
        public int Index
        {
            get => _index;
            set
            {
                _index = value;
                RaisePropertyChanged();
            }
        }

        public RelayCommand Build { get; private set; }

        public BuildVM()
        {
            PlatformTypes = new List<string>() { "Windows", "Android", "IOS", "Linux" };
            Build = new RelayCommand(_ =>
            {
                OnBuild();
            });

        }

        private void OnBuild()
        {

        }
    }
}
