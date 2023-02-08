using SpiritScript;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Example.assets
{
    public class Hallo : Component
    {
        public int speed;
        protected override void Update()
        {
            
            transform.Translate(SpiritScript.Math.Vector3Direction.Forward, speed);
        }

    }
}
