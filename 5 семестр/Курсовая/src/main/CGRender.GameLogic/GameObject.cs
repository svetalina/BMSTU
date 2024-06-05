using System;
using CGRender.Core;
using Vector3 = System.Numerics.Vector3;

namespace CGRender.GameLogic
{
    public class GameObject : ICloneable
    {
        public MeshType MeshType { get; set; }

        public Vector3 Position { get; set; }

        public Vector3 Rotation { get; set; }

        public Vector3 Scale { get; set; } = Vector3.One;

        public Mesh Mesh { get; set; }

        public GameObject(Mesh mesh, MeshType type)
        {
            Mesh = mesh;
            MeshType = type;
        }

        public object Clone()
        {
            var mesh = new GameObject(Mesh, MeshType)
            {
                Position = Position,
                Rotation = Rotation,
                Scale = Scale
            };

            return mesh;
        }
    }
}