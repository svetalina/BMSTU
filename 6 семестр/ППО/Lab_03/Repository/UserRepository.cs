using Books.Interfaces;
using Books.Models;

namespace Books.Repository
{
    public class UserRepository : IUserRepository
    {
        public UserRepository()
        {
        }

        public void Add(User model)
        {
            throw new NotImplementedException();
        }

        public void Update(User model)
        {
            throw new NotImplementedException();
        }

        public void Delete(int id)
        {
            throw new NotImplementedException();
        }

        public IEnumerable<User> GetAll()
        {
            throw new NotImplementedException();
        }

        public User GetByID(int id)
        {
            throw new NotImplementedException();
        }


        public User GetByLogin(string login)
        {
            throw new NotImplementedException();
        }

        public IEnumerable<User> GetByPermission(string permission)
        {
            throw new NotImplementedException();
        }
    }
}