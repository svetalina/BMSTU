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
	[AllureSuite("SeriesRepositorySuite")]
	public class SeriesTests
	{
		AppDbContext _dbContext;
		SeriesRepository _seriesRepository;

		public SeriesTests()
		{
			_dbContext = new DbContext().GetDbContext();
			_seriesRepository = new SeriesRepository(_dbContext);

			if (!_dbContext.Series.Any())
			{
				_dbContext.Database.ExecuteSqlRaw("DBCC CHECKIDENT ('Series', RESEED, 0);");
				_dbContext.Series.Add(new SeriesObjectMother().Series_1());
				_dbContext.SaveChanges();
			}
		}

		[AllureXunit]
		public void TestGetAll()
		{
			int expected = _dbContext.Series.Count();

			int actual = _seriesRepository.GetAll().Count();

			Assert.Equal(expected, actual);
		}

		[AllureXunitTheory]
		[InlineData(1, "name_1", "genre_1", "publisher_1", 1, 1)]
		public void TestGetById(int _id, string _name, string _genre, 
								string _publisher, int _year, double _rating)
		{
			var expected = new SeriesBuilder()
							.WithId(_id)
							.WithName(_name)
							.WithGenre(_genre)
							.WithPublisher(_publisher)
							.WithYear(_year)
							.WithRating(_rating)
							.Build();

			var actual = _seriesRepository.GetById(_id);

			Assert.Equal(expected.Id, actual.Id);
			Assert.Equal(expected.Name, actual.Name);
			Assert.Equal(expected.Genre, actual.Genre);
			Assert.Equal(expected.Publisher, actual.Publisher);
			Assert.Equal(expected.Year, actual.Year);
			Assert.Equal(expected.Rating, actual.Rating);
		}

		[AllureXunitTheory]
		[InlineData("name_2", "genre_2", "publisher_2", 2, 2)]
		public void TestAdd(string _name, string _genre, 
							string _publisher, int _year, double _rating)
		{
			var transaction = _dbContext.Database.BeginTransaction();

			var expected = new SeriesBuilder()
							.WithName(_name)
							.WithGenre(_genre)
							.WithPublisher(_publisher)
							.WithYear(_year)
							.WithRating(_rating)
							.Build();

			_seriesRepository.Add(expected);

			var actual = _dbContext.Series.Where(s => s.Name == _name).FirstOrDefault();

			Assert.Equal(expected.Name, actual.Name);
			Assert.Equal(expected.Genre, actual.Genre);
			Assert.Equal(expected.Publisher, actual.Publisher);
			Assert.Equal(expected.Year, actual.Year);
			Assert.Equal(expected.Rating, actual.Rating);

			transaction.Rollback();
		}

		[AllureXunitTheory]
		[InlineData("name_2")]
		public void TestAddException(string _name)
		{
			var transaction = _dbContext.Database.BeginTransaction();

			var expected = new SeriesBuilder()
							.WithName(_name)
							.Build();

			var exception = Assert.Throws<Exception>(() => _seriesRepository.Add(expected));

			Assert.Equal("Ошибка при добавлении серии", exception.Message);

			transaction.Rollback();
		}

		[AllureXunitTheory]
		[InlineData(1, "name_2", "genre_2", "publisher_2", 2, 2)]
		public void TestUpdate(int _id, string _name, string _genre,
							   string _publisher, int _year, double _rating)
		{
			var transaction = _dbContext.Database.BeginTransaction();

			var expected = new SeriesBuilder()
							.WithId(_id)
							.WithName(_name)
							.WithGenre(_genre)
							.WithPublisher(_publisher)
							.WithYear(_year)
							.WithRating(_rating)
							.Build();

			_seriesRepository.Update(expected);

			var actual = _dbContext.Series.Where(s => s.Id == _id).FirstOrDefault();

			Assert.Equal(expected.Id, actual.Id);
			Assert.Equal(expected.Name, actual.Name);
			Assert.Equal(expected.Genre, actual.Genre);
			Assert.Equal(expected.Publisher, actual.Publisher);
			Assert.Equal(expected.Year, actual.Year);
			Assert.Equal(expected.Rating, actual.Rating);

			transaction.Rollback();
		}

		[AllureXunitTheory]
		[InlineData(2, "name_2", "genre_2", "publisher_2", 2, 2)]
		public void TestUpdateException(int _id, string _name, string _genre, 
										string _publisher, int _year, double _rating)
		{
			var transaction = _dbContext.Database.BeginTransaction();

			var expected = new SeriesBuilder()
							.WithId(_id)
							.WithName(_name)
							.WithGenre(_genre)
							.WithPublisher(_publisher)
							.WithYear(_year)
							.WithRating(_rating)
							.Build();

			var exception = Assert.Throws<Exception>(() => _seriesRepository.Update(expected));

			Assert.Equal("Ошибка при обновлении серии", exception.Message);

			transaction.Rollback();
		}

		[AllureXunitTheory]
		[InlineData(1)]
		public void TestDelete(int _id)
		{
			var transaction = _dbContext.Database.BeginTransaction();

			_seriesRepository.Delete(_id);

			var actual = _dbContext.Series.Where(s => s.Id == _id).FirstOrDefault();
			Assert.Null(actual);

			transaction.Rollback();
		}

		[AllureXunitTheory]
		[InlineData(0)]
		public void TestDeleteException(int _id)
		{
			var transaction = _dbContext.Database.BeginTransaction();

			var exception = Assert.Throws<Exception>(() => _seriesRepository.Delete(_id));

			Assert.Equal("Ошибка при удалении серии", exception.Message);

			transaction.Rollback();
		}

		[AllureXunitTheory]
		[InlineData(1, "name_1", "genre_1", "publisher_1", 1, 1)]
		public void TestGetByName(int _id, string _name, string _genre, 
								  string _publisher, int _year, double _rating)
		{
			var expected = new SeriesBuilder()
							.WithId(_id)
							.WithName(_name)
							.WithGenre(_genre)
							.WithPublisher(_publisher)
							.WithYear(_year)
							.WithRating(_rating)
							.Build();

			var actual = _seriesRepository.GetByName(_name);

			Assert.Equal(expected.Id, actual.Id);
			Assert.Equal(expected.Name, actual.Name);
			Assert.Equal(expected.Genre, actual.Genre);
			Assert.Equal(expected.Publisher, actual.Publisher);
			Assert.Equal(expected.Year, actual.Year);
			Assert.Equal(expected.Rating, actual.Rating);
		}
	}
}
