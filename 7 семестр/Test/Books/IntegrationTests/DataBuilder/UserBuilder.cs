using Books.Models;

namespace IntegrationTests.DataBuilder
{
	public class UserBuilder
	{
		private User _user;

		public UserBuilder()
		{
			_user = new User { };
		}

		public UserBuilder WithId(int id)
		{
			_user.Id = id;
			return this;
		}

		public UserBuilder WithLogin(string login)
		{
			_user.Login = login;
			return this;
		}

		public UserBuilder WithPassword(string password)
		{
			_user.Password = password;
			return this;
		}

		public UserBuilder WithPermission(string permission)
		{
			_user.Permission = permission;
			return this;
		}

		public User Build()
		{
			return _user;
		}
	}
}
