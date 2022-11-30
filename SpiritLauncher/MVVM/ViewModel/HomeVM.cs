using Newtonsoft.Json;
using SpiritLauncher.Core;
using SpiritLauncher.MVVM.Model;
using System;
using System.Collections.Generic;
using System.IO;
using System.Text;

namespace SpiritLauncher.MVVM.ViewModel
{
    public class HomeVM : ObservableObject
    {
        private List<ProjectControl> _projectsView;
        public List<ProjectControl> ProjectsView
        {
            get => _projectsView;
            set
            {
                _projectsView = value;
                RaisePropertyChanged();
            }
        }

        public List<ProjectControl> Projects;

        private List<Project> GetProjects ()
        {
            var l = new List<Project>();
            foreach(var project in _projectsView)
            {
                l.Add(project.Project);
            }
            return l;
        }
        public HomeVM()
        {
            Projects = new List<ProjectControl>();
            if (File.Exists(System.IO.Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.LocalApplicationData), "SpiritLauncher/Projects.json")))
            {
                List<Project> p = JsonConvert.DeserializeObject<List<Project>>(File.ReadAllText(System.IO.Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.LocalApplicationData), "SpiritLauncher/Projects.json")));
                foreach (var project in p)
                {
                    Projects.Add(new ProjectControl(project));
                }
                UpdateView();
            }
            

         

            
        }

        public void Save()
        {
            if (!Directory.Exists(System.IO.Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.LocalApplicationData), "SpiritLauncher")))
            {
                Directory.CreateDirectory(System.IO.Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.LocalApplicationData), "SpiritLauncher"));
            }

            File.WriteAllText(System.IO.Path.Combine(System.IO.Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.LocalApplicationData), "SpiritLauncher"), "Projects.json"), Serialize());

        }


        public string Serialize() => JsonConvert.SerializeObject(GetProjects(), Formatting.Indented);

        public void UpdateView()
        {
           List<ProjectControl> view = new List<ProjectControl>();
            foreach(ProjectControl c in Projects)
            {
                view.Add(c);
            }
            ProjectsView = view;
        }
    }
}
