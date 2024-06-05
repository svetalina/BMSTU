using Books.Models;
using Books.Interfaces;
using static Books.Services.SortOrder;

namespace Books.Services
{
    public class UserService : IUserService
    {
        private IUserRepository _userRepository;

        public UserService(IUserRepository userRepository)
        {
            _userRepository = userRepository;
        }

        private bool IsExist(User user)
        {
            return _userRepository.GetAll().FirstOrDefault(elem =>
                    elem.Login == user.Login) != null;
        }

        private bool IsNotExist(int id)
        {
            return _userRepository.GetByID(id) == null;
        }


        public void Add(User user)
        {
            if (IsExist(user))
                throw new Exception("Пользователь с таким логином уже существует");

            _userRepository.Add(user);
        }

        public void Update(User user)
        {
            if (IsNotExist(user.Id))
                throw new Exception("Такого пользователя не существует");

            _userRepository.Update(user);
        }

        public void Delete(User user)
        {
            if (IsNotExist(user.Id))
                throw new Exception("Такого пользователя не существует");

            _userRepository.Delete(user.Id);
        }

        public IEnumerable<User> GetAll()
        {
            return _userRepository.GetAll();
        }

        public User GetByID(int id)
        {
            return _userRepository.GetByID(id);
        }

        public User GetByLogin(string login)
        {
            return _userRepository.GetByLogin(login);
        }

        public IEnumerable<User> GetByPermission(string permission)
        {
            return _userRepository.GetByPermission(permission);
        }

        public IEnumerable<User> GetSortUsersByOrder(IEnumerable<User> users, UserSortOrder sortOrder)
        {
            IEnumerable<User> sortedUsers = sortOrder switch
            {
                UserSortOrder.IdAsc => users.OrderByDescending(elem => elem.Id),
                UserSortOrder.IdDesc => users.OrderByDescending(elem => elem.Id),

                UserSortOrder.LoginAsc => users.OrderBy(elem => elem.Login),
                UserSortOrder.LoginDesc => users.OrderByDescending(elem => elem.Login),

                UserSortOrder.PermissionAsc => users.OrderBy(elem => elem.Permission),
                UserSortOrder.PermissionDesc => users.OrderByDescending(elem => elem.Permission),
            };

            return sortedUsers;
        }
    }
}