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
	[AllureSuite("UserRepositorySuite")]
	public class UserTests
	{
		AppDbContext _dbContext;
		UserRepository _userRepository;

		public UserTests()
		{
			_dbContext = new DbContext().GetDbContext();
			_userRepository = new UserRepository(_dbContext);

			if (!_dbContext.User.Any())
			{
				_dbContext.Database.ExecuteSqlRaw("DBCC CHECKIDENT ('User', RESEED, 0);");
				_dbContext.User.Add(new UserObjectMother().User_1());
				_dbContext.User.Add(new UserObjectMother().User_2());
				_dbContext.SaveChanges();
			}

			_userRepository.GetAll();
		}

		[AllureXunit]
		public void TestGetAll()
		{
			int expected = _dbContext.User.Count();

			int actual = _userRepository.GetAll().Count();
			
			Assert.Equal(expected, actual);
		}

		[AllureXunitTheory]
		[InlineData(1, "login_1", "password_1", "user")]
		public void TestGetById(int _id, string _login, string _password, string _permission)
		{
			var expected = new UserBuilder()
								.WithId(_id)
								.WithLogin(_login)
								.WithPassword(_password)
								.WithPermission(_permission)
								.Build();

			var actual = _userRepository.GetById(_id);

			Assert.Equal(expected.Id, actual.Id);
			Assert.Equal(expected.Login, actual.Login);
			Assert.Equal(expected.Password, actual.Password);
			Assert.Equal(expected.Permission, actual.Permission);
		}

		[AllureXunitTheory]
		[InlineData(1, "login_1", "password_1", "user")]
		public void TestGetByLogin(int _id, string _login, string _password, string _permission)
		{
			var expected = new UserBuilder()
								.WithId(_id)
								.WithLogin(_login)
								.WithPassword(_password)
								.WithPermission(_permission)
								.Build();

			var actual = _userRepository.GetByLogin(_login);

			Assert.Equal(expected.Id, actual.Id);
			Assert.Equal(expected.Login, actual.Login);
			Assert.Equal(expected.Password, actual.Password);
			Assert.Equal(expected.Permission, actual.Permission);
		}

		[AllureXunitTheory]
		[InlineData("login_3", "password_3", "user")]
		public void TestAdd(string _login, string _password, string _permission)
		{
			var transaction = _dbContext.Database.BeginTransaction();

			var expected = new UserBuilder()
								.WithLogin(_login)
								.WithPassword(_password)
								.WithPermission(_permission)
								.Build();

			_userRepository.Add(expected);

			var actual = _dbContext.User.Where(u => u.Login == _login).FirstOrDefault();

			Assert.Equal(expected.Login, actual.Login);
			Assert.Equal(expected.Password, actual.Password);
			Assert.Equal(expected.Permission, actual.Permission);

			transaction.Rollback();
		}

		[AllureXunitTheory]
		[InlineData("login_2")]
		public void TestAddException(string _login)
		{
			var transaction = _dbContext.Database.BeginTransaction();

			var expected = new UserBuilder()
								.WithLogin(_login)
								.Build();

			var exception = Assert.Throws<Exception>(() => _userRepository.Add(expected));

			Assert.Equal("Ошибка при добавлении пользователя", exception.Message);

			transaction.Rollback();
		}

		[AllureXunitTheory]
		[InlineData(1, "login_3", "password_3", "user")]
		public void TestUpdate(int _id, string _login, string _password, string _permission)
		{
			var transaction = _dbContext.Database.BeginTransaction();

			var expected = new UserBuilder()
								.WithId(_id)
								.WithLogin(_login)
								.WithPassword(_password)
								.WithPermission(_permission)
								.Build();

			_userRepository.Update(expected);

			var actual = _dbContext.User.Where(u => u.Id == _id).FirstOrDefault();

			Assert.Equal(expected.Id, actual.Id);
			Assert.Equal(expected.Login, actual.Login);
			Assert.Equal(expected.Password, actual.Password);
			Assert.Equal(expected.Permission, actual.Permission);

			transaction.Rollback();
		}

		[AllureXunitTheory]
		[InlineData(3, "login_3", "password_3", "user")]
		public void TestUpdateException(int _id, string _login, string _password, string _permission)
		{
			var transaction = _dbContext.Database.BeginTransaction();

			var expected = new UserBuilder()
								.WithId(_id)
								.WithLogin(_login)
								.WithPassword(_password)
								.WithPermission(_permission)
								.Build();

			var exception = Assert.Throws<Exception>(() => _userRepository.Update(expected));

			Assert.Equal("Ошибка при обновлении пользователя", exception.Message);

			transaction.Rollback();
		}

		[AllureXunitTheory]
		[InlineData(2)]
		public void TestDelete(int _id)
		{
			var transaction = _dbContext.Database.BeginTransaction();
			
			_userRepository.Delete(_id);
			
			var actual = _dbContext.User.Where(u => u.Id == _id).FirstOrDefault();
			Assert.Null(actual);
			
			transaction.Rollback();
		}

		[AllureXunitTheory]
		[InlineData(0)]
		public void TestDeleteException(int _id)
		{
			var transaction = _dbContext.Database.BeginTransaction();

			var exception = Assert.Throws<Exception>(() => _userRepository.Delete(_id));

			Assert.Equal("Ошибка при удалении пользователя", exception.Message);

			transaction.Rollback();
		}
	}
}