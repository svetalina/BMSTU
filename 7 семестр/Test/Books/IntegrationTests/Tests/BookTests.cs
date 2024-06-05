using Xunit;
using Allure.Xunit.Attributes;
using Books.Models;
using Books.Interfaces;
using Books.Services;
using Books.Repository;
using IntegrationTests.ObjectMother;
using IntegrationTests.DataBuilder;

namespace IntegrationTests
{
	[TestCaseOrderer(
		ordererTypeName: "IntegrationTests.Order.RandomOrder",
		ordererAssemblyName: "IntegrationTests")]
	[AllureSuite("BookIntegrationSuite")]
	public class BookTests
	{
		AppDbContext _dbContext;
		IBookRepository _bookRepository;
		IBookService _bookService;

		public BookTests()
		{
			_dbContext = new DbContext().GetDbContext();
			_bookRepository = new BookRepository(_dbContext);
			_bookService = new BookService(_bookRepository);
		}

		[AllureXunit]
		public void TestAdd()
		{
			var transaction = _dbContext.Database.BeginTransaction();

			var expected = new BookObjectMother().Book_2();

			_bookService.Add(expected);

			var actual = _bookService.GetByName(expected.Name);

			Assert.Equal(expected.Name, actual.Name);
			Assert.Equal(expected.Genre, actual.Genre);
			Assert.Equal(expected.Language, actual.Language);
			Assert.Equal(expected.Year, actual.Year);
			Assert.Equal(expected.Rating, actual.Rating);

			transaction.Rollback();
		}

		[AllureXunit]
		public void TestAddException()
		{
			var transaction = _dbContext.Database.BeginTransaction();

			var expected = new BookObjectMother().Book_1();

			var exception = Assert.Throws<Exception>(() => _bookService.Add(expected));

			Assert.Equal("Такая книга уже существует", exception.Message);

			transaction.Rollback();
		}

		[AllureXunit]
		public void TestUpdate()
		{
			var transaction = _dbContext.Database.BeginTransaction();

			var expected = new BookObjectMother().Book_2();
			expected.Id = 1;

			_bookService.Update(expected);

			var actual = _bookService.GetByName(expected.Name);

			Assert.Equal(expected.Id, actual.Id);
			Assert.Equal(expected.Name, actual.Name);
			Assert.Equal(expected.Genre, actual.Genre);
			Assert.Equal(expected.Language, actual.Language);
			Assert.Equal(expected.Year, actual.Year);
			Assert.Equal(expected.Rating, actual.Rating);

			transaction.Rollback();
		}

		[AllureXunit]
		public void TestUpdateException()
		{
			var transaction = _dbContext.Database.BeginTransaction();

			var expected = new BookObjectMother().Book_2();
			expected.Id = 3;

			var exception = Assert.Throws<Exception>(() => _bookService.Update(expected));

			Assert.Equal("Такой книги не существует", exception.Message);

			transaction.Rollback();
		}

		[AllureXunitTheory]
		[InlineData(1, "name_1")]
		public void TestDelete(int _id, string _name)
		{
			var transaction = _dbContext.Database.BeginTransaction();

			var expected = new BookBuilder()
								.WithId(_id)
								.WithName(_name)
								.Build();

			_bookService.Delete(expected);

			var actual = _bookService.GetByName(expected.Name);

			Assert.Null(actual);

			transaction.Rollback();
		}

		[AllureXunitTheory]
		[InlineData(3)]
		public void TestDeleteException(int _id)
		{
			var transaction = _dbContext.Database.BeginTransaction();

			var expected = new BookBuilder()
								.WithId(_id)
								.Build();

			var exception = Assert.Throws<Exception>(() => _bookService.Delete(expected));

			Assert.Equal("Такой книги не существует", exception.Message);

			transaction.Rollback();
		}


		[AllureXunit]
		public void TestGetAll()
		{
			var actual = _bookService.GetAll();

			Assert.Equal(2, actual.Count());
		}


		[AllureXunit]
		public void TestGetByName()
		{
			var expected = new BookObjectMother().Book_1();
			expected.Id = 1;

			var actual = _bookService.GetByName(expected.Name);

			Assert.Equal(expected.Id, actual.Id);
			Assert.Equal(expected.Name, actual.Name);
			Assert.Equal(expected.Genre, actual.Genre);
			Assert.Equal(expected.Language, actual.Language);
			Assert.Equal(expected.Year, actual.Year);
			Assert.Equal(expected.Rating, actual.Rating);
		}

		[AllureXunitTheory]
		[InlineData("genre_1")]
		public void TestGetByParameters(string _genre)
		{

			var expected = new List<Book>
			{
				new BookObjectMother().Book_1()
			};

			var parameters = new BookBuilder()
									.WithGenre(_genre)
									.Build();

			var actual = _bookService.GetByParameters(parameters);

			Assert.Equal(expected[0].Name, actual.First().Name);
			Assert.Equal(expected[0].Genre, actual.First().Genre);
			Assert.Equal(expected[0].Language, actual.First().Language);
			Assert.Equal(expected[0].Year, actual.First().Year);
			Assert.Equal(expected[0].Rating, actual.First().Rating);
		}
	}
}
