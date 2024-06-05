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
	[AllureSuite("AuthorRepositorySuite")]
	public class AuthorTests
	{
		AppDbContext _dbContext;
		AuthorRepository _authorRepository;

		public AuthorTests()
		{
			_dbContext = new DbContext().GetDbContext();
			_authorRepository = new AuthorRepository(_dbContext);

			if (!_dbContext.Author.Any())
			{
				_dbContext.Database.ExecuteSqlRaw("DBCC CHECKIDENT ('Author', RESEED, 0);");
				_dbContext.Author.Add(new AuthorObjectMother().Author_1());
				_dbContext.SaveChanges();
			}
		}

		[AllureXunit]
		public void TestGetAll()
		{
			int expected = _dbContext.Author.Count();

			int actual = _authorRepository.GetAll().Count();

			Assert.Equal(expected, actual);
		}

		[AllureXunitTheory]
		[InlineData(1, "name_1", "genre_1", "country_1", 1, 1)]
		public void TestGetById(int _id, string _name, string _genre,
						string _country, int _yearBirth, int _yearDeath)
		{
			var expected = new AuthorBuilder()
								.WithId(_id)
								.WithName(_name)
								.WithGenre(_genre)
								.WithCountry(_country)
								.WithYearBirth(_yearBirth)
								.WithYearDeath(_yearDeath)
								.Build();

			var actual = _authorRepository.GetById(_id);

			Assert.Equal(expected.Id, actual.Id);
			Assert.Equal(expected.Name, actual.Name);
			Assert.Equal(expected.Genre, actual.Genre);
			Assert.Equal(expected.Country, actual.Country);
			Assert.Equal(expected.YearBirth, actual.YearBirth);
			Assert.Equal(expected.YearDeath, actual.YearDeath);
		}

		[AllureXunitTheory]
		[InlineData("name_2", "genre_2", "country_2", 2, 2)]
		public void TestAdd(string _name, string _genre,
						string _country, int _yearBirth, int _yearDeath)
		{
			var transaction = _dbContext.Database.BeginTransaction();

			var expected = new AuthorBuilder()
							.WithName(_name)
							.WithYearBirth(_yearBirth)
							.WithYearDeath(_yearDeath)
							.WithCountry(_country)
							.WithGenre(_genre)
							.Build();

			_authorRepository.Add(expected);

			var actual = _dbContext.Author.Where(a => a.Name == _name).FirstOrDefault();

			Assert.Equal(expected.Name, actual.Name);
			Assert.Equal(expected.YearBirth, actual.YearBirth);
			Assert.Equal(expected.YearDeath, actual.YearDeath);
			Assert.Equal(expected.Country, actual.Country);
			Assert.Equal(expected.Genre, actual.Genre);

			transaction.Rollback();
		}

		[AllureXunitTheory]
		[InlineData("author_2")]
		public void TestAddException(string _name)
		{
			var transaction = _dbContext.Database.BeginTransaction();

			var expected = new AuthorBuilder()
							.WithName(_name)
							.Build();

			var exception = Assert.Throws<Exception>(() => _authorRepository.Add(expected));

			Assert.Equal("Ошибка при добавлении автора", exception.Message);

			transaction.Rollback();
		}

		[AllureXunitTheory]
		[InlineData(1, "name_2", "genre_2", "country_2", 2, 2)]
		public void TestUpdate(int _id, string _name, string _genre,
						string _country, int _yearBirth, int _yearDeath)
		{ 
			var transaction = _dbContext.Database.BeginTransaction();

			var expected = new AuthorBuilder()
							.WithId(_id)
							.WithName(_name)
							.WithYearBirth(_yearBirth)
							.WithYearDeath(_yearDeath)
							.WithCountry(_country)
							.WithGenre(_genre)
							.Build();

			_authorRepository.Update(expected);

			var actual = _dbContext.Author.Where(a => a.Id == _id).FirstOrDefault();

			Assert.Equal(expected.Id, actual.Id);
			Assert.Equal(expected.Name, actual.Name);
			Assert.Equal(expected.YearBirth, actual.YearBirth);
			Assert.Equal(expected.YearDeath, actual.YearDeath);
			Assert.Equal(expected.Country, actual.Country);
			Assert.Equal(expected.Genre, actual.Genre);

			transaction.Rollback();
		}

		[AllureXunitTheory]
		[InlineData(2, "name_2", "genre_2", "country_2", 2, 2)]
		public void TestUpdateException(int _id, string _name, string _genre,
						string _country, int _yearBirth, int _yearDeath)
		{ 
			var transaction = _dbContext.Database.BeginTransaction();

			var expected = new AuthorBuilder()
							.WithId(_id)
							.WithName(_name)
							.WithYearBirth(_yearBirth)
							.WithYearDeath(_yearDeath)
							.WithCountry(_country)
							.WithGenre(_genre)
							.Build();

			var exception = Assert.Throws<Exception>(() => _authorRepository.Update(expected));

			Assert.Equal("Ошибка при обновлении автора", exception.Message);

			transaction.Rollback();
		}

		[AllureXunitTheory]
		[InlineData(1)]
		public void TestDelete(int _id)
		{
			var transaction = _dbContext.Database.BeginTransaction();

			_authorRepository.Delete(_id);

			var actual = _dbContext.Author.Where(a => a.Id == _id).FirstOrDefault();
			Assert.Null(actual);

			transaction.Rollback();
		}

		[AllureXunitTheory]
		[InlineData(0)]
		public void TestDeleteException(int _id)
		{
			var transaction = _dbContext.Database.BeginTransaction();

			var exception = Assert.Throws<Exception>(() => _authorRepository.Delete(_id));

			Assert.Equal("Ошибка при удалении автора", exception.Message);

			transaction.Rollback();
		}

		[AllureXunitTheory]
		[InlineData(1, "name_1", "genre_1", "country_1", 1, 1)]
		public void TestGetByName(int _id, string _name, string _genre,
						string _country, int _yearBirth, int _yearDeath)
		{
			var expected = new AuthorBuilder()
								.WithId(_id)
								.WithName(_name)
								.WithGenre(_genre)
								.WithCountry(_country)
								.WithYearBirth(_yearBirth)
								.WithYearDeath(_yearDeath)
								.Build();

			var actual = _authorRepository.GetByName(_name);

			Assert.Equal(expected.Id, actual.Id);
			Assert.Equal(expected.Name, actual.Name);
			Assert.Equal(expected.Genre, actual.Genre);
			Assert.Equal(expected.Country, actual.Country);
			Assert.Equal(expected.YearBirth, actual.YearBirth);
			Assert.Equal(expected.YearDeath, actual.YearDeath);
		}
	}
}
