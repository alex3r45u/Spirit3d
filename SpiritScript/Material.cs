using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using SpiritScript.Math;

namespace SpiritScript
{
    public class Material
    {
        public Vector3 Albedo { get; private set; }
        public Vector3 Normal { get; private set; }
        public float Roughness { get; private set; }
        public float Metallic { get; private set; }
        public float AO { get; private set; }

        public Texture2d AlbedoMap { get; private set; }
        public Texture2d NormalMap { get; private set; }
        public Texture2d RoughnessMap { get; private set; }
        public Texture2d MetallicMap { get; private set; }
        public Texture2d AOMap { get; private set; }
    }
    public class AssetMaterial : Material
    {
        public string Path { get; private set; }

        public AssetMaterial(string path)
        {
            Path = path;
        }
    }
}
