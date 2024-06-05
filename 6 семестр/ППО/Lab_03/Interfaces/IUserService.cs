using Books.Models;
using Books.Services;

namespace Books.Interfaces
{
    public interface IUserService : IService<User>

    {     
        User GetByLogin(string login);
        IEnumerable<User> GetByPermission(string permission);

        IEnumerable<User> GetSortUsersByOrder(IEnumerable<User> users, UserSortOrder sortOrder);
    }
}
