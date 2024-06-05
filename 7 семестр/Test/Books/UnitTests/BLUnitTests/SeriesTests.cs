using Xunit;
using Allure.Xunit.Attributes;
using Books.Interfaces;
using Books.Models;
using Books.Services;
using Moq;
using UnitTests.DataBuilder;
using UnitTests.ObjectMother;

namespace UnitTests.BLUnitTests
{
	[TestCaseOrderer(
		ordererTypeName: "UnitTests.Order.RandomOrder",
		ordererAssemblyName: "UnitTests")]
	[AllureSuite("SeriesServiceSuite")]
	public class SeriesTests
	{
		private List<Series> _mockList;
		private readonly ISeriesService _service;

		public SeriesTests()
		{
			var series = new SeriesObjectMother().Series_1();
			series.Id = 1;

			_mockList = new List<Series>
			{
				series
			};

			var mockRepo = new Mock<ISeriesRepository>();

			mockRepo.Setup(repo => repo.Add(It.IsAny<Series>())).Callback(
				(Series x) =>
				{
					x.Id = _mockList.Count + 1;
					_mockList.Add(x);
				}
			);

			mockRepo.Setup(repo => repo.Update(It.IsAny<Series>())).Callback<Series>(
				(Series x) =>
				{
					var existing = _mockList.FirstOrDefault(y => y.Id == x.Id);
					if (existing != null)
					{
						existing.Name = x.Name;
						existing.Genre = x.Genre;
						existing.Publisher = x.Publisher;
						existing.Year = x.Year;
						existing.Rating = x.Rating;
					}
				}
			);

			mockRepo.Setup(repo => repo.Delete(It.IsAny<int>())).Callback(
				(int id) => _mockList.RemoveAll(x => x.Id == id));

			mockRepo.Setup(repo => repo.GetAll()).Returns(_mockList);

			mockRepo.Setup(repo => repo.GetById(It.IsAny<int>())).Returns(
				(int id) => _mockList.Find(x => x.Id == id));

			mockRepo.Setup(repo => repo.GetByName(It.IsAny<string>())).Returns(
				(string name) => _mockList.Find(x => x.Name == name));

			_service = new SeriesService(mockRepo.Object);
		}

		[AllureXunit]
		public void TestAdd()
		{
			var expected = new SeriesObjectMother().Series_2();

			_service.Add(expected);

			var actual = _service.GetByName(expected.Name);

			Assert.Equal(expected.Name, actual.Name);
			Assert.Equal(expected.Genre, actual.Genre);
			Assert.Equal(expected.Publisher, actual.Publisher);
			Assert.Equal(expected.Year, actual.Year);
			Assert.Equal(expected.Rating, actual.Rating);
		}

		[AllureXunit]
		public void TestAddException()
		{
			var expected = new SeriesObjectMother().Series_1();

			var exception = Assert.Throws<Exception>(() => _service.Add(expected));

			Assert.Equal("Такая серия уже существует", exception.Message);
		}

		[AllureXunit]
		public void TestUpdate()
		{
			var expected = new SeriesObjectMother().Series_2();
			expected.Id = 1;

			_service.Update(expected);

			var actual = _service.GetByName(expected.Name);

			Assert.Equal(expected.Id, actual.Id);
			Assert.Equal(expected.Name, actual.Name);
			Assert.Equal(expected.Genre, actual.Genre);
			Assert.Equal(expected.Publisher, actual.Publisher);
			Assert.Equal(expected.Year, actual.Year);
			Assert.Equal(expected.Rating, actual.Rating);
		}

		[AllureXunit]
		public void TestUpdateException()
		{
			var expected = new SeriesObjectMother().Series_2();
			expected.Id = 2;

			var exception = Assert.Throws<Exception>(() => _service.Update(expected));

			Assert.Equal("Такой серии не существует", exception.Message);
		}

		[AllureXunitTheory]
		[InlineData(1, "name_1")]
		public void TestDelete(int _id, string _name)
		{
			var expected = new SeriesBuilder()
								.WithId(_id)
								.WithName(_name)
								.Build();

			_service.Delete(expected);

			var actual = _service.GetByName(expected.Name);

			Assert.Null(actual);
		}

		[AllureXunitTheory]
		[InlineData(2)]
		public void TestDeleteException(int _id)
		{
			var expected = new SeriesBuilder()
								.WithId(_id)
								.Build();

			var exception = Assert.Throws<Exception>(() => _service.Delete(expected));

			Assert.Equal("Такой серии не существует", exception.Message);
		}

		[AllureXunit]
		public void TestGetAll()
		{
			var actual = _service.GetAll();

			Assert.Equal(_mockList.Count(), actual.Count());
		}

		[AllureXunit]
		public void TestGetByName()
		{
			var expected = new SeriesObjectMother().Series_1();
			expected.Id = 1;

			var actual = _service.GetByName(expected.Name);

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

			var actual = _service.GetByParameters(parameters);

			Assert.Equal(expected[0].Name, actual.First().Name);
			Assert.Equal(expected[0].Genre, actual.First().Genre);
			Assert.Equal(expected[0].Publisher, actual.First().Publisher);
			Assert.Equal(expected[0].Year, actual.First().Year);
			Assert.Equal(expected[0].Rating, actual.First().Rating);
		}
	}
}
