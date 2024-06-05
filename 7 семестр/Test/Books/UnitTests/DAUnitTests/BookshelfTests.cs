using Allure.Xunit.Attributes;
using Books.Interfaces;
using Books.Models;
using Books.Repository;
using Microsoft.EntityFrameworkCore;
using UnitTests.DataBuilder;
using UnitTests.ObjectMother;
using Xunit;

namespace UnitTests.DAUnitTests
{
	[TestCaseOrderer(
		ordererTypeName: "UnitTests.Order.RandomOrder",
		ordererAssemblyName: "UnitTests")]
	[AllureSuite("BookshelfRepositorySuite")]
	public class BookshelfTests
	{
		AppDbContext _dbContext;
		BookshelfRepository _bookshelfRepository;

		public BookshelfTests()
		{
			_dbContext = new DbContext().GetDbContext();
			_bookshelfRepository = new BookshelfRepository(_dbContext);


			if (!_dbContext.Bookshelf.Any())
			{
				_dbContext.Database.ExecuteSqlRaw("DBCC CHECKIDENT ('Bookshelf', RESEED, 0);");
				_dbContext.Bookshelf.Add(new BookshelfObjectMother().Bookshelf_1());
				_dbContext.BookshelfBook.Add(new BookshelfObjectMother().BookshelfBook_1());
				_dbContext.SaveChanges();
			}
		}

		[AllureXunitTheory]
		[InlineData(2, 2, 2)]
		public void TestAdd(int _idUser, int _number, int _rating)
		{
			var transaction = _dbContext.Database.BeginTransaction();

			var expected = new BookshelfBuilder()
							.WithIdUser(_idUser)
							.WithNumber(_number)
							.WithRating(_rating)
							.Build();

			_bookshelfRepository.Add(expected);

			var actual = _dbContext.Bookshelf.Where(b => b.IdUser == _idUser).FirstOrDefault();

			Assert.Equal(expected.IdUser, actual.IdUser);
			Assert.Equal(expected.Number, actual.Number);
			Assert.Equal(expected.Rating, actual.Rating);

			transaction.Rollback();
		}

		[AllureXunitTheory]
		[InlineData(1, 1, 0, 0)]
		public void TestGetByIdUser(int _id, int _idUser, int _number, double _rating)
		{
			var expected = new BookshelfBuilder()
							.WithId(_id)
							.WithIdUser(_idUser)
							.WithNumber(_number)
							.WithRating(_rating)
							.Build();

			var actual = _bookshelfRepository.GetByIdUser(_idUser);

			Assert.Equal(expected.Id, actual.Id);
			Assert.Equal(expected.IdUser, actual.IdUser);
			Assert.Equal(expected.Number, actual.Number);
			Assert.Equal(expected.Rating, actual.Rating);
		}

		[AllureXunitTheory]
		[InlineData(1, 1, false)]
		public void TestGetBookshelfBookByIds(int _idBookshelf, int _idBook, bool _isRead)
		{
			var expected = new BookshelfBookBuilder()
							.WithIdBookshelf(_idBookshelf)
							.WithIdBook(_idBook)
							.WithIsRead(_isRead)
							.Build();

			var actual = _bookshelfRepository.GetBookshelfBookByIds(_idBookshelf, _idBook);

			Assert.Equal(expected.IdBookshelf, actual.IdBookshelf);
			Assert.Equal(expected.IdBook, actual.IdBook);
			Assert.Equal(expected.IsRead, actual.IsRead);
		}

		[AllureXunitTheory]
		[InlineData(1, 1, "name_1", "genre_1", "language_1", 1, 1)]
		public void TestGetBooksByIdBookshelf(int _idBookshelf,
											  int _id, string _name, string _genre,
										       string _language, int _year, double _rating)
		{
			var expected = new BookBuilder()
								.WithId(_id)
								.WithName(_name)
								.WithGenre(_genre)
								.WithLanguage(_language)
								.WithYear(_year)
								.WithRating(_rating)
								.Build();

			var actual = _bookshelfRepository.GetBooksByIdBookshelf(_idBookshelf);

			Assert.Equal(expected.Id, actual[0].Id);
			Assert.Equal(expected.Name, actual[0].Name);
			Assert.Equal(expected.Genre, actual[0].Genre);
			Assert.Equal(expected.Language, actual[0].Language);
			Assert.Equal(expected.Year, actual[0].Year);
			Assert.Equal(expected.Rating, actual[0].Rating);
		}

