

using SharpDX;

namespace CGRender.Core
{
    public struct Face
    {
        public int A;
        public int B;
        public int C;
        public MaterialType MaterialType;
        public Color4 Color;
        public Vector3 Normal;
        public int AllPixels;
        public int DrawedPixels;

    }
}