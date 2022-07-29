using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.CompilerServices;
using SpiritScript.Math;

namespace SpiritScript
{
    public abstract class Component
    {
        public Transform transform
        {
            get { return entity.GetComponent<Transform>(); }
        }

        public uint entityID
        {
            get;
            private set;
        }

        public Entity entity
        {
            get { return Entity.Get(entityID); }
        }

        protected virtual void Start() { }
        protected virtual void Update() { }
       
    }
    public class Tag : Component
    {
        public string tag
        {
            get => GetTag_Native(entity.ID);

            set => SetTag_Native(entity.ID, value);
        }
        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern string GetTag_Native(uint entityID);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void SetTag_Native(uint entityID, string value);
    }

    public class Transform : Component
    {
        void Update() { }
        public Vector3 position
        {
            get
            {
                Vector3 _Result;
                GetPosition_Native(entity.ID, out _Result);
                return _Result;
            }
            set => SetPosition_Native(entity.ID, ref value);
        }

        public Vector3 rotation
        {
            get
            {
                Vector3 _Result;
                GetRotation_Native(entity.ID, out _Result);
                return _Result;
            }
            set => SetRotation_Native(entity.ID, ref value);
        }

        public Vector3 scale
        {
            get
            {
                Vector3 _Result;
                GetScale_Native(entity.ID, out _Result);
                return _Result;
            }
            set => SetScale_Native(entity.ID, ref value);
        }

        public void Translate(Vector3Direction direction, float value)
        {
            Vector3 d = new Vector3();
            switch(direction)
            {
                case Vector3Direction.Forward:
                    GetForward_Native(entity.ID, out d);
                    break;
                case Vector3Direction.Backward:
                    GetBackward_Native(entity.ID, out d);
                    break;
                case Vector3Direction.Left:
                    GetLeft_Native(entity.ID, out d);
                    break;
                case Vector3Direction.Right:
                    GetRight_Native(entity.ID, out d);
                    break;
                case Vector3Direction.Up:
                    GetUp_Native(entity.ID, out d);
                    break;
                case Vector3Direction.Down:
                    GetDown_Native(entity.ID, out d);
                    break;
            }
            position = new Vector3(position.X + d.X * value, position.Y + d.Y * value, position.Z + d.Z * value);
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void GetPosition_Native(uint entityID, out Vector3 result);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void SetPosition_Native(uint entityID, ref Vector3 result);



        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void GetRotation_Native(uint entityID, out Vector3 result);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void SetRotation_Native(uint entityID, ref Vector3 result);



        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void GetScale_Native(uint entityID, out Vector3 result);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void SetScale_Native(uint entityID, ref Vector3 result);


        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void GetForward_Native(uint entityID, out Vector3 result);


        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void GetBackward_Native(uint entityID, out Vector3 result);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void GetLeft_Native(uint entityID, out Vector3 result);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void GetRight_Native(uint entityID, out Vector3 result);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void GetUp_Native(uint entityID, out Vector3 result);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void GetDown_Native(uint entityID, out Vector3 result);




    }
    
}
