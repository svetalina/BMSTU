using System;
using System.Collections.Generic;
using System.Runtime.Intrinsics;
using SharpDX;
using Matrix = SharpDX.Matrix;
using Vector3 = SharpDX.Vector3;

namespace CGRender.Core
{
    public class Device
    {
        private byte[] _backBuffer;

        private float[] _depthBuffer;
        
        public ShadowInfo[] ShadowFaces;
        
        private Mesh[] _objectBuffer;
        
        public int _renderWidth;
        
        public int _renderHeight;
        
        private Mesh _currentMesh;
        
        private List<Mesh> _meshes;
        
        private int _currentFaceIndex;
        
        private bool _shadowFlag;

        public Device(int w, int h)
        {
            _renderWidth = w;
            _renderHeight = h;

            _backBuffer = new byte[_renderWidth * _renderHeight * 4];
            _depthBuffer = new float[_renderWidth * _renderHeight];
            _objectBuffer = new Mesh[_renderWidth * _renderHeight];

            ShadowFaces = new ShadowInfo[_renderWidth * _renderHeight];
            for (int i = 0; i < _renderWidth * _renderHeight; i++)
                ShadowFaces[i] = new ShadowInfo();
        }

        public void Resize(int newWidth, int newHeight)
        {
            if (newWidth <= _renderWidth && newHeight <= _renderHeight)
            {
                _renderWidth = newWidth;
                _renderHeight = newHeight;
                return;
            }

            _renderWidth = newWidth;
            _renderHeight = newHeight;

            _backBuffer = new byte[_renderWidth * _renderHeight * 4];
            _depthBuffer = new float[_renderWidth * _renderHeight];
            _objectBuffer = new Mesh[_renderWidth * _renderHeight];

            ShadowFaces = new ShadowInfo[_renderWidth * _renderHeight];
            for (int i = 0; i < _renderWidth * _renderHeight; i++)
                ShadowFaces[i] = new ShadowInfo();
        }

        public void Clear(byte r, byte g, byte b, byte a)
        {
            for (int index = 0, i = 0; index < _backBuffer.Length; index += 4, i++)
            {
                _backBuffer[index] = b;
                _backBuffer[index + 1] = g;
                _backBuffer[index + 2] = r;
                _backBuffer[index + 3] = a;

                _depthBuffer[i] = float.MaxValue;

                _objectBuffer[i] = null;

                ShadowFaces[i].FaceIndex = int.MinValue;
                ShadowFaces[i].Mesh = null;
            }

            if (_meshes == null)
                return;

            foreach (var mesh in _meshes)
            {
                for (int i = 0; i < mesh.Faces.Length; i++)
                {
                    mesh.Faces[i].AllPixels = 0;
                    mesh.Faces[i].DrawedPixels = 0;
                }
            }

        }

        public void ClearAfterShadow(byte r, byte g, byte b, byte a)
        {
            for (int index = 0, i = 0; index < _backBuffer.Length; index += 4, i++)
            {
                _backBuffer[index] = b;
                _backBuffer[index + 1] = g;
                _backBuffer[index + 2] = r;
                _backBuffer[index + 3] = a;

                _depthBuffer[i] = float.MaxValue;

                _objectBuffer[i] = null;
            }
        }


        private Color4 _wtfColor;


        public byte[] Render(Vector3 cameraPos, Matrix viewMatrix, Matrix projectionMatrix, List<Mesh> meshes, Vector3 lightPosition, Color4 wtfColor, bool shadowFlag)
        {
            _shadowFlag = shadowFlag;

            _wtfColor = wtfColor;
            _meshes = meshes;

            foreach (Mesh mesh in _meshes)
            {
                _currentMesh = mesh;
                var worldMatrix = Matrix.RotationYawPitchRoll(mesh.Rotation.Y,
                                      mesh.Rotation.X, mesh.Rotation.Z) *
                                  Matrix.Scaling(mesh.Scale) *
                                  Matrix.Translation(mesh.Position);

                var transformMatrix = worldMatrix * viewMatrix * projectionMatrix;

                for (int i = 0; i < mesh.Faces.Length; i++)
                {
                    var face = mesh.Faces[i];
                    // if (shadowFlag)
                    // {
                    //     face.AllPixels = 0;
                    //     face.DrawedPixels = 0;
                    //
                    // }
                    _currentFaceIndex = i;

                    var vertexA = mesh.Vertices[face.A];
                    var vertexB = mesh.Vertices[face.B];
                    var vertexC = mesh.Vertices[face.C];



                    var pixelA = Project(vertexA, transformMatrix, worldMatrix);
                    var pixelB = Project(vertexB, transformMatrix, worldMatrix);
                    var pixelC = Project(vertexC, transformMatrix, worldMatrix);

                    var normal = (pixelA.Normal + pixelB.Normal + pixelC.Normal) / 3;

                    DrawTriangle(pixelA, pixelB, pixelC, face.Color,
                        Vector3.TransformNormal(face.Normal, 
                            Matrix.RotationYawPitchRoll(mesh.Rotation.Y,
                            mesh.Rotation.X, mesh.Rotation.Z)) , lightPosition, cameraPos);

                }
            }

            return _backBuffer;
        }

