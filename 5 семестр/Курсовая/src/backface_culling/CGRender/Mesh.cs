using SharpDX;

namespace CGRender.Core
{
    public class Mesh
    {
        public string Name { get; set; }
        public MeshType MeshType { get; set; }

        public Point MatrixPosition { get; set; }

        public bool Placed { get; set; }
        public Vertex[] Vertices { get; set; }
        public Face[] Faces { get; set; }
        public Vector3 Position { get; set; }
        public Vector3 Rotation { get; set; }

        public Vector3 Scale { get; set; }

        private Mesh()
        {
        }

        public Mesh(string name, int verticesCount, int facesCount)
        {
            Vertices = new Vertex[verticesCount];
            Faces = new Face[facesCount];
            Name = name;
        }

        public Mesh CloneWithPosition(Vector3 newPosition)
        {
            return new Mesh
            {
                Name = Name,
                MeshType = MeshType,
                Placed = Placed,
                Vertices = (Vertex[]) Vertices.Clone(),
                Faces = (Face[]) Faces.Clone(),
                Rotation = Rotation,
                Position = newPosition,
                Scale = Scale,
            };
        }
    }
}