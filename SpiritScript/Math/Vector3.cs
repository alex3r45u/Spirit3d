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

        public static Vector3Direction Forward = Vector3Direction.Forward;
        public static Vector3Direction Backward = Vector3Direction.Backward;
        public static Vector3Direction Left = Vector3Direction.Left;
        public static Vector3Direction Right = Vector3Direction.Right;
        public static Vector3Direction Up = Vector3Direction.Up;
        public static Vector3Direction Down = Vector3Direction.Down;
    }

}