using SpiritScript.Math;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace SpiritScript
{
    public abstract class Camera
    {
        public readonly Entity Entity;
        public Camera(Entity entity)
        {
            Entity = entity;
        }
        public int Width { get; set; }
        public int Height { get; set; }

        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void GetWidth_Native(uint entityID, out int width);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void SetWidth_Native(uint entityID, ref int width);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void GetHeight_Native(uint entityID, out int height);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void SetHeight_Native(uint entityID, ref int height);
    }

    public class PerspectiveCamera : Camera
    {
        public readonly float Zoom;
        public PerspectiveCamera(Entity entity, float zoom) : base(entity)
        {
            Zoom = zoom;
        }
    }

    public class OrthographicCamera : Camera
    {
        public OrthographicCamera(Entity entity) : base(entity)
        {

        }
    }
}
