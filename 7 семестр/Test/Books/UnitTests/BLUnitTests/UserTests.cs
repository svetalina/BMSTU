using Xunit;
using Allure.Xunit.Attributes;
using Books.Interfaces;
using Books.Services;
using Moq;
using UnitTests.ObjectMother;
using Books.Models;
using UnitTests.DataBuilder;

namespace UnitTests.BLUnitTests
{
	[TestCaseOrderer(
		ordererTypeName: "UnitTests.Order.RandomOrder",
		ordererAssemblyName: "UnitTests")]
	[AllureSuite("UserServiceSuite")]
	public class UserTests
	{
		private List<User> _mockList;
		private readonly IUserService _service;

		public UserTests()
		{
			var user = new UserObjectMother().User_1();
			user.Id = 1;

			_mockList = new List<User>
			{
				user
			};

			var mockRepo = new Mock<IUserRepository>();

			mockRepo.Setup(repo => repo.Add(It.IsAny<User>())).Callback(
			   (User user) =>
			   {
				   user.Id = _mockList.Count + 1;
				   _mockList.Add(user);
			   }
			   );

			mockRepo.Setup(repo => repo.Update(It.IsAny<User>())).Callback<User>(
				(User user) =>
				{
					var existing = _mockList.FirstOrDefault(x => x.Id == user.Id);
					if (existing != null)
					{
						existing.Login = user.Login;
						existing.Password = user.Password;
						existing.Permission = user.Permission;
					}
				}
				);

			mockRepo.Setup(repo => repo.Delete(It.IsAny<int>())).Callback(
			   (int id) => _mockList.RemoveAll(x => x.Id == id));

			mockRepo.Setup(repo => repo.GetAll()).Returns(_mockList);

			mockRepo.Setup(repo => repo.GetById(It.IsAny<int>())).Returns(
				(int id) => _mockList.Find(x => x.Id == id));

			mockRepo.Setup(repo => repo.GetByLogin(It.IsAny<string>())).Returns(
				(string login) => _mockList.Find(x => x.Login == login));

			_service = new UserService(mockRepo.Object);
		}

		[AllureXunit]
		public void TestAdd()
		{
			var expected = new UserObjectMother().User_2();

			_service.Add(expected);

			var actual = _service.GetByLogin(expected.Login);

			Assert.Equal(expected.Login, actual.Login);
			Assert.Equal(expected.Password, actual.Password);
			Assert.Equal(expected.Permission, actual.Permission);
		}

		[AllureXunit]
		public void TestAddException()
		{
			var expected = new UserObjectMother().User_1();

			var exception = Assert.Throws<Exception>(() => _service.Add(expected));

			Assert.Equal("Пользователь с таким логином уже существует", exception.Message);
		}

		[AllureXunit]
		public void TestUpdate()
		{
			var expected = new UserObjectMother().User_2();
			expected.Id = 1;

			_service.Update(expected);

			var actual = _service.GetByLogin(expected.Login);

			Assert.Equal(expected.Id, actual.Id);
			Assert.Equal(expected.Login, actual.Login);
			Assert.Equal(expected.Password, actual.Password);
			Assert.Equal(expected.Permission, actual.Permission);
		}

		[AllureXunit]
		public void TestUpdateException()
		{
			var expected = new UserObjectMother().User_2();
			expected.Id = 2;

			var exception = Assert.Throws<Exception>(() => _service.Update(expected));

			Assert.Equal("Такого пользователя не существует", exception.Message);
		}

		[AllureXunitTheory]
		[InlineData(1, "login_1")]
		public void TestDelete(int _id, string _login)
		{
			var expected = new UserBuilder()
								.WithId(_id)
								.WithLogin(_login)
								.Build();

			_service.Delete(expected);

			var actual = _service.GetByLogin(expected.Login);

			Assert.Null(actual);
		}

		[AllureXunitTheory]
		[InlineData(2)]
		public void TestDeleteException(int _id)
		{
			var expected = new UserBuilder()
								.WithId(_id)
								.Build();

			var exception = Assert.Throws<Exception>(() => _service.Delete(expected));

			Assert.Equal("Такого пользователя не существует", exception.Message);
		}


		[AllureXunit]
		public void TestGetAll()
		{
			var actual = _service.GetAll();

			Assert.Equal(_mockList.Count(), actual.Count());
		}


		[AllureXunit]
		public void TestGetByLogin()
		{
			var expected = new UserObjectMother().User_1();
			expected.Id = 1;

			var actual = _service.GetByLogin(expected.Login);

			Assert.Equal(expected.Id, actual.Id);
			Assert.Equal(expected.Login, actual.Login);
			Assert.Equal(expected.Password, actual.Password);
			Assert.Equal(expected.Permission, actual.Permission);
		}

	}
}
