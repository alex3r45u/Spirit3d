using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SpiritScript.Math
{
    public struct Quaternion
    {
        public float X;
        public float Y;
        public float Z;
        public float W;

        public Quaternion(float x, float y, float z, float w)
        {
            X = x;
            Y = y;  
            Z = z;
            W = w;
        }

        public Vector3 ToEuler()
        {
            Vector3 angles = new Vector3();

            // roll (x-axis rotation)
            double sinr_cosp = 2 * (W * X + Y * Z);
            double cosr_cosp = 1 - 2 * (X * X + Y * Y);
            angles.X = (float)System.Math.Atan2(sinr_cosp, cosr_cosp);

            // pitch (y-axis rotation)
            double sinp = System.Math.Sqrt(1 + 2 * (W * Y - X * Z));
            double cosp = System.Math.Sqrt(1 - 2 * (W * Y - X * Z));
            angles.Y = (float)(2 * System.Math.Atan2(sinp, cosp) - System.Math.PI / 2);

            // yaw (z-axis rotation)
            double siny_cosp = 2 * (W * Z + X * Y);
            double cosy_cosp = 1 - 2 * (Y * Y + Z * Z);
            angles.Z = (float)System.Math.Atan2(siny_cosp, cosy_cosp);

            return angles;
        }
    }
}
