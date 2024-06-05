using System;
using SharpDX;

namespace CGRender.Core
{
    public class Camera
    {
        public Vector3 Position { get; set; }

        public Vector3 Target { get; set; }

        public Vector3 Up { get; set; }
        
        public float Angle { get; private set; }

        private readonly float _radius;

        public Camera(Vector3 position, Vector3 target, Vector3 up)
        {
            _radius = (float) (position.X / (Math.Sqrt(2) / 2));
            Position = position;
            Target = target;
            Up = up;
        }
        public Matrix ViewMatrix() => Matrix.LookAtLH(Position, Target, Up);

        public void MoveAround()
        {
            Position = new Vector3((float) (_radius * Math.Cos(MathUtil.DegreesToRadians(Angle))), Position.Y, (float) (_radius * Math.Sin(MathUtil.DegreesToRadians(Angle))));
        }

        public void AddAngle(float delta)
        {
            Angle += delta;
            if (Angle < -360)
                Angle += 360;
            if (Angle > 360)
                Angle -= 360;
        }
    }
}