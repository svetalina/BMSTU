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
	[AllureSuite("AuthorIntegrationSuite")]
	public class AuthorTests
	{
		AppDbContext _dbContext;
		IAuthorRepository _authorRepository;
		IAuthorService _authorService;

		public AuthorTests()
		{
			_dbContext = new DbContext().GetDbContext();
			_authorRepository = new AuthorRepository(_dbContext);
			_authorService = new AuthorService(_authorRepository);
		}

		[AllureXunit]
		public void TestAdd()
		{
			var transaction = _dbContext.Database.BeginTransaction();

			var expected = new AuthorObjectMother().Author_2();

			_authorService.Add(expected);

			var actual = _authorService.GetByName(expected.Name);

			Assert.Equal(expected.Name, actual.Name);
			Assert.Equal(expected.Country, actual.Country);
			Assert.Equal(expected.Genre, actual.Genre);
			Assert.Equal(expected.YearBirth, actual.YearBirth);
			Assert.Equal(expected.YearDeath, actual.YearDeath);

			transaction.Rollback();
		}

		[AllureXunit]
		public void TestAddException()
		{
			var transaction = _dbContext.Database.BeginTransaction();

			var expected = new AuthorObjectMother().Author_1();

			var exception = Assert.Throws<Exception>(() => _authorService.Add(expected));

			Assert.Equal("Такой автор уже существует", exception.Message);

			transaction.Rollback();
		}

		[AllureXunit]
		public void TestUpdate()
		{
			var transaction = _dbContext.Database.BeginTransaction();

			var expected = new AuthorObjectMother().Author_2();
			expected.Id = 1;

			_authorService.Update(expected);

			var actual = _authorService.GetByName(expected.Name);

			Assert.Equal(expected.Id, actual.Id);
			Assert.Equal(expected.Name, actual.Name);
			Assert.Equal(expected.Country, actual.Country);
			Assert.Equal(expected.Genre, actual.Genre);
			Assert.Equal(expected.YearBirth, actual.YearBirth);
			Assert.Equal(expected.YearDeath, actual.YearDeath);

			transaction.Rollback();
		}

		[AllureXunit]
		public void TestUpdateException()
		{
			var transaction = _dbContext.Database.BeginTransaction();

			var expected = new AuthorObjectMother().Author_2();
			expected.Id = 2;

			var exception = Assert.Throws<Exception>(() => _authorService.Update(expected));

			Assert.Equal("Такого автора не существует", exception.Message);

			transaction.Rollback();
		}

		[AllureXunitTheory]
		[InlineData(1, "name_1")]
		public void TestDelete(int _id, string _name)
		{
			var transaction = _dbContext.Database.BeginTransaction();

			var expected = new AuthorBuilder()
								.WithId(_id)
								.WithName(_name)
								.Build();

			_authorService.Delete(expected);

			var actual = _authorService.GetByName(expected.Name);

			Assert.Null(actual);

			transaction.Rollback();
		}

		[AllureXunitTheory]
		[InlineData(2)]
		public void TestDeleteException(int _id)
		{
			var transaction = _dbContext.Database.BeginTransaction();

			var expected = new AuthorBuilder()
								.WithId(_id)
								.Build();

			var exception = Assert.Throws<Exception>(() => _authorService.Delete(expected));

			Assert.Equal("Такого автора не существует", exception.Message);

			transaction.Rollback();
		}

		[AllureXunit]
		public void TestGetAll()
		{
			var actual = _authorService.GetAll();

			Assert.Equal(1, actual.Count());
		}

		[AllureXunit]
		public void TestGetByName()
		{
			var expected = new AuthorObjectMother().Author_1();
			expected.Id = 1;

			var actual = _authorService.GetByName(expected.Name);

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

			var actual = _authorService.GetByParameters(parameters);

			Assert.Equal(expected[0].Name, actual.First().Name);
			Assert.Equal(expected[0].Genre, actual.First().Genre);
			Assert.Equal(expected[0].Country, actual.First().Country);
			Assert.Equal(expected[0].YearBirth, actual.First().YearBirth);
			Assert.Equal(expected[0].YearDeath, actual.First().YearDeath);
		}
	}
}