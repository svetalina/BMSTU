using Books.Models;

namespace Books.Interfaces
{
    public interface IUserService : IService<User>
    {
        User GetByLogin(string login);
    }
}
