﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using SpiritScript;
using SpiritScript.Math;

namespace GameScripts
{
    public class Class1 : Component
    {
        public float speed;
        void Update()
        {
            transform.position = new Vector3(transform.position.X+speed, 0, 0);
        }
     
    }
}
