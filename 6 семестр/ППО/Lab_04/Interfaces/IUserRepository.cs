using Books.Models;

namespace Books.Interfaces
{
    public interface IUserRepository : IRepository<User>
    {
        User GetByLogin(string login);
        
        IEnumerable<User> GetByPermission(string permission);
    }
}