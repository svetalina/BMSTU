using Books.Models;

namespace Books.Repository
{
	public interface IUserRepository
	{
		public User Add(User model);
		public User Update(User model);
		public User Delete(int id);

		public IEnumerable<User> GetAll();
		public User GetById(int id);
		public User GetByLogin(string login);
	}


	public class UserRepository : IUserRepository
    {
        private readonly AppDbContext _appDBContext;

        public UserRepository(AppDbContext appDBContext)
        {
            _appDBContext = appDBContext;
        }

		public User Add(User model)
		{
			try
			{
				_appDBContext.User.Add(model);
				_appDBContext.SaveChanges();

				return _appDBContext.User.FirstOrDefault(elem => elem.Id == model.Id);
			}
			catch (Exception ex)
			{
				Console.Write(ex.Message);
				throw new Exception("Ошибка при добавлении пользователя");
			}
		}

		public User Update(User model)
		{
			try
			{
				var curModel = _appDBContext.User.FirstOrDefault(elem => elem.Id == model.Id);

				_appDBContext.Entry(curModel).CurrentValues.SetValues(model);
				_appDBContext.SaveChanges();

				return _appDBContext.User.FirstOrDefault(elem => elem.Id == model.Id);
			}
			catch (Exception ex)
			{
				Console.Write(ex.Message);
				throw new Exception("Ошибка при обновлении пользователя");
			}
		}

		public User Delete(int id)
		{
			try
			{
				User user = _appDBContext.User.Find(id);

				if (user != null)
				{
					_appDBContext.User.Remove(user);
					_appDBContext.SaveChanges();
				}

				return user;
			}
			catch (Exception ex)
			{
				Console.Write(ex.Message);
				throw new Exception("Ошибка при удалении пользователя");
			}
		}

		public IEnumerable<User> GetAll()
        {
            return _appDBContext.User.ToList();
        }

        public User GetById(int id)
        {
            return _appDBContext.User.Find(id);
        }

        public User GetByLogin(string login)
        {
            return _appDBContext.User.FirstOrDefault(elem => elem.Login == login);
        }
	}
}