using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SpiritScript
{
    public class Texture2d
    {
        public string Path { get; private set; }

        public Texture2d(string path)
        {
            Path = path;
        }
    }
}
