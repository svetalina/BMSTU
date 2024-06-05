using Allure.Xunit.Attributes;
using Books.Interfaces;
using Books.Models;
using Books.Services;
using Moq;
using UnitTests.ObjectMother;
using Xunit;

namespace UnitTests.BLUnitTests
{
	[TestCaseOrderer(
		ordererTypeName: "UnitTests.Order.RandomOrder",
		ordererAssemblyName: "UnitTests")]
	[AllureSuite("BookshelfServiceSuite")]
	public class BookshelfTests
	{
		private List<Bookshelf> _mockBookshelfList;
		private List<BookshelfBook> _mockBookshelfBookList;
		private List<Book> _mockBookList;
		private readonly IBookshelfService _service;

		public BookshelfTests()
		{
			var bookshelf = new BookshelfObjectMother().Bookshelf_1();
			bookshelf.Id = 1;

			_mockBookshelfList = new List<Bookshelf>
				{
					bookshelf
				};

			var bookshelfBook = new BookshelfObjectMother().BookshelfBook_1();

			_mockBookshelfBookList = new List<BookshelfBook>
				{
					bookshelfBook
				};

			var book = new BookObjectMother().Book_1();
			book.Id = 1;

			_mockBookList = new List<Book>
				{
					book
				};

			var mockRepo = new Mock<IBookshelfRepository>();

			mockRepo.Setup(repo => repo.AddBook(It.IsAny<BookshelfBook>())).Callback(
			   (BookshelfBook x) =>
			   {
				   _mockBookshelfBookList.Add(x);
			   }
			   );

			mockRepo.Setup(repo => repo.UpdateBook(It.IsAny<BookshelfBook>())).Callback<BookshelfBook>(
				(BookshelfBook x) =>
				{
					var existing = _mockBookshelfBookList.FirstOrDefault(
						y => y.IdBookshelf == x.IdBookshelf && y.IdBook == x.IdBook);

					if (existing != null)
					{
						existing.IsRead = x.IsRead;
					}
				}
				);

			mockRepo.Setup(repo => repo.DeleteBook(It.IsAny<BookshelfBook>())).Callback(
			   (BookshelfBook x) => _mockBookshelfBookList.RemoveAll(
				   y => y.IdBookshelf == x.IdBookshelf && y.IdBook == x.IdBook));

			mockRepo.Setup(repo => repo.GetByIdUser(It.IsAny<int>())).Returns(
				(int idUser) => _mockBookshelfList.Find(x => x.IdUser == idUser));

			mockRepo.Setup(repo => repo.GetBooksByIdBookshelf(It.IsAny<int>()))
			.Returns(
				(int idBookshelf) =>
					_mockBookList
					.Join(
						_mockBookshelfBookList,
						book => book.Id,
						bookshelfBook => bookshelfBook.IdBook,
						(book, bookshelfBook) => new { Book = book, BookshelfBook = bookshelfBook }
					)
					.Where(joinedData => joinedData.BookshelfBook.IdBookshelf == idBookshelf)
					.Select(joinedData => joinedData.Book)
					.ToList()
			);

			mockRepo.Setup(repo => repo.GetBookshelfBookByIds(It.IsAny<int>(), It.IsAny<int>()))
				.Returns(
					(int idBookshelf, int idBook) =>
						_mockBookshelfBookList.Find(x => x.IdBookshelf == idBookshelf &&
														 x.IdBook == idBook));

			_service = new BookshelfService(mockRepo.Object);
		}

		[AllureXunit]
		public void TestGetByIdUser()
		{
			var expected = new BookshelfObjectMother().Bookshelf_1();
			expected.Id = 1;

			var actual = _service.GetByIdUser(expected.IdUser);

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

			var actual = _service.GetBooksByIdBookshelf(_idBookshelf);

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

			var actual = _service.GetBookshelfBookByIds(expected.IdBookshelf, expected.IdBook);

			Assert.Equal(expected.IdBookshelf, actual.IdBookshelf);
			Assert.Equal(expected.IdBook, actual.IdBook);
			Assert.Equal(expected.IsRead, actual.IsRead);
		}

		[AllureXunit]
		public void TestAddBook()
		{
			var expected = new BookshelfObjectMother().BookshelfBook_2();

			_service.AddBook(expected);

			var actual = _service.GetBookshelfBookByIds(expected.IdBookshelf, expected.IdBook);

			Assert.Equal(expected.IdBookshelf, actual.IdBookshelf);
			Assert.Equal(expected.IdBook, actual.IdBook);
			Assert.Equal(expected.IsRead, actual.IsRead);
		}

		[AllureXunit]
		public void TestAddBookException()
		{
			var expected = new BookshelfObjectMother().BookshelfBook_1();

			var exception = Assert.Throws<Exception>(() => _service.AddBook(expected));

			Assert.Equal("Такая книга уже существует на книжной полке", exception.Message);
		}

		[AllureXunit]
		public void TestUpdateBook()
		{
			var expected = new BookshelfObjectMother().BookshelfBook_2();
			expected.IdBook = 1;

			_service.UpdateBook(expected);

			var actual = _service.GetBookshelfBookByIds(expected.IdBookshelf, expected.IdBook);

			Assert.Equal(expected.IdBookshelf, actual.IdBookshelf);
			Assert.Equal(expected.IdBook, actual.IdBook);
			Assert.Equal(expected.IsRead, actual.IsRead);
		}

		[AllureXunit]
		public void TestDeleteBook()
		{
			var expected = new BookshelfObjectMother().BookshelfBook_1();

			_service.DeleteBook(expected);

			var actual = _service.GetBookshelfBookByIds(expected.IdBookshelf, expected.IdBook);

			Assert.Null(actual);
		}
	}
}
