using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;
using CGRender.Core;
using SharpDX;

namespace CGRender.Database
{
    public static class Loader
    {
       
        private static Vector3 ReadVector3(string[] data)
        {
            return new Vector3
            {
                X = float.Parse(data[1], CultureInfo.InvariantCulture.NumberFormat),
                Y = float.Parse(data[2], CultureInfo.InvariantCulture.NumberFormat),
                Z = float.Parse(data[3], CultureInfo.InvariantCulture.NumberFormat),
            };
        }

        private static List<Material> ReadMaterials(string filename)
        {
            string[] lines = File.ReadAllLines(filename + ".mtl");

            var materials = new List<Material>();

            foreach (string s in lines)
            {
                var data = s.Split();

                switch (data[0])
                {
                    case "newmtl":
                        materials.Add(new Material
                        {
                            Name = data[1]
                        });
                        break;
                    case "Kd":
                        materials.Last().Color = new Color4(ReadVector3(data), 1);
                        break;
                }
            }

            return materials;
        }


        public static Mesh MyLoading(string filename)
        {
            string[] lines = File.ReadAllLines(filename + ".obj");

            var materials = ReadMaterials(filename);

            string name = String.Empty;

            var vertices = new List<Vertex>();

            var normals = new List<Vector3>();

            var faces = new List<Face>();

            Material currentMaterial = null;

            foreach (string s in lines)
            {
                var data = s.Split();

                switch (data[0])
                {
                    case "o":
                        name = data[1];
                        break;
                    case "v":
                        vertices.Add(new Vertex
                        {
                            Coordinates = ReadVector3(data)
                        });
                        break;
                    case "vn":
                        normals.Add(ReadVector3(data));
                        break;
                    case "usemtl":
                        currentMaterial = materials.First(e => e.Name == data[1]);
                        break;
                        
                    case "f":
                        var face = new Face();

                        var v1 = data[1].Split('/');
                        var v2 = data[2].Split('/');
                        var v3 = data[3].Split('/');

                        face.A = int.Parse(v1[0]) - 1;
                        face.B = int.Parse(v2[0]) - 1;
                        face.C = int.Parse(v3[0]) - 1;

                        face.Normal = (normals[int.Parse(v1[2]) - 1] + normals[int.Parse(v2[2]) - 1] + normals[int.Parse(v3[2]) - 1]) / 3;

                        if (currentMaterial.Name == "Material.001" && (filename == "Assets/leaf" || filename == "Assets/bush"))
                        {
                            face.MaterialType = MaterialType.Leaf;
                        }
                        else
                        {
                            face.MaterialType = MaterialType.None;
                        }


                        face.Color = currentMaterial.Color;

                        faces.Add(face);
                        break;
                }
            }

            var mesh = new Mesh(name, vertices.Count, faces.Count);

            mesh.Vertices = vertices.ToArray();
            mesh.Faces = faces.ToArray();

            mesh.Scale = Vector3.One;

            return mesh;
        }
    }
}