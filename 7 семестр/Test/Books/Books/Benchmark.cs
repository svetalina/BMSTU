using BenchmarkDotNet.Attributes;
using Microsoft.EntityFrameworkCore;
using Books.Models;
using Books.Repository;
using Books.Services;
using Books.Interfaces;

namespace Books.Benchmark
{
	[RPlotExporter]
	[MemoryDiagnoser]
	[MinColumn, MaxColumn]
	//[SimpleJob(launchCount: 5, iterationCount: 5)]
	public class BenchmarkMs
	{
		string _connectionString;
		AppDbContext _dbContext;
		IBookRepository _bookRepository;
		IBookService _bookService;

		public BenchmarkMs()
		{
			_connectionString =
				"server=localhost,1433;" +
				"database=BookDatabaseTest;" +
				"User Id=sa;Password=Password2606!;" +
				"TrustServerCertificate=true;";

			_dbContext = new AppDbContext(
				new DbContextOptionsBuilder<AppDbContext>()
					.UseSqlServer(_connectionString)
					.Options);

			_bookRepository = new BookRepository(_dbContext);
			_bookService = new BookService(_bookRepository);
		}

		[Benchmark]
		public List<Book> TestGetAll()
		{
			return _bookService.GetAll().ToList();
		}

		[Benchmark]
		public Book TestGetByName()
		{
			return _bookService.GetByName("Хроники амбера");
		}
	}

	[RPlotExporter]
	[MemoryDiagnoser]
	[MinColumn, MaxColumn]
	//[SimpleJob(launchCount: 5, iterationCount: 5)]
	public class BenchmarkPostgres
	{
		string _connectionString;
		AppDbContext _dbContext;
		IBookRepository _bookRepository;
		IBookService _bookService;

		public BenchmarkPostgres()
		{
			_connectionString =
				"server=localhost,5432;" +
				"database=BookDatabaseTest;" +
				"User Id=postgres;Password=Password2606!;";

			_dbContext = new AppDbContext(
				new DbContextOptionsBuilder<AppDbContext>()
					.UseNpgsql(_connectionString)
					.Options);

			_bookRepository = new BookRepository(_dbContext);
			_bookService = new BookService(_bookRepository);
		}

		[Benchmark]
		public List<Book> TestGetAll()
		{
			return _bookService.GetAll().ToList();
		}

		[Benchmark]
		public Book TestGetByName()
		{
			return _bookService.GetByName("Хроники амбера");
		}

	}
}
