using Microsoft.Win32;
using SpiritLauncher.Core;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Text;


namespace SpiritLauncher.MVVM.ViewModel
{
    public class AddVM : ObservableObject
    {



        private static ProjectType GetTypeOfName(string projectTypeName)
        {
            switch(projectTypeName)
            {
                case "2d":
                    return ProjectType._2d;
                case "3d":
                    return ProjectType._3d;
                default:
                    throw new Exception();
            }
        }
        private List<string> _projectTypes;
        public List<string> ProjectTypes {
            get => _projectTypes;
            set
            {
                _projectTypes = value;
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


        public RelayCommand Create { get; private set; }

        public RelayCommand Directory { get; private set; }

        private string _buttonContent;
        public string ButtonContent
        {
            get => _buttonContent;
            set  {
                _buttonContent = value;
                RaisePropertyChanged();
            }
        }

        public AddVM()
        {
            ProjectTypes = new List<string>() { "3d", "2d" };
            Create = new RelayCommand(_ =>
            {
                OnCreate();
            });
            ButtonContent = "Select your directory";
            Directory = new RelayCommand(_ => {
                SaveFileDialog dialog = new SaveFileDialog();
                dialog.Filter = "SpiritProject(*.spiritproject)|*.spiritproject";
                dialog.Title = "Save Project";
                if ((bool)dialog.ShowDialog())
                {
                    ButtonContent = dialog.FileName;
                }
            });
        }


        private void OnCreate() 
        {
          //  std::filesystem::path assetPath = File::Merge2Paths(filePath.parent_path(), "assets");
            string assetPath = Path.Combine(Path.GetDirectoryName(ButtonContent), "assets").Replace("\\", "/");
            System.IO.Directory.CreateDirectory(assetPath);
            File.Copy("SpiritScript.dll", Path.Combine(Path.GetDirectoryName(ButtonContent), "SpiritScript.dll"));
            // std::filesystem::create_directory(assetPath);
            string write = $@"
workspace ""{Path.GetFileNameWithoutExtension(ButtonContent)}""
architecture ""x64""
outputdir = """"
configurations {@"{""Release"", ""Debug""}"}
project ""{Path.GetFileNameWithoutExtension(ButtonContent)}""
    kind ""SharedLib""
    language ""C#""
    files ""{assetPath}/**.cs""
    links ""{Path.GetDirectoryName(ButtonContent).Replace("\\", "")}/SpiritScript.dll""
    targetdir("""")
";
            string s = System.IO.Directory.GetCurrentDirectory();
           StreamWriter sw = new StreamWriter(Path.Combine(Path.GetDirectoryName(ButtonContent).Replace("\\", "/"), "premake5.lua"));
           sw.Write(write);
           sw.Close();

            Process process = new Process();
            ProcessStartInfo startInfo = new ProcessStartInfo();
            startInfo.WindowStyle = ProcessWindowStyle.Hidden;
            startInfo.CreateNoWindow = true;
            startInfo.FileName = "cmd.exe";
            startInfo.Arguments = $@"/C {System.IO.Directory.GetCurrentDirectory()}/vendor/bin/premake/premake5.exe --file={Path.GetDirectoryName(ButtonContent)}/premake5.lua vs2022";

            process.StartInfo = startInfo;
            process.Start();

            StreamWriter projectFile = new StreamWriter(ButtonContent);
            projectFile.WriteLine("Settings:");
            projectFile.WriteLine(" StartScene:Example.spiritscene");
            projectFile.WriteLine(" ProjectName:"+Path.GetFileNameWithoutExtension(ButtonContent));
            projectFile.Close();



            MainWindowVM.Instance.HomeVM.Projects.Add(new Model.ProjectControl(new Core.Project() { LastLaunchedDate=DateTime.Now, Name=Path.GetFileNameWithoutExtension(ButtonContent), Path=ButtonContent, Type=GetTypeOfName(ProjectTypes[Index])}));
            MainWindowVM.Instance.HomeVM.UpdateView();
            MainWindowVM.Instance.HomeVM.Save();
        }

    }
}
