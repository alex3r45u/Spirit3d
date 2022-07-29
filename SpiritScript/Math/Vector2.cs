using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SpiritScript.Math
{
    public struct Vector2
    {
        public float X;
        public float Y;

        public Vector2(float value)
        {
            X = Y = value;
        }
        public Vector2(float x, float y)
        {
            this.X = x; this.Y = y;
        }

        public void Clamp(Vector2 min, Vector2 max)
        {
            if (X < min.X)
                X = min.X;
            if (X > max.X)
                X = max.X;

            if (Y < min.Y)
                Y = min.Y;
            if (Y > max.Y)
                Y = max.Y;
        }
        public static Vector2 operator -(Vector2 vector)
        {
            return new Vector2(-vector.X, -vector.Y);
        }
    }

    
}