        public void PutPixel(int x, int y, float z, Color4 color)
        {
            var index = (x + y * _renderWidth);
            var index4 = index * 4;

            if (_depthBuffer[index] < z)
                return;

            if (_currentMesh.MeshType is MeshType.Ground or MeshType.Water)
                _objectBuffer[index] = _currentMesh;

            _depthBuffer[index] = z;

            if (_shadowFlag)
            {
                if (ShadowFaces[index].FaceIndex >= 0)
                    ShadowFaces[index].Mesh.Faces[ShadowFaces[index].FaceIndex].DrawedPixels -= 1;

                _currentMesh.Faces[_currentFaceIndex].AllPixels += 1;
                _currentMesh.Faces[_currentFaceIndex].DrawedPixels += 1;
                ShadowFaces[index].FaceIndex = _currentFaceIndex;
                ShadowFaces[index].Mesh = _currentMesh;
            }
            else
            {
                _backBuffer[index4 + 0] = (byte)(color.Blue * 255);
                _backBuffer[index4 + 1] = (byte)(color.Green * 255);
                _backBuffer[index4 + 2] = (byte)(color.Red * 255);
                _backBuffer[index4 + 3] = (byte)(color.Alpha * 255);
            }
        }

        public Mesh CheckMouseIntersection(int x, int y)
        {
            var index = (x + y * _renderWidth);

            return _objectBuffer[index];
        }

        public Vertex Project(Vertex vertex, Matrix transMat, Matrix world)
        {
            var point2d = Vector3.TransformCoordinate(vertex.Coordinates, transMat);
            var point3dWorld = Vector3.TransformCoordinate(vertex.Coordinates, world);
            var normal3dWorld = Vector3.TransformCoordinate(vertex.Normal, world);

            var x = point2d.X * _renderWidth + _renderWidth / 2.0f;
            var y = -point2d.Y * _renderHeight + _renderHeight / 2.0f;

            return new Vertex
            {
                Coordinates = new Vector3(x, y, point2d.Z),
                Normal = normal3dWorld,
                WorldCoordinates = point3dWorld
            };
        }

        float Clamp(float value, float min = 0, float max = 1) => Math.Max(min, Math.Min(value, max));

        float Interpolate(float min, float max, float gradient) => min + (max - min) * Clamp(gradient);

        float ComputeNDotL(Vector3 normal, Vector3 lightPosition)
        {
            var lightDirection = lightPosition;

            normal.Normalize();
            lightDirection.Normalize();

            return Vector3.Dot(normal, lightDirection);
        }

