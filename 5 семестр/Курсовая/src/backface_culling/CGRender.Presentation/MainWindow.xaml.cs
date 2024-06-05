using ObjLoader.Loader.Loaders;
using System;
using System.Diagnostics;
using System.IO;
using System.Numerics;
using System.Windows;
using CGRender;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using Vector = System.Numerics.Vector;

namespace CGRender.Presentation
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private static readonly int width = 400;
        private static readonly int height = 400;
        private const int depth = 255;

        private DateTime time;

        private WriteableBitmap wb = new WriteableBitmap(
            width,
            height,
            32,
            32,
            PixelFormats.Bgr32,
            null);


        private LoadResult model;

        int[] zbuffer = new int[width * height];

        public MainWindow()
        {
            InitializeComponent();
            //CompositionTarget.Rendering += Render;

            var objLoaderFactory = new ObjLoaderFactory();
            var objLoader = objLoaderFactory.Create();

            var fileStream = File.OpenRead(@"Model\head.obj");
            model = objLoader.Load(fileStream);

            for (int i = 0; i < zbuffer.Length; i++)
            {
                zbuffer[i] = Int32.MinValue;
            }

            Viewport.Source = wb;
            time = DateTime.Now;
            Render();
            Debug.Print((DateTime.Now - time).TotalSeconds.ToString());
        }

        byte[] invertColor(byte[] colorData)
        {
            return colorData;
            return new byte[]
            {
                (byte) (255 - colorData[0]), (byte) (255 - colorData[1]), (byte) (255 - colorData[2]),
                (byte) (255 - colorData[3])
            };
        }

        void SetPixel(int x, int y, byte[] colorData)
        {
            Int32Rect rect = new Int32Rect(x, y, 1, 1);
            wb.WritePixels(rect, invertColor(colorData), 4, 0);
        }

        void DrawLine(int x0, int y0, int x1, int y1, byte[] colorData)
        {
            bool steep = false;
            if (Math.Abs(x0 - x1) < Math.Abs(y0 - y1))
            {
                (x0, y0) = (y0, x0);
                (x1, y1) = (y1, x1);
                steep = true;
            }

            if (x0 > x1)
            {
                (x0, x1) = (x1, x0);
                (y0, y1) = (y1, y0);
            }

            int dx = x1 - x0;
            int dy = y1 - y0;
            int derror2 = Math.Abs(dy) * 2;
            int error2 = 0;
            int y = y0;
            for (int x = x0; x <= x1; x++)
            {
                if (steep)
                {
                    SetPixel(y, x, colorData);
                }
                else
                {
                    SetPixel(x, y, colorData);
                }

                error2 += derror2;

                if (error2 > dx)
                {
                    y += (y1 > y0 ? 1 : -1);
                    error2 -= dx * 2;
                }
            }
        }

        public static void Swap<T>(ref T val1, ref T val2) => (val1, val2) = (val2, val1);


        void Triangle(Vector3 t0, Vector3 t1, Vector3 t2, byte[] colorData)
        {
            t0 = new Vector3((int)t0.X, (int)t0.Y, (int)t0.Z);
            t1 = new Vector3((int)t1.X, (int)t1.Y, (int)t1.Z);
            t2 = new Vector3((int)t2.X, (int)t2.Y, (int)t2.Z);

            if ((int) t0.Y == (int) t1.Y && (int) t0.Y == (int) t2.Y) return;
            if (t0.Y > t1.Y) Swap(ref t0, ref t1);
            if (t0.Y > t2.Y) Swap(ref t0, ref t2);
            if (t1.Y > t2.Y) Swap(ref t1, ref t2);

            int totalHeight = (int) (t2.Y - t0.Y);
            for (int i = 0; i < totalHeight; i++)
            {
                bool secondHalf = i > t1.Y - t0.Y || (int) t1.Y == (int) t0.Y;
                int segmentHeight = (int) (secondHalf ? t2.Y - t1.Y : t1.Y - t0.Y);
                float alpha = (float) i / totalHeight;
                float beta = (i - (secondHalf ? t1.Y - t0.Y : 0)) /
                             segmentHeight; // be careful: with above conditions no division by zero here
                Vector3 a = t0 + (t2 - t0) * alpha;

                Vector3 b = secondHalf ? t1 + (t2 - t1) * beta : t0 + (t1 - t0) * beta;
                if (a.X > b.X) Swap(ref a, ref b);
                for (int j = (int) a.X; j <= b.X; j++)
                {
                    float phi = (int) b.X == (int) a.X ? 1.0f : (j - a.X) / (b.X - a.X);
                    Vector3 p = a + (b - a) * phi;
                    int idx = (int) (p.X + p.Y * width);
                    if (zbuffer[idx] < p.Z)
                    {
                        zbuffer[idx] = (int) p.Z;
                        SetPixel((int) p.X, (int) p.Y, colorData);
                    }
                }
            }
        }

        private Matrix4x4 ModelView= Matrix4x4.CreateLookAt(new Vector3(1, 1, 3), new Vector3(0, 0, 0), new Vector3(0, 1, 0));

        private Matrix4x4 viewPort = NumericExtensions.CreateViewPortMatrix(width / 8, height / 8, depth, width * 3 / 4, height * 3 / 4);

        //private Matrix4x4 Projection =  Matrix4x4.CreatePerspective(width, height, 10, 255);


        void Render()
        {
            Vector3 lightDir = new Vector3(0, 0, -1f);
            foreach (var face in model.Groups[0].Faces)
            {
                var screenCoords = new Vector3[3];
                var worldCoords = new Vector3[3];

                for (int j = 0; j < 3; j++)
                {
                    var v = model.Vertices[face[j].VertexIndex - 1];
                    screenCoords[j] = MultiplyMatrixVector(viewPort * ModelView, new Vector3(v.X, v.Y, v.Z));
                    worldCoords[j] = new Vector3(v.X, v.Y, v.Z);
                }
                
                Vector3 n = Vector3.Cross((worldCoords[2] - worldCoords[0]), (worldCoords[1] - worldCoords[0]));

                float intensity = Vector3.Dot(n, lightDir) * 60;
                if (intensity > 0)
                {
                    Triangle(screenCoords[0], screenCoords[1], screenCoords[2],
                        new byte[] {(byte) (intensity * 255), (byte) (intensity * 255), (byte) (intensity * 255), 255});
                }
            }
        }

        public Vector3 MultiplyMatrixVector(Matrix4x4 m, Vector3 v)
        {
            return new Vector3( m.M11 * v.X + m.M12 * v.Y + m.M13 * v.Z + m.M14,
                                m.M21 * v.X + m.M22 * v.Y + m.M23 * v.Z + m.M24,
                                m.M31 * v.X + m.M32 * v.Y + m.M33 * v.Z + m.M34);

        }


    }
}