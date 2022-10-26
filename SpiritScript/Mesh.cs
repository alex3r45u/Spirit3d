using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SpiritScript
{
    public class Mesh
    {
        public string Path { get; private set; }
        public Mesh(string path)
        {
            Path = path;
        }
    }
}
