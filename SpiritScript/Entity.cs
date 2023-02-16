using System;
using System.Runtime.CompilerServices;

namespace SpiritScript
{
    public class Entity
    {
        public static Entity Get(uint entityID)
        {
            Entity entity;
            GetEntity_Native(entityID, out entity);
            return entity;
        }

        public uint ID
        {
            get;
            private set;
        }

        public T AddComponent<T>() where T : Component, new()
        {
            if (HasComponent<T>())
                return null;
            AddComponent_Native(ID, typeof(T));
            return GetComponent<T>();
        }

        public bool HasComponent<T>() where T : Component, new()
        {
            bool has;
            HasComponent_Native(ID, typeof(T), out has);
            return has;
        }

        public T GetComponent<T>() where T : Component, new()
        {
             T component;
             GetComponent_Native(ID, typeof(T), out component);
            return component;
        }

        public void RemoveComponent<T>() where T : Component, new()
        {

            if (HasComponent<T>())
                RemoveComponent_Native(ID, typeof(T));
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void AddComponent_Native(uint entityID, Type t);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void RemoveComponent_Native(uint entityID, Type t);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void HasComponent_Native(uint entityID, Type t, out bool has);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void GetComponent_Native<T>(uint entityID, Type t, out T component) where T : Component;

        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void NewEntity_Native(Entity entity);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void GetEntity_Native(uint entityID, out Entity entity);


    }
}
