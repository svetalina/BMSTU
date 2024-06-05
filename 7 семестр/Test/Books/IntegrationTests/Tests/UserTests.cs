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
	[AllureSuite("UserIntegrationSuite")]
	public class UserTests
	{
		AppDbContext _dbContext;
		IUserRepository _userRepository;
		IUserService _userService;

		public UserTests()
		{
			_dbContext = new DbContext().GetDbContext();
			_userRepository = new UserRepository(_dbContext);
			_userService = new UserService(_userRepository);
		}

		[AllureXunit]
		public void TestAdd()
		{
			var transaction = _dbContext.Database.BeginTransaction();

			var expected = new UserObjectMother().User_2();

			_userService.Add(expected);

			var actual = _userService.GetByLogin(expected.Login);

			Assert.Equal(expected.Login, actual.Login);
			Assert.Equal(expected.Password, actual.Password);
			Assert.Equal(expected.Permission, actual.Permission);

			transaction.Rollback();
		}

		[AllureXunit]
		public void TestAddException()
		{
			var transaction = _dbContext.Database.BeginTransaction();

			var expected = new UserObjectMother().User_1();

			var exception = Assert.Throws<Exception>(() => _userService.Add(expected));

			Assert.Equal("Пользователь с таким логином уже существует", exception.Message);

			transaction.Rollback();
		}

		[AllureXunit]
		public void TestUpdate()
		{
			var transaction = _dbContext.Database.BeginTransaction();

			var expected = new UserObjectMother().User_2();
			expected.Id = 1;

			_userService.Update(expected);

			var actual = _userService.GetByLogin(expected.Login);

			Assert.Equal(expected.Id, actual.Id);
			Assert.Equal(expected.Login, actual.Login);
			Assert.Equal(expected.Password, actual.Password);
			Assert.Equal(expected.Permission, actual.Permission);

			transaction.Rollback();
		}

		[AllureXunit]
		public void TestUpdateException()
		{
			var transaction = _dbContext.Database.BeginTransaction();

			var expected = new UserObjectMother().User_2();
			expected.Id = 3;

			var exception = Assert.Throws<Exception>(() => _userService.Update(expected));

			Assert.Equal("Такого пользователя не существует", exception.Message);

			transaction.Rollback();
		}

		[AllureXunitTheory]
		[InlineData(1, "login_1")]
		public void TestDelete(int _id, string _login)
		{
			var transaction = _dbContext.Database.BeginTransaction();

			var expected = new UserBuilder()
								.WithId(_id)
								.WithLogin(_login)
								.Build();

			_userService.Delete(expected);

			var actual = _userService.GetByLogin(expected.Login);

			Assert.Null(actual);

			transaction.Rollback();
		}

		[AllureXunitTheory]
		[InlineData(3)]
		public void TestDeleteException(int _id)
		{
			var transaction = _dbContext.Database.BeginTransaction();

			var expected = new UserBuilder()
								.WithId(_id)
								.Build();

			var exception = Assert.Throws<Exception>(() => _userService.Delete(expected));

			Assert.Equal("Такого пользователя не существует", exception.Message);

			transaction.Rollback();
		}


		[AllureXunit]
		public void TestGetAll()
		{
			var actual = _userService.GetAll();

			Assert.Equal(2, actual.Count());
		}


		[AllureXunit]
		public void TestGetByLogin()
		{
			var expected = new UserObjectMother().User_1();
			expected.Id = 1;

			var actual = _userService.GetByLogin(expected.Login);

			Assert.Equal(expected.Id, actual.Id);
			Assert.Equal(expected.Login, actual.Login);
			Assert.Equal(expected.Password, actual.Password);
			Assert.Equal(expected.Permission, actual.Permission);
		}

	}
}
