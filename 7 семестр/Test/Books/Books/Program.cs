using BenchmarkDotNet.Running;
using Books.Benchmark;

namespace db_cp
{
    public class Program
    {
        public static void Main(string[] args)
        { 
			//_ = BenchmarkRunner.Run<BenchmarkMs>();

			//_ = BenchmarkRunner.Run<BenchmarkPostgres>();

			using var server = new Prometheus.KestrelMetricServer(port: 5000);
			server.Start();

			CreateHostBuilder(args).Build().Run();
		}

		public static IHostBuilder CreateHostBuilder(string[] args) =>
            Host.CreateDefaultBuilder(args)
                .ConfigureWebHostDefaults(webBuilder =>
                {
                    webBuilder.UseStartup<Startup>();
                });
    }
}