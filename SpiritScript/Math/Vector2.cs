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

        public float CalculateDistance(Vector2 target)
        {
            float distA = X - target.X;
            float distC = Y - target.Y;
            return (float)System.Math.Sqrt(distA * distA + distC * distC);
        }

        #region Operators
        public static Vector2 operator -(Vector2 vector)
        {
            return new Vector2(-vector.X, -vector.Y);
        }

        public static Vector2 operator -(Vector2 vector1, Vector2 vector2)
        {
            return new Vector2(vector1.X - vector2.X, vector1.Y - vector2.Y);
        }

        public static Vector2 operator -(Vector2 vector1, float scalar)
        {
            return new Vector2(vector1.X - scalar, vector1.Y - scalar);
        }

        public static Vector2 operator +(Vector2 vector1, Vector2 vector2)
        {
            return new Vector2(vector1.X + vector2.X, vector1.Y + vector2.Y);
        }

        public static Vector2 operator +(Vector2 vector1, float scalar)
        {
            return new Vector2(vector1.X + scalar, vector1.Y + scalar);
        }

        public static Vector2 operator /(Vector2 vector1, Vector2 vector2)
        {
            return new Vector2(vector1.X / vector2.X, vector1.Y / vector2.Y);
        }

        public static Vector2 operator /(Vector2 vector1, float scalar)
        {
            return new Vector2(vector1.X / scalar, vector1.Y / scalar);
        }

        public static Vector2 operator *(Vector2 vector1, Vector2 vector2)
        {
            return new Vector2(vector1.X * vector2.X, vector1.Y * vector2.Y);
        }

        public static Vector2 operator *(Vector2 vector1, float scalar)
        {
            return new Vector2(vector1.X * scalar, vector1.Y * scalar);
        }

        #endregion
    }
}