        void ProcessScanLine(ScanLineData data, Vertex va, Vertex vb, Vertex vc, Vertex vd, Color4 color)
        {
            Vector3 pa = va.Coordinates;
            Vector3 pb = vb.Coordinates;
            Vector3 pc = vc.Coordinates;
            Vector3 pd = vd.Coordinates;


            var gradient1 = Math.Abs(pa.Y - pb.Y) > float.Epsilon ? (data.CurrentY - pa.Y) / (pb.Y - pa.Y) : 1;
            var gradient2 = Math.Abs(pc.Y - pd.Y) > float.Epsilon ? (data.CurrentY - pc.Y) / (pd.Y - pc.Y) : 1;

            int sx = (int)Interpolate(pa.X, pb.X, gradient1);
            int ex = (int)Interpolate(pc.X, pd.X, gradient2);

            var z1 = Interpolate(pa.Z, pb.Z, gradient1);
            var z2 = Interpolate(pc.Z, pd.Z, gradient2);

            var face = _currentMesh.Faces[_currentFaceIndex];
            float u = 0;
            if (face.AllPixels != 0)
            {
                u = (float)face.DrawedPixels / face.AllPixels;
            }

            if (u > 0.3)
                u = 1;

            var c = Color4.Lerp(Color.Black, 
                Color4.Lerp(Color4.Lerp(_wtfColor, Color.AdjustContrast(Color.White, data.Ndotla / 2 + 0.5f), 0.4f), color, 0.5f), u / 5 + 0.8f);
           // var c = Color4.Lerp(Color.Black, Color.White, u);
            c.Alpha = color.Alpha;

            for (var x = sx; x < ex; x++)
            {
                float gradient = (x - sx) / (float)(ex - sx);

                var z = Interpolate(z1, z2, gradient);

                //var c = Color4.Lerp(Color4.Lerp(_wtfColor, Color4.White, data.ndotla / 6 + 0.6f), color, 0.5f);
                //var face = _currentMesh.Faces[currentFaceIndex];
                //float u = 0;
                //if (face.AllPixels != 0)
                //{
                //    u = face.DrawedPixels / (float)face.AllPixels;
                //}
                //var c = Color4.Lerp(Color.Black, Color4.Lerp(
                //    Color4.Lerp(_wtfColor, 
                //        Color.AdjustContrast(Color.White, data.ndotla / 2 + 0.5f), 0.4f),  color, 0.5f), u / 4 + 0.75f);

                ////c.Alpha = color.Alpha;
                //c.Alpha = color.Alpha;
                DrawPoint(new Vector3(x, data.CurrentY, z), c);
            }
        }

        float Cross2D(float x0, float y0, float x1, float y1) => x0 * y1 - x1 * y0;

        float LineSide2D(Vector3 p, Vector3 lineFrom, Vector3 lineTo) => Cross2D(p.X - lineFrom.X, p.Y - lineFrom.Y, lineTo.X - lineFrom.X, lineTo.Y - lineFrom.Y);

        public void DrawTriangle(Vertex v1, Vertex v2, Vertex v3, Color4 color, Vector3 vnFace, Vector3 lightPos, Vector3 cameraPos)
        {
            if (v1.Coordinates.Y > v2.Coordinates.Y)
                (v2, v1) = (v1, v2);

            if (v2.Coordinates.Y > v3.Coordinates.Y)
                (v2, v3) = (v3, v2);

            if (v1.Coordinates.Y > v2.Coordinates.Y)
                (v2, v1) = (v1, v2);

            Vector3 p1 = v1.Coordinates;
            Vector3 p2 = v2.Coordinates;
            Vector3 p3 = v3.Coordinates;
            
            //Vector3 centerPoint = (v1.WorldCoordinates + v2.WorldCoordinates + v3.WorldCoordinates) / 3;
            // Vector3 centerPoint = Vector3.Zero;
            //Vector3 lightPos = new Vector3(5000, 10000, 50000);
            float ndotl = ComputeNDotL(vnFace, lightPos);

            float cameraNDotL = ComputeNDotL(vnFace, cameraPos);

            if (cameraNDotL < 0)
                return;


            var data = new ScanLineData { Ndotla = ndotl };

            if (LineSide2D(p2, p1, p3) > 0)
            {
                for (var y = (int)p1.Y; y <= (int)p3.Y; y++)
                {
                    data.CurrentY = y;

                    if (y < p2.Y)
                        ProcessScanLine(data, v1, v3, v1, v2, color);
                    else
                        ProcessScanLine(data, v1, v3, v2, v3, color);
                }
            }
            else
            {
                for (var y = (int)p1.Y; y <= (int)p3.Y; y++)
                {
                    data.CurrentY = y;

                    if (y < p2.Y)
                        ProcessScanLine(data, v1, v2, v1, v3, color);
                    else
                        ProcessScanLine(data, v2, v3, v1, v3, color);
                }
            }
        }

        public void DrawPoint(Vector3 point, Color4 color)
        {
            if (point.X >= 0 && point.Y >= 0 && point.X < _renderWidth && point.Y < _renderHeight)
                PutPixel((int)point.X, (int)point.Y, point.Z, color);
        }
    }
}