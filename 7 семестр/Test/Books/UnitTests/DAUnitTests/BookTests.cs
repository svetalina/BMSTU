using Xunit;
using Allure.Xunit.Attributes;
using Books.Models;
using Books.Repository;
using UnitTests.DataBuilder;
using UnitTests.ObjectMother;
using Microsoft.EntityFrameworkCore;


namespace UnitTests.DAUnitTests
{
	[TestCaseOrderer(
		ordererTypeName: "UnitTests.Order.RandomOrder",
		ordererAssemblyName: "UnitTests")]
	[AllureSuite("BookRepositorySuite")]
	public class BookTests
	{
		AppDbContext _dbContext;
		BookRepository _bookRepository;

		public BookTests()
		{
			_dbContext = new DbContext().GetDbContext();
			_bookRepository = new BookRepository(_dbContext);

			if (!_dbContext.Book.Any())
			{
				_dbContext.Database.ExecuteSqlRaw("DBCC CHECKIDENT ('Book', RESEED, 0);");
				_dbContext.Book.Add(new BookObjectMother().Book_1());
				_dbContext.Book.Add(new BookObjectMother().Book_2());
				_dbContext.BookAuthor.Add(new BookObjectMother().BookAuthor_1());
				_dbContext.SaveChanges();
			}
		}

		[AllureXunit]
		public void TestGetAll()
		{
			int expected = _dbContext.Book.Count();

			int actual = _bookRepository.GetAll().Count();

			Assert.Equal(expected, actual);
		}

		[AllureXunitTheory]
		[InlineData(1, "name_1", "genre_1", "language_1", 1, 1)]
		public void TestGetById(int _id, string _name, string _genre,
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

			var actual = _bookRepository.GetById(_id);

			Assert.Equal(expected.Id, actual.Id);
			Assert.Equal(expected.Name, actual.Name);
			Assert.Equal(expected.Genre, actual.Genre);
			Assert.Equal(expected.Language, actual.Language);
			Assert.Equal(expected.Year, actual.Year);
			Assert.Equal(expected.Rating, actual.Rating);
		}

		[AllureXunitTheory]
		[InlineData("book_3", "genre_3", "language_3", 3, 3)]
		public void TestAdd(string _name, string _genre, 
							string _language, int _year, double _rating)
		{
			var transaction = _dbContext.Database.BeginTransaction();

			var expected = new BookBuilder()
								.WithName(_name)
								.WithGenre(_genre)
								.WithLanguage(_language)
								.WithYear(_year)
								.WithRating(_rating)
								.Build();

			_bookRepository.Add(expected);

			var actual = _dbContext.Book.Where(b => b.Name == _name).FirstOrDefault();

			Assert.Equal(expected.Name, actual.Name);
			Assert.Equal(expected.Genre, actual.Genre);
			Assert.Equal(expected.Language, actual.Language);
			Assert.Equal(expected.Year, actual.Year);
			Assert.Equal(expected.Rating, actual.Rating);

			transaction.Rollback();
		}

		[AllureXunitTheory]
		[InlineData("book_3")]
		public void TestAddException(string _name)
		{
			var transaction = _dbContext.Database.BeginTransaction();

			var expected = new BookBuilder()
								.WithName(_name)
								.Build();

			var exception = Assert.Throws<Exception>(() => _bookRepository.Add(expected));

			Assert.Equal("Ошибка при добавлении книги", exception.Message);

			transaction.Rollback();
		}

		[AllureXunitTheory]
		[InlineData(1, "book_3", "genre_3", "language_3", 3, 3)]
		public void TestUpdate(int _id, string _name, string _genre, 
							   string _language, int _year, double _rating)
		{
			var transaction = _dbContext.Database.BeginTransaction();

			var expected = new BookBuilder()
								.WithId(_id)
								.WithName(_name)
								.WithGenre(_genre)
								.WithLanguage(_language)
								.WithYear(_year)
								.WithRating(_rating)
								.Build();

			_bookRepository.Update(expected);

			var actual = _dbContext.Book.Where(b => b.Id == _id).FirstOrDefault();

			Assert.Equal(expected.Id, actual.Id);
			Assert.Equal(expected.Name, actual.Name);
			Assert.Equal(expected.Genre, actual.Genre);
			Assert.Equal(expected.Language, actual.Language);
			Assert.Equal(expected.Year, actual.Year);
			Assert.Equal(expected.Rating, actual.Rating);

			transaction.Rollback();
		}

		[AllureXunitTheory]
		[InlineData(3, "book_3", "genre_3", "language_3", 3, 3)]
		public void TestUpdateException(int _id, string _name, string _genre, string _language, int _year, double _rating)
		{
			var transaction = _dbContext.Database.BeginTransaction();

			var expected = new BookBuilder()
								.WithId(_id)
								.WithName(_name)
								.WithGenre(_genre)
								.WithLanguage(_language)
								.WithYear(_year)
								.WithRating(_rating)
								.Build();

			var exception = Assert.Throws<Exception>(() => _bookRepository.Update(expected));

			Assert.Equal("Ошибка при обновлении книги", exception.Message);

			transaction.Rollback();
		}

		[AllureXunitTheory]
		[InlineData(1)]
		public void TestDelete(int _id)
		{
			var transaction = _dbContext.Database.BeginTransaction();

			_bookRepository.Delete(_id);

			var actual = _dbContext.Book.Where(b => b.Id == _id).FirstOrDefault();
			Assert.Null(actual);

			transaction.Rollback();
		}

		[AllureXunitTheory]
		[InlineData(0)]
		public void TestDeleteException(int _id)
		{
			var transaction = _dbContext.Database.BeginTransaction();

			var exception = Assert.Throws<Exception>(() => _bookRepository.Delete(_id));

			Assert.Equal("Ошибка при удалении книги", exception.Message);

			transaction.Rollback();
		}

		[AllureXunitTheory]
		[InlineData(1, "name_1", "genre_1", "language_1", 1, 1)]
		public void TestGetByName(int _id, string _name, string _genre,
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

			var actual = _bookRepository.GetByName(_name);

			Assert.Equal(expected.Id, actual.Id);
			Assert.Equal(expected.Name, actual.Name);
			Assert.Equal(expected.Genre, actual.Genre);
			Assert.Equal(expected.Language, actual.Language);
			Assert.Equal(expected.Year, actual.Year);
			Assert.Equal(expected.Rating, actual.Rating);
		}

		[AllureXunitTheory]
		[InlineData(1, "name_1", "genre_1", "country_1", 1, 1)]
		public void TestGetAuthors(int _id, string _name, string _genre,
						string _country, int _yearBirth, int _yearDeath)
		{
			var actual = _bookRepository.GetAuthors(_id);

			Assert.Equal(_name, actual.First().Name);
			Assert.Equal(_genre, actual.First().Genre);
			Assert.Equal(_country, actual.First().Country);
			Assert.Equal(_yearBirth, actual.First().YearBirth);
			Assert.Equal(_yearDeath, actual.First().YearDeath);
		}
	}
}