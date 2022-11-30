using System;
using System.Collections.Generic;
using System.Text;

namespace SpiritLauncher.Core
{
    public class Project
    {
        public string Name { get; set; }
        public DateTime LastLaunchedDate { get; set; }
        public ProjectType Type { get; set; }
        public string Path { get; set; }
    }
}
