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

        public Quaternion rotation
        {
            get
            {
                Vector3 _Result;
                GetRotation_Native(entity.ID, out _Result);
                return _Result.ToQuaternion();
            }
            set
            {
                Vector3 x = value.ToEuler();
                SetRotation_Native(entity.ID, ref x);
            }

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
    public enum CameraType
    {
        Perspective = 1,
        Orthographic = 2,
    }

    public class RenderCamera : Component
    {
        

        public bool IsMain
        {
            get
            {
                bool isMain;
                GetMain_Native(entity.ID, out isMain);
                return isMain;
            }
            set => SetMain_Native(entity.ID, value);
        }
        public CameraType Type
        {
            get
            {
                int type;
                GetType_Native(entity.ID, out type);
                return (CameraType)type;
            }
            set => SetType_Native(entity.ID, (int)value);
        }
        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void GetMain_Native(uint entityID, out bool isMain);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void SetMain_Native(uint entityID, bool isMain);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void GetType_Native(uint entityID, out int type);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void SetType_Native(uint entityID, int type);

    }

    public class MeshRenderer : Component
    {
        public Mesh Mesh
        {
            get
            {
                return new Mesh(GetPath_Native(entity.ID));
                //Material material = new Material() { AlbedoMap = true };
            }
            set => SetPath_Native(entity.ID, value.Path);
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void SetPath_Native(uint entityID, string path);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern string GetPath_Native(uint entityID);
    }

    public enum MaterialType
    {
        Asset = 1,
        Component = 2
    }

    public class MaterialRenderer : Component
    {
        public MaterialType Type
        {
            get
            {
                int type;
                GetType_Native(entity.ID, out type);
                return (MaterialType)type;
            }
            set => SetType_Native(entity.ID, (int)value);
        }

        public Material Material
        {
            get
            {
                switch(Type) {
                    case MaterialType.Asset:
                        return new AssetMaterial(GetPath_Native(entity.ID));
                    case MaterialType.Component:
                        return new ComponentMaterial(entity);
                }
                return null;
            }
            set
            {
                switch(Type)
                {
                    case MaterialType.Asset:
                        SetPath_Native(entity.ID, ((AssetMaterial)value).Path);
                        break;
                }
            }
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void GetType_Native(uint entityID, out int type);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void SetType_Native(uint entityID, int type);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern string GetPath_Native(uint entityID);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void SetPath_Native(uint entityID, string path);
    }
    
}
