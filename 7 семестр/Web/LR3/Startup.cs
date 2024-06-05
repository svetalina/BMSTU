using Microsoft.EntityFrameworkCore;
using Books.Models;
using Books.Repository;
using Books.Services;
using Books.Utils;
using System.Text.Json.Serialization;


namespace Books
{
	public class Startup
	{

		private IConfigurationRoot _configuration;

		public Startup(IWebHostEnvironment hostEnv)
		{
			_configuration = new ConfigurationBuilder().SetBasePath(hostEnv.ContentRootPath).AddJsonFile("dbsettings.json").Build();
		}

		public virtual void ConfigureServices(IServiceCollection services)
		{

			services.AddDbContext<AppDbContext>(options =>
				options.UseSqlServer(_configuration.GetConnectionString("DefaultConnection")),
				ServiceLifetime.Transient);

			services.AddTransient<IAuthorService, AuthorService>();
			services.AddTransient<IBookService, BookService>();
			services.AddTransient<ISeriesService, SeriesService>();
			services.AddTransient<IBookshelfService, BookshelfService>();
			services.AddTransient<IUserService, UserService>();

			services.AddTransient<IAuthorRepository, AuthorRepository>();
			services.AddTransient<IBookRepository, BookRepository>();
			services.AddTransient<ISeriesRepository, SeriesRepository>();
			services.AddTransient<IBookshelfRepository, BookshelfRepository>();
			services.AddTransient<IUserRepository, UserRepository>();


			services.AddControllers().AddJsonOptions(o =>
			{
				var enumConverter = new JsonStringEnumConverter();
				o.JsonSerializerOptions.Converters.Add(enumConverter);
			});
			services.AddEndpointsApiExplorer();

			services.AddSwaggerGen();


			services.AddAutoMapper(typeof(AutoMappingProfile));
		}

		public virtual void Configure(IApplicationBuilder app, IWebHostEnvironment env, ILoggerFactory loggerFactory)
		{
			if (env.IsDevelopment())
			{
				app.UseSwagger(c => {
					c.RouteTemplate = "/api/v1/swagger/{documentName}/swagger.json";
				});
				app.UseSwaggerUI(c => {
					c.SwaggerEndpoint("swagger/v1/swagger.json", "My API V1");
					c.RoutePrefix = "api/v1";
				});
				app.Use(async (context, next) =>
				{
					if (context.Request.Path == "/")
					{
						context.Response.Redirect("/api/v1");
						return;
					}
					await next();
				});

				app.UseDeveloperExceptionPage();
			}

			app.UseAuthentication();
			app.UseRouting();
			app.UseAuthorization();

			app.UseEndpoints(endpoints => {
				endpoints.MapControllers();
			});
		}
	}
}