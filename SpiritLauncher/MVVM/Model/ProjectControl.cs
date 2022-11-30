using SpiritLauncher.Core;
using SpiritLauncher.MVVM.ViewModel;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;

namespace SpiritLauncher.MVVM.Model
{
    public class ProjectControl : Control
    {

        public static readonly DependencyProperty LaunchProperty = DependencyProperty.Register(nameof(Launch), typeof(ICommand), typeof(ProjectControl), new UIPropertyMetadata(null));
        public ICommand Launch
        {
            get
            {
                return (ICommand)GetValue(LaunchProperty);
            }
            set
            {
                SetValue(LaunchProperty, value);
            }
        }

        public static readonly DependencyProperty DeleteProperty = DependencyProperty.Register(nameof(Delete), typeof(ICommand), typeof(ProjectControl), new UIPropertyMetadata(null));
        public ICommand Delete
        {
            get
            {
                return (ICommand)GetValue(DeleteProperty);
            }
            set
            {
                SetValue(DeleteProperty, value);
            }
        }

   

        public static readonly DependencyProperty ProjectNameProperty = DependencyProperty.Register(nameof(ProjectName), typeof(string), typeof(ProjectControl), new UIPropertyMetadata(null));
        public string ProjectName
        {
            get
            {
                return (string)GetValue(ProjectNameProperty);
            }
            set
            {
                SetValue(ProjectNameProperty, value);
            }
        }

        public static readonly DependencyProperty LastLaunchedDateProperty = DependencyProperty.Register(nameof(LastLaunchedDate), typeof(DateTime), typeof(ProjectControl), new UIPropertyMetadata(null));
        public DateTime LastLaunchedDate
        {
            get
            {
                return (DateTime)GetValue(LastLaunchedDateProperty);
            }
            set
            {
                SetValue(LastLaunchedDateProperty, value);
            }
        }

        public static readonly DependencyProperty ProjectTypeProperty = DependencyProperty.Register(nameof(ProjectType), typeof(ProjectType), typeof(ProjectControl), new UIPropertyMetadata(null));
        public ProjectType ProjectType
        {
            get
            {
                return (ProjectType)GetValue(ProjectTypeProperty);
            }
            set
            {
                SetValue(ProjectTypeProperty, value);
            }
        }

      

        static ProjectControl()
        {
            DefaultStyleKeyProperty.OverrideMetadata(typeof(ProjectControl), new FrameworkPropertyMetadata(typeof(ProjectControl)));
        }

        public Project Project { get; set; }

        public ProjectControl(Project project)
        {
            this.Project = project;
            ProjectName = project.Name;
            LastLaunchedDate = project.LastLaunchedDate;
            ProjectType = project.Type;
        

            Launch = new RelayCommand(_ =>
            {
                Process process = new Process();
                ProcessStartInfo startInfo = new ProcessStartInfo();
                startInfo.FileName = "cmd.exe";
                startInfo.Arguments = $@"/C C:\Users\ap\source\repos\Spirit3d\bin\Debug-windows-x86_64\Editor\Editor.exe {Project.Path}";

                process.StartInfo = startInfo;
                process.Start();
            });
            Delete = new RelayCommand(_ =>
            {
                MainWindowVM.Instance.HomeVM.Projects.Remove(this);
                MainWindowVM.Instance.HomeVM.UpdateView();
                MainWindowVM.Instance.HomeVM.Save();
            });
        }
    }
}
