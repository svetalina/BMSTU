using System;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using CGRender.Core;
using CGRender.GameLogic;

namespace CGRender.Presentation
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private readonly Scene _scene;
        
        private readonly WriteableBitmap _bmp;
        
        private Point _lastPos;
        
        private bool _pressed;
        
        const double compress = 1f;
        
        private Task renderTask;

        public MainWindow()
        {
            InitializeComponent();

            WriteableBitmap bmp = new WriteableBitmap((int)(RenderedImage.Width / compress),
                (int)(RenderedImage.Height / compress), 96, 96, PixelFormats.Bgra32, null);
            _bmp = bmp;

            var device = new Device(bmp.PixelWidth, bmp.PixelHeight);
            _scene = new Scene(device);
            _scene.CreateBaseScene();

            RenderedImage.Source = bmp;


            CompositionTarget.Rendering += CompositionTarget_Rendering;
        }

        public void Present(byte[] buffer, int width, int height)
        {
            _bmp.WritePixels(new Int32Rect(0, 0, width, height), buffer,
                width * 4, 0);
        }

        private void CompositionTarget_Rendering(object sender, EventArgs e)
        {
            if (renderTask == null || renderTask.IsCompleted)
            {
                if (renderTask != null && renderTask.IsCompleted)
                {
                    Present(_scene.Buffer, (int)_bmp.Width,
                        (int)_bmp.Height);

                }
                renderTask = Task
                    .Run(() =>
                    {
                        _scene.Render();
                    });
            }
        }

        private DateTime downTime;
        private object downSender;

        private void Image_MouseDown(object sender, MouseButtonEventArgs e)
        {
            if (e.LeftButton == MouseButtonState.Pressed)
            {
                _lastPos = e.GetPosition(this);
                _pressed = true;
                this.downSender = sender;
                this.downTime = DateTime.Now;
            }
        }

        private void Image_MouseUp(object sender, MouseButtonEventArgs e)
        {
            if (e.LeftButton != MouseButtonState.Released || sender != downSender) 
                return;

            var timeSinceDown = DateTime.Now - this.downTime;
            if (timeSinceDown.TotalMilliseconds < 500)
            {
                var pos = e.GetPosition(RenderedImage);

                renderTask.Wait();
                _scene.TryPlaceMesh((int)(pos.X / compress), (int)(pos.Y / compress));

                _scene.CheckUiIntersection(lastMousePosition.Item1, lastMousePosition.Item2);
            }

            _pressed = false;
        }

        private void Window_KeyDown(object sender, KeyEventArgs e)
        {
            renderTask.Wait();

            if (e.Key == Key.A)
                _scene.SelectItem(MeshType.LeafTree);
            else if (e.Key == Key.S)
                _scene.SelectItem(MeshType.Bush);
            else if (e.Key == Key.D)
                _scene.SelectItem(MeshType.SpruceTree);
            else if (e.Key == Key.F)
                _scene.SelectItem(MeshType.Water);

            if (_pressed) return;

            renderTask.Wait();

            _scene.CheckUiIntersection(lastMousePosition.Item1, lastMousePosition.Item2);
        }

        private (int, int) lastMousePosition;

        private void RenderedImage_OnMouseMove(object sender, MouseEventArgs e)
        {
            if (!_pressed)
            {
                renderTask.Wait();
                var pos = e.GetPosition(RenderedImage);
                lastMousePosition = ((int)(pos.X / compress), (int)(pos.Y / compress));
                _scene.CheckUiIntersection((int)(pos.X / compress), (int)(pos.Y / compress));
            }
            else
            {
                var position = e.GetPosition(this);
                var delta = _lastPos - position;

                _scene.Camera.AddAngle((float)delta.X);
                _scene.Camera.MoveAround();

                _lastPos = position;
            }
        }
    }
}