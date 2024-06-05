using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Threading;
using CGRender.Core;
using CGRender.Database;
using SharpDX;
using Color = SharpDX.Color;

namespace CGRender.GameLogic
{
    public class Scene
    {
        public Camera Camera = new Camera(
            new Vector3(30, 15, 30),
            Vector3.Zero,
            new Vector3(0, 1, 0));

        public Vector3 LightPosition;
        public byte[] Buffer { get; set; }

        private readonly List<Mesh> _meshes = new List<Mesh>(20);

        private MeshType _previewMeshType = MeshType.None;

        private readonly Dictionary<MeshType, Mesh> _previewMeshes = new Dictionary<MeshType, Mesh>();

        private readonly Device _device;

        private readonly Mesh[,] _meshMatrix = new Mesh[5, 5];

        private Mesh _prevMesh;

        private MeshType _lastSelected;

        private readonly Random _rnd = new Random();
        
        private Vector3 _rotation = new Vector3(0);
        
        private List<Color> randomColors = new List<Color> { Color.Green, Color.SpringGreen, Color.Olive};

        public Scene(Device device)
        {
            _device = device;
        }

        public void CheckUiIntersection(int x, int y)
        {
            var intersectMesh = _device.CheckMouseIntersection(x, y);

            if (_prevMesh != null)
            {
                for (var i = 0; i < _prevMesh.Faces.Length; i++)
                {
                    switch (_prevMesh.MeshType)
                    {
                        case MeshType.Ground:
                            _prevMesh.Faces[i].Color = Color.LimeGreen;
                            break;
                        case MeshType.Water:
                            _prevMesh.Faces[i].Color = Color.Blue;
                            break;
                    }
                }
            }

            _prevMesh = intersectMesh;

            if (intersectMesh != null)
            {

                var pos = intersectMesh.MatrixPosition;
                var color = Color.Yellow;
                if (_meshMatrix[pos.X, pos.Y].MeshType != MeshType.Ground)
                {
                    color = Color.Red;
                    if (_previewMeshType != MeshType.None)
                    {
                        _lastSelected = _previewMeshType;
                        var mesh = _previewMeshes[_previewMeshType];
                        _meshes.Remove(mesh);
                        _previewMeshType = MeshType.None;
                    }
                }

                if (_meshMatrix[pos.X, pos.Y].MeshType == MeshType.Ground && _previewMeshType == MeshType.Water)
                    color = Color.LightBlue;

                for (var i = 0; i < intersectMesh.Faces.Length; i++)
                {
                    intersectMesh.Faces[i].Color = color;
                }

                if (_previewMeshType != MeshType.None)
                {
                    var mesh = _previewMeshes[_previewMeshType];
                    mesh.Position = new Vector3(intersectMesh.Position.X, 1.0f, intersectMesh.Position.Z);
                    mesh.Rotation = _rotation;
                    _lastSelected = MeshType.None;
                    if (!_meshes.Contains(mesh))
                    {
                        var indx = _rnd.Next(randomColors.Count);
                        for (int i = 0; i < mesh.Faces.Length; i++)
                        {
                            if (mesh.Faces[i].MaterialType == MaterialType.Leaf)
                                mesh.Faces[i].Color = randomColors[indx];
                        }

                        _meshes.Add(mesh);
                    }
                }

                if (_previewMeshType == MeshType.None && _lastSelected != MeshType.None)
                    SelectItem(_lastSelected);
            }
            else
            {
                if (_previewMeshType == MeshType.None)
                    return;
                var mesh = _previewMeshes[_previewMeshType];
                _meshes.Remove(mesh);
            }

        }

        public void SelectItem(MeshType type)
        {
             if (_previewMeshType != MeshType.None)
             {
                 var mesh = _previewMeshes[_previewMeshType];
                 _meshes.Remove(mesh);
            
             }
            if (type == _previewMeshType)
            {
                var mesh = _previewMeshes[_previewMeshType];
                _meshes.Remove(mesh);
                _previewMeshType = MeshType.None;
            }
            else
                _previewMeshType = type;
        }

        public void TryPlaceMesh(int x, int y)
        {
            if (_prevMesh == null)
                return;

            if (_previewMeshType == MeshType.None)
                return;

            var pos = _prevMesh.MatrixPosition;


            if (_meshMatrix[pos.X, pos.Y].MeshType != MeshType.Ground) return;

            if (_previewMeshType == MeshType.Water)
            {
                for (var i = 0; i < _prevMesh.Faces.Length; i++)
                {
                    _prevMesh.Faces[i].Color = Color.Blue;
                }

                _meshMatrix[pos.X, pos.Y].MeshType = MeshType.Water;
                return;
            }

            var mesh = _previewMeshes[_previewMeshType];
            var t = mesh.CloneWithPosition(mesh.Position);
            t.Rotation = mesh.Rotation; //new Vector3(0, rnd.NextFloat((float)-Math.PI, (float)Math.PI), 0);
            _meshMatrix[pos.X, pos.Y] = t;
            t.Placed = true;
            _meshes.Add(t);

            _rotation = new Vector3(0, _rnd.NextFloat((float)-Math.PI, (float)Math.PI), 0);
        }


        public void CreateBaseScene()
        {
            var ground = Loader.MyLoading(@"Assets/ground");

            for (var i = -2; i <= 2; i++)
            {
                for (var j = -2; j <= 2; j++)
                {
                    var p = ground.CloneWithPosition(new Vector3(i * 2f, 0, j * 2f));
                    p.MeshType = MeshType.Ground;
                    p.Placed = true;
                    p.MatrixPosition = new Point(i + 2, j + 2);
                    _meshMatrix[i + 2, j + 2] = p;


                    for (var u = 0; u < p.Faces.Length; u++)
                        p.Faces[u].Color = Color.LimeGreen;

                    _meshes.Add(p);
                }
            }

            AddPreview(Loader.MyLoading(@"Assets/leaf"), MeshType.LeafTree);
            AddPreview(Loader.MyLoading(@"Assets/bush"), MeshType.Bush);
            AddPreview(Loader.MyLoading(@"Assets/spruce"), MeshType.SpruceTree);
            AddPreview(new Mesh("water", 0, 0), MeshType.Water);
        }

        public void AddPreview(Mesh mesh, MeshType type)
        {
            mesh.MeshType = type;
            mesh.Placed = false;

            _previewMeshes.Add(type, mesh);
        }

        private float Angle = -70f;
        private readonly float _radius = 50;
        private readonly float Y = 0;

        public Vector3 MoveAround()
        {
            return new Vector3(Y, (float)(_radius * Math.Cos(MathUtil.DegreesToRadians(Angle))),
                (float)(_radius * Math.Sin(MathUtil.DegreesToRadians(Angle))));
        }

        private float _step = 0.5f;

        private int count = 0;
        public void Render()
        {
            Stopwatch stopwatch = new Stopwatch();
            stopwatch.Start();

            Angle += _step;

            if (Angle == 0)
                Angle = 0.1f;

            if (Angle >= 89)
            {
                Angle = 89;
                count++;
            }
            if (count == 20)
            {
                count = 0;
                Angle = -89;
            }

            //LightPosition = new Vector3(30);
            LightPosition = MoveAround();


            _device.Clear(240, 240, 240, 255);
            var position = Camera.Position;

            Camera.Position = LightPosition;

            //_device.Render(Camera.Position, Camera.ViewMatrix(), Matrix.OrthoOffCenterLH(-20, 20, -20, 20, -10, 20), _meshes, LightPosition, Color4.Lerp(Color.Red, Color.Blue, Angle / 360), true);
            _device.Render(Camera.Position, Camera.ViewMatrix(), Matrix.PerspectiveFovLH(0.78f, 1, 0.1f, 1.0f), _meshes, LightPosition, Color4.Lerp(Color.Red, Color.Blue, Angle / 360), true);
            
            //_device.Render(Camera.Position, Camera.ViewMatrix(), Matrix.OrthoOffCenterLH(-20, 20, -20, 20, -10, 20), _meshes, LightPosition,
            //    Color4.Lerp(Color.Red, Color.Blue, Angle / 360), true);

            _device.ClearAfterShadow(240, 240, 240, 255);
            
            Camera.Position = position;
            Buffer = _device.Render(Camera.Position, Camera.ViewMatrix(), Matrix.PerspectiveFovLH(0.78f,
                1,
                0.1f, 1.0f), _meshes, LightPosition, Color4.Lerp(Color.White, Color.Blue, Math.Abs(Angle) / 70), false);
            
            stopwatch.Stop();
            Console.Write(stopwatch.ElapsedTicks);
        }
    }
}