using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SpiritScript.Math
{

    public enum Vector3Direction
    {
        Forward,
        Backward,
        Left,
        Right,
        Up,
        Down,
    }

    public struct Vector3
    {
        public float X;
        public float Y;
        public float Z;

        public Vector3(float value)
        {
            X = Y = Z = value;
        }

        public Vector3(float x, float y, float z)
        {
            X = x;
            Y = y;
            Z = z;
        }

        public Vector3(Vector2 vector)
        {
            X = vector.X;
            Y = vector.Y;
            Z = 0.0f;
        }

        public Vector2 XY
        {
            get { return new Vector2(X, Y); }
            set { X = value.X; Y = value.Y; }
        }
        public Vector2 XZ
        {
            get { return new Vector2(X, Z); }
            set { X = value.X; Z = value.Y; }
        }
        public Vector2 YZ
        {
            get { return new Vector2(Y, Z); }
            set { Y = value.X; Z = value.Y; }
        }

        public void Clamp(Vector3 min, Vector3 max)
        {
            if (X < min.X)
                X = min.X;
            if (X > max.X)
                X = max.X;

            if (Y < min.Y)
                Y = min.Y;
            if (Y > max.Y)
                Y = max.Y;

            if (Z < min.Z)
                Z = min.Z;
            if (Z > max.Z)
                Z = max.Z;
        }

        public float CalculateDistance(Vector3 target)
        {
            float distA = X - target.X;
            float distC = Y - target.Y;
            float distB = Z - target.Z;
            return (float)System.Math.Sqrt(distA * distA + distC * distC + distB * distB);
        }

        public Quaternion ToQuaternion()
        {
            // Abbreviations for the various angular functions

            double cr = System.Math.Cos(X * 0.5 * System.Math.PI / 180);
            double sr = System.Math.Sin(X * 0.5 * System.Math.PI / 180);
            double cp = System.Math.Cos(Y * 0.5 * System.Math.PI / 180);
            double sp = System.Math.Sin(Y * 0.5 * System.Math.PI / 180);
            double cy = System.Math.Cos(Z * 0.5 * System.Math.PI / 180);
            double sy = System.Math.Sin(Z * 0.5 * System.Math.PI / 180);

            Quaternion q = new Quaternion((float)(cr * cp * cy + sr * sp * sy),
                                          (float)(sr * cp * cy - cr * sp * sy),
                                          (float)(cr * sp * cy + sr * cp * sy),
                                          (float)(cr * cp * sy - sr * sp * cy));

            return q;
        }

        public static Vector3Direction Forward = Vector3Direction.Forward;
        public static Vector3Direction Backward = Vector3Direction.Backward;
        public static Vector3Direction Left = Vector3Direction.Left;
        public static Vector3Direction Right = Vector3Direction.Right;
        public static Vector3Direction Up = Vector3Direction.Up;
        public static Vector3Direction Down = Vector3Direction.Down;

        #region Operators
        public static Vector3 operator -(Vector3 vector)
        {
            return new Vector3(-vector.X, -vector.Y, -vector.Z);
        }

        public static Vector3 operator -(Vector3 vector1, Vector3 vector2)
        {
            return new Vector3(vector1.X - vector2.X, vector1.Y - vector2.Y, vector1.Z - vector2.Z);
        }

        public static Vector3 operator -(Vector3 vector1, float scalar)
        {
            return new Vector3(vector1.X - scalar, vector1.Y - scalar, vector1.Z - scalar);
        }

        public static Vector3 operator +(Vector3 vector1, Vector3 vector2)
        {
            return new Vector3(vector1.X + vector2.X, vector1.Y + vector2.Y, vector1.Z + vector2.Z);
        }

        public static Vector3 operator +(Vector3 vector1, float scalar)
        {
            return new Vector3(vector1.X + scalar, vector1.Y + scalar, vector1.Z + scalar);
        }

        public static Vector3 operator /(Vector3 vector1, Vector3 vector2)
        {
            return new Vector3(vector1.X / vector2.X, vector1.Y / vector2.Y, vector1.Z / vector2.Z);
        }

        public static Vector3 operator /(Vector3 vector1, float scalar)
        {
            return new Vector3(vector1.X / scalar, vector1.Y / scalar, vector1.Z / scalar);
        }

        public static Vector3 operator *(Vector3 vector1, Vector3 vector2)
        {
            return new Vector3(vector1.X * vector2.X, vector1.Y * vector2.Y, vector1.Z * vector2.Z);
        }

        public static Vector3 operator *(Vector3 vector1, float scalar)
        {
            return new Vector3(vector1.X * scalar, vector1.Y * scalar, vector1.Z * scalar);
        }

        #endregion
    }

}