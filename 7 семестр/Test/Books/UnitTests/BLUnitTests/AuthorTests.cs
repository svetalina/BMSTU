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
	[AllureSuite("AuthorServiceSuite")]
	public class AuthorTests
	{
		private List<Author> _mockList;
		private readonly IAuthorService _service;

		public AuthorTests()
		{
			var author = new AuthorObjectMother().Author_1();
			author.Id = 1;

			_mockList = new List<Author>
			{
				author
			};

			var mockRepo = new Mock<IAuthorRepository>();

			mockRepo.Setup(repo => repo.Add(It.IsAny<Author>())).Callback(
				(Author x) =>
				{
					x.Id = _mockList.Count + 1;
					_mockList.Add(x);
				}
			);

			mockRepo.Setup(repo => repo.Update(It.IsAny<Author>())).Callback<Author>(
				(Author x) =>
				{
					var existing = _mockList.FirstOrDefault(y => y.Id == x.Id);
					if (existing != null)
					{
						existing.Name = x.Name;
						existing.Country = x.Country;
						existing.Genre = x.Genre;
						existing.YearBirth = x.YearBirth;
						existing.YearDeath = x.YearDeath;
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

			_service = new AuthorService(mockRepo.Object);
		}

		[AllureXunit]
		public void TestAdd()
		{
			var expected = new AuthorObjectMother().Author_2();

			_service.Add(expected);

			var actual = _service.GetByName(expected.Name);

			Assert.Equal(expected.Name, actual.Name);
			Assert.Equal(expected.Country, actual.Country);
			Assert.Equal(expected.Genre, actual.Genre);
			Assert.Equal(expected.YearBirth, actual.YearBirth);
			Assert.Equal(expected.YearDeath, actual.YearDeath);
		}

		[AllureXunit]
		public void TestAddException()
		{
			var expected = new AuthorObjectMother().Author_1();

			var exception = Assert.Throws<Exception>(() => _service.Add(expected));

			Assert.Equal("Такой автор уже существует", exception.Message);
		}

		[AllureXunit]
		public void TestUpdate()
		{
			var expected = new AuthorObjectMother().Author_2();
			expected.Id = 1;

			_service.Update(expected);

			var actual = _service.GetByName(expected.Name);

			Assert.Equal(expected.Id, actual.Id);
			Assert.Equal(expected.Name, actual.Name);
			Assert.Equal(expected.Country, actual.Country);
			Assert.Equal(expected.Genre, actual.Genre);
			Assert.Equal(expected.YearBirth, actual.YearBirth);
			Assert.Equal(expected.YearDeath, actual.YearDeath);
		}

		[AllureXunit]
		public void TestUpdateException()
		{
			var expected = new AuthorObjectMother().Author_2();
			expected.Id = 2;

			var exception = Assert.Throws<Exception>(() => _service.Update(expected));

			Assert.Equal("Такого автора не существует", exception.Message);
		}

		[AllureXunitTheory]
		[InlineData(1, "name_1")]
		public void TestDelete(int _id, string _name)
		{
			var expected = new AuthorBuilder()
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
			var expected = new AuthorBuilder()
								.WithId(_id)
								.Build();

			var exception = Assert.Throws<Exception>(() => _service.Delete(expected));

			Assert.Equal("Такого автора не существует", exception.Message);
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
			var expected = new AuthorObjectMother().Author_1();
			expected.Id = 1;

			var actual = _service.GetByName(expected.Name);

			Assert.Equal(expected.Id, actual.Id);
			Assert.Equal(expected.Name, actual.Name);
			Assert.Equal(expected.Country, actual.Country);
			Assert.Equal(expected.Genre, actual.Genre);
			Assert.Equal(expected.YearBirth, actual.YearBirth);
			Assert.Equal(expected.YearDeath, actual.YearDeath);
		}

		[AllureXunitTheory]
		[InlineData("genre_1")]
		public void TestGetByParameters(string _genre)
		{
			var expected = new List<Author>
			{
				new AuthorObjectMother().Author_1()
			};

			var parameters = new AuthorBuilder()
									.WithGenre(_genre)
									.Build();

			var actual = _service.GetByParameters(parameters);

			Assert.Equal(expected[0].Name, actual.First().Name);
			Assert.Equal(expected[0].Genre, actual.First().Genre);
			Assert.Equal(expected[0].Country, actual.First().Country);
			Assert.Equal(expected[0].YearBirth, actual.First().YearBirth);
			Assert.Equal(expected[0].YearDeath, actual.First().YearDeath);
		}
	}
}
