using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;
using SpiritScript.Math;

namespace SpiritScript
{
    public abstract class Material
    {
        public abstract Vector3 Albedo { get; set; }
        public abstract Vector3 Normal {get; set; }
        public abstract float Roughness {get; set; }
        public abstract float Metallic {get; set; }
        public abstract float AO {get; set; }
        public abstract Texture2d AlbedoMap { get; set; }
        public abstract Texture2d NormalMap {get; set;}
        public abstract Texture2d RoughnessMap {get; set;}
        public abstract Texture2d MetallicMap {get; set;}
        public abstract Texture2d AOMap {get; set;}
    }
    public class AssetMaterial : Material
    {
        public readonly string Path;

        public AssetMaterial(string path)
        {
            Path = path;
        }

        public override Vector3 Albedo { 
            get
            {
                Vector3 result;
                GetAlbedo_Native(Path, out result);
                return result;
            }
            set => SetAlbedo_Native(Path, ref value);
        }
        public override Vector3 Normal {
            get
            {
                Vector3 result;
                GetNormal_Native(Path, out result);
                return result;
            }
            set => SetNormal_Native(Path, ref value);
        }
        public override float Roughness { 
            get
            {
                float result;
                GetRoughness_Native(Path,out result);
                return result;
            }
            set => SetRoughness_Native(Path, value);
        }
        public override float Metallic {
            get
            {
                float result;
                GetMetallic_Native(Path, out result);
                return result;
            }
            set => SetMetallic_Native(Path, value);
        }
        public override float AO {
            get
            {
                float result;
                GetAO_Native(Path, out result);
                return result;
            }
            set => SetAO_Native(Path, value);
        }
        public override Texture2d AlbedoMap { get => throw new NotImplementedException(); set => throw new NotImplementedException(); }
        public override Texture2d NormalMap { get => throw new NotImplementedException(); set => throw new NotImplementedException(); }
        public override Texture2d RoughnessMap { get => throw new NotImplementedException(); set => throw new NotImplementedException(); }
        public override Texture2d MetallicMap { get => throw new NotImplementedException(); set => throw new NotImplementedException(); }
        public override Texture2d AOMap { get => throw new NotImplementedException(); set => throw new NotImplementedException(); }

        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void GetAlbedo_Native(string path, out Vector3 albedo);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void SetAlbedo_Native(string path, ref Vector3 albedo);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void GetNormal_Native(string path, out Vector3 normal);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void SetNormal_Native(string path, ref Vector3 normal);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void GetRoughness_Native(string path, out float roughness);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void SetRoughness_Native(string path, float roughness);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void GetMetallic_Native(string path, out float metallic);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void SetMetallic_Native(string path, float metallic);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void GetAO_Native(string path, out float ao);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void SetAO_Native(string path, float ao);
        //TODO textures
    }
    public class ComponentMaterial : Material
    {
        public readonly Entity Entity;
        public ComponentMaterial(Entity entity)
        {
            Entity = entity;
        }

        public override Vector3 Albedo {
            get
            {
                Vector3 result;
                GetAlbedo_Native(Entity.ID, out result);
                return result;
            }
            set => SetAlbedo_Native(Entity.ID, ref value);
        }
        public override Vector3 Normal {
            get
            {
                Vector3 result;
                GetNormal_Native(Entity.ID, out result);
                return result;
            }
            set => SetNormal_Native(Entity.ID, ref value);
        }
        public override float Roughness {
            get
            {
                float result;
                GetRoughness_Native(Entity.ID, out result);
                return result;
            }
            set => SetRoughness_Native(Entity.ID, value);
        }
        public override float Metallic {
            get
            {
                float result;
                GetMetallic_Native(Entity.ID, out result);
                return result;
            }
            set => SetMetallic_Native(Entity.ID, value);
        }
        public override float AO {
            get
            {
                float result;
                GetAO_Native(Entity.ID, out result);
                return result;
            }
            set => SetAO_Native(Entity.ID, value);
        }
        public override Texture2d AlbedoMap { get => throw new NotImplementedException(); set => throw new NotImplementedException(); }
        public override Texture2d NormalMap { get => throw new NotImplementedException(); set => throw new NotImplementedException(); }
        public override Texture2d RoughnessMap { get => throw new NotImplementedException(); set => throw new NotImplementedException(); }
        public override Texture2d MetallicMap { get => throw new NotImplementedException(); set => throw new NotImplementedException(); }
        public override Texture2d AOMap { get => throw new NotImplementedException(); set => throw new NotImplementedException(); }

        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void GetAlbedo_Native(uint entityID, out Vector3 albedo);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void SetAlbedo_Native(uint entityID, ref Vector3 albedo);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void GetNormal_Native(uint entityID, out Vector3 normal);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void SetNormal_Native(uint entityID,  ref Vector3 normal);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void GetRoughness_Native(uint entityID, out float roughness);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void SetRoughness_Native(uint entityID, float roughness);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void GetMetallic_Native(uint entityID, out float metallic);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void SetMetallic_Native(uint entityID, float metallic);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void GetAO_Native(uint entityID, out float ao);
        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void SetAO_Native(uint entityID, float ao);
    } 
}
