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
	[AllureSuite("SeriesIntegrationSuite")]
	public class SeriesTests
	{
		AppDbContext _dbContext;
		ISeriesRepository _seriesRepository;
		ISeriesService _seriesService;

		public SeriesTests()
		{
			_dbContext = new DbContext().GetDbContext();
			_seriesRepository = new SeriesRepository(_dbContext);
			_seriesService = new SeriesService(_seriesRepository);
		}

		[AllureXunit]
		public void TestAdd()
		{
			var transaction = _dbContext.Database.BeginTransaction();

			var expected = new SeriesObjectMother().Series_2();

			_seriesService.Add(expected);

			var actual = _seriesService.GetByName(expected.Name);

			Assert.Equal(expected.Name, actual.Name);
			Assert.Equal(expected.Genre, actual.Genre);
			Assert.Equal(expected.Publisher, actual.Publisher);
			Assert.Equal(expected.Year, actual.Year);
			Assert.Equal(expected.Rating, actual.Rating);

			transaction.Rollback();
		}

		[AllureXunit]
		public void TestAddException()
		{
			var transaction = _dbContext.Database.BeginTransaction();

			var expected = new SeriesObjectMother().Series_1();

			var exception = Assert.Throws<Exception>(() => _seriesService.Add(expected));

			Assert.Equal("Такая серия уже существует", exception.Message);
			
			transaction.Rollback();
		}

		[AllureXunit]
		public void TestUpdate()
		{
			var transaction = _dbContext.Database.BeginTransaction();

			var expected = new SeriesObjectMother().Series_2();
			expected.Id = 1;

			_seriesService.Update(expected);

			var actual = _seriesService.GetByName(expected.Name);

			Assert.Equal(expected.Id, actual.Id);
			Assert.Equal(expected.Name, actual.Name);
			Assert.Equal(expected.Genre, actual.Genre);
			Assert.Equal(expected.Publisher, actual.Publisher);
			Assert.Equal(expected.Year, actual.Year);
			Assert.Equal(expected.Rating, actual.Rating);

			transaction.Rollback();
		}

		[AllureXunit]
		public void TestUpdateException()
		{
			var transaction = _dbContext.Database.BeginTransaction();

			var expected = new SeriesObjectMother().Series_2();
			expected.Id = 2;

			var exception = Assert.Throws<Exception>(() => _seriesService.Update(expected));

			Assert.Equal("Такой серии не существует", exception.Message);

			transaction.Rollback();
		}

		[AllureXunitTheory]
		[InlineData(1, "name_1")]
		public void TestDelete(int _id, string _name)
		{
			var transaction = _dbContext.Database.BeginTransaction();

			var expected = new SeriesBuilder()
								.WithId(_id)
								.WithName(_name)
								.Build();

			_seriesService.Delete(expected);

			var actual = _seriesService.GetByName(expected.Name);

			Assert.Null(actual);

			transaction.Rollback();
		}

		[AllureXunitTheory]
		[InlineData(2)]
		public void TestDeleteException(int _id)
		{
			var transaction = _dbContext.Database.BeginTransaction();

			var expected = new SeriesBuilder()
								.WithId(_id)
								.Build();

			var exception = Assert.Throws<Exception>(() => _seriesService.Delete(expected));

			Assert.Equal("Такой серии не существует", exception.Message);

			transaction.Rollback();
		}

		[AllureXunit]
		public void TestGetAll()
		{
			var actual = _seriesService.GetAll();

			Assert.Equal(1, actual.Count());
		}

		[AllureXunit]
		public void TestGetByName()
		{
			var expected = new SeriesObjectMother().Series_1();
			expected.Id = 1;

			var actual = _seriesService.GetByName(expected.Name);

			Assert.Equal(expected.Id, actual.Id);
			Assert.Equal(expected.Name, actual.Name);
			Assert.Equal(expected.Genre, actual.Genre);
			Assert.Equal(expected.Publisher, actual.Publisher);
			Assert.Equal(expected.Year, actual.Year);
			Assert.Equal(expected.Rating, actual.Rating);
		}

		[AllureXunitTheory]
		[InlineData("genre_1")]
		public void TestGetByParameters(string _genre)
		{
			var expected = new List<Series>
			{
				new SeriesObjectMother().Series_1()
			};

			var parameters = new SeriesBuilder()
									.WithGenre(_genre)
									.Build();

			var actual = _seriesService.GetByParameters(parameters);

			Assert.Equal(expected[0].Name, actual.First().Name);
			Assert.Equal(expected[0].Genre, actual.First().Genre);
			Assert.Equal(expected[0].Publisher, actual.First().Publisher);
			Assert.Equal(expected[0].Year, actual.First().Year);
			Assert.Equal(expected[0].Rating, actual.First().Rating);
		}
	}
}
