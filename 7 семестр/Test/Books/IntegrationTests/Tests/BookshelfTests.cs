using Xunit;
using Allure.Xunit.Attributes;
using Books.Models;
using Books.Interfaces;
using Books.Services;
using IntegrationTests.ObjectMother;
using Books.Repository;

namespace IntegrationTests
{
	[TestCaseOrderer(
		ordererTypeName: "IntegrationTests.Order.RandomOrder",
		ordererAssemblyName: "IntegrationTests")]
	[AllureSuite("BookshelfIntegrationSuite")]
	public class BookshelfTests
	{
		AppDbContext _dbContext;
		IBookshelfRepository _bookshelfRepository;
		IBookshelfService _bookshelfService;

		public BookshelfTests()
		{
			_dbContext = new DbContext().GetDbContext();
			_bookshelfRepository = new BookshelfRepository(_dbContext);
			_bookshelfService = new BookshelfService(_bookshelfRepository);
		}

		[AllureXunit]
		public void TestGetByIdUser()
		{
			var expected = new BookshelfObjectMother().Bookshelf_1();
			expected.Id = 1;

			var actual = _bookshelfService.GetByIdUser(expected.IdUser);

			Assert.Equal(expected.Id, actual.Id);
			Assert.Equal(expected.IdUser, actual.IdUser);
			Assert.Equal(expected.Number, actual.Number);
			Assert.Equal(expected.Rating, actual.Rating);
		}

		[AllureXunitTheory]
		[InlineData(1)]
		public void TestGetBooksByIdBookshelf(int _idBookshelf)
		{
			var expected = new List<Book>
			{
				new BookObjectMother().Book_1()
			};

			var actual = _bookshelfService.GetBooksByIdBookshelf(_idBookshelf);

			Assert.Equal(expected[0].Name, actual.First().Name);
			Assert.Equal(expected[0].Genre, actual.First().Genre);
			Assert.Equal(expected[0].Language, actual.First().Language);
			Assert.Equal(expected[0].Year, actual.First().Year);
			Assert.Equal(expected[0].Rating, actual.First().Rating);
		}

		[AllureXunit]
		public void TestGetBookshelfBookByIds()
		{
			var expected = new BookshelfObjectMother().BookshelfBook_1();

			var actual = _bookshelfService.GetBookshelfBookByIds(expected.IdBookshelf, expected.IdBook);

			Assert.Equal(expected.IdBookshelf, actual.IdBookshelf);
			Assert.Equal(expected.IdBook, actual.IdBook);
			Assert.Equal(expected.IsRead, actual.IsRead);
		}

		[AllureXunit]
		public void TestAddBook()
		{
			var transaction = _dbContext.Database.BeginTransaction();

			var expected = new BookshelfObjectMother().BookshelfBook_2();

			_bookshelfService.AddBook(expected);

			var actual = _bookshelfService.GetBookshelfBookByIds(expected.IdBookshelf, expected.IdBook);

			Assert.Equal(expected.IdBookshelf, actual.IdBookshelf);
			Assert.Equal(expected.IdBook, actual.IdBook);
			Assert.Equal(expected.IsRead, actual.IsRead);

			transaction.Rollback();
		}

		[AllureXunit]
		public void TestAddBookException()
		{
			var expected = new BookshelfObjectMother().BookshelfBook_1();

			var exception = Assert.Throws<Exception>(() => _bookshelfService.AddBook(expected));

			Assert.Equal("Такая книга уже существует на книжной полке", exception.Message);
		}

		[AllureXunit]
		public void TestUpdateBook()
		{
			var transaction = _dbContext.Database.BeginTransaction();

			var expected = new BookshelfObjectMother().BookshelfBook_2();
			expected.IdBook = 1;

			_bookshelfService.UpdateBook(expected);

			var actual = _bookshelfService.GetBookshelfBookByIds(expected.IdBookshelf, expected.IdBook);

			Assert.Equal(expected.IdBookshelf, actual.IdBookshelf);
			Assert.Equal(expected.IdBook, actual.IdBook);
			Assert.Equal(expected.IsRead, actual.IsRead);

			transaction.Rollback();
		}

		[AllureXunit]
		public void TestDeleteBook()
		{
			var transaction = _dbContext.Database.BeginTransaction();

			var expected = new BookshelfObjectMother().BookshelfBook_1();

			_bookshelfService.DeleteBook(expected);

			var actual = _bookshelfService.GetBookshelfBookByIds(expected.IdBookshelf, expected.IdBook);

			Assert.Null(actual);

			transaction.Rollback();
		}
	}
}