		[AllureXunitTheory]
		[InlineData(1, 2, true)]
		public void TestAddBook(int _idBookshelf, int _idBook, bool _isRead)
		{
			var transaction = _dbContext.Database.BeginTransaction();

			var expected = new BookshelfBookBuilder()
							.WithIdBookshelf(_idBookshelf)
							.WithIdBook(_idBook)
							.WithIsRead(_isRead)
							.Build();

			_bookshelfRepository.AddBook(expected);

			var actual = _dbContext.BookshelfBook.Where(b => b.IdBookshelf == _idBookshelf
													 && b.IdBook == _idBook).FirstOrDefault();

			Assert.Equal(expected.IdBookshelf, actual.IdBookshelf);
			Assert.Equal(expected.IdBook, actual.IdBook);
			Assert.Equal(expected.IsRead, actual.IsRead);

			transaction.Rollback();
		}

		[AllureXunitTheory]
		[InlineData(1)]
		public void TestAddBookException(int _idBookshelf)
		{
			var transaction = _dbContext.Database.BeginTransaction();

			var expected = new BookshelfBookBuilder()
							.WithIdBookshelf(_idBookshelf)
							.Build();

			var exception = Assert.Throws<Exception>(() 
							=> _bookshelfRepository.AddBook(expected));

			Assert.Equal("Ошибка при добавлении книги на книжную полку", exception.Message);

			transaction.Rollback();
		}

		[AllureXunitTheory]
		[InlineData(1, 1, true)]
		public void TestUpdateBook(int _idBookshelf, int _idBook, bool _isRead)
		{
			var transaction = _dbContext.Database.BeginTransaction();

			var expected = new BookshelfBookBuilder()
							.WithIdBookshelf(_idBookshelf)
							.WithIdBook(_idBook)
							.WithIsRead(_isRead)
							.Build();

			_bookshelfRepository.UpdateBook(expected);

			var actual = _dbContext.BookshelfBook.Where(b => b.IdBookshelf == _idBookshelf
													 && b.IdBook == _idBook).FirstOrDefault();

			Assert.Equal(expected.IdBookshelf, actual.IdBookshelf);
			Assert.Equal(expected.IdBook, actual.IdBook);
			Assert.Equal(expected.IsRead, actual.IsRead);

			transaction.Rollback();
		}

		[AllureXunitTheory]
		[InlineData(2, 2, true)]
		public void TestUpdateBookException(int _idBookshelf, int _idBook, bool _isRead)
		{
			var transaction = _dbContext.Database.BeginTransaction();

			var expected = new BookshelfBookBuilder()
							.WithIdBookshelf(_idBookshelf)
							.WithIdBook(_idBook)
							.WithIsRead(_isRead)
							.Build();

			var exception = Assert.Throws<Exception>(() => 
							_bookshelfRepository.UpdateBook(expected));

			Assert.Equal("Ошибка при обновлении книги на книжной полке", exception.Message);

			transaction.Rollback();
		}

		[AllureXunitTheory]
		[InlineData(1, 1)]
		public void TestDeleteBook(int _idBookshelf, int _idBook)
		{
			var transaction = _dbContext.Database.BeginTransaction();

			var expected = new BookshelfBookBuilder()
							.WithIdBookshelf(_idBookshelf)
							.WithIdBook(_idBook)
							.Build();

			_bookshelfRepository.DeleteBook(expected);

			var actual = _dbContext.BookshelfBook.Where(b => b.IdBookshelf == _idBookshelf
													 && b.IdBook == _idBook).FirstOrDefault();

			Assert.Null(actual);

			transaction.Rollback();
		}

		[AllureXunitTheory]
		[InlineData(0, 0)]
		public void TestDeleteBookException(int _idBookshelf, int _idBook)
		{
			var transaction = _dbContext.Database.BeginTransaction();

			var expected = new BookshelfBookBuilder()
							.WithIdBookshelf(_idBookshelf)
							.WithIdBook(_idBook)
							.Build();

			var exception = Assert.Throws<Exception>(() => 
							_bookshelfRepository.DeleteBook(expected));

			Assert.Equal("Ошибка при удалении книги с книжной полки", exception.Message);

			transaction.Rollback();
		}

	}

}
