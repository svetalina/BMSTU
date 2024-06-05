using AutoMapper;
using Books.Models;
using Books.ModelsBL;
using Books.Repository;

namespace Books.Services
{
	public interface IUserService
	{
		UserBL Add(UserBL user);
		UserBL Update(UserBL user);
		UserBL Delete(int id);

		IEnumerable<UserBL> GetAll();
		UserBL GetById(int id);
		UserBL GetByLogin(string login);
	}

	public class UserService : IUserService
    {
		private readonly IUserRepository _userRepository;
		private readonly IMapper _mapper;

		public UserService(IUserRepository userRepository,
                           IMapper mapper)
        {
            _userRepository = userRepository;
			_mapper = mapper;
		}
		private bool IsExist(UserBL user)
		{
			return _userRepository.GetAll().FirstOrDefault(elem =>
					elem.Login == user.Login) != null;
		}

        private bool IsNotExist(int id)
        {
            return _userRepository.GetById(id) == null;
        }

		public UserBL Add(UserBL user)
		{
			if (IsExist(user))
				throw new Exception("Такой пользователь уже существует");

			return _mapper.Map<UserBL>(_userRepository.Add(_mapper.Map<User>(user)));

		}

		public UserBL Update(UserBL user)
		{
			if (IsNotExist(user.Id))
				throw new Exception("Такой пользователь не существует");

			return _mapper.Map<UserBL>(_userRepository.Update(_mapper.Map<User>(user)));
		}

		public UserBL Delete(int id)
		{
			return _mapper.Map <UserBL>(_userRepository.Delete(id));
		}

		public IEnumerable<UserBL> GetAll()
		{
			return _mapper.Map<IEnumerable<UserBL>>(_userRepository.GetAll());
		}

		public UserBL GetById(int id)
		{
			return _mapper.Map<UserBL>(_userRepository.GetById(id));
		}

		public UserBL GetByLogin(string login)
		{
			return _mapper.Map<UserBL>(_userRepository.GetByLogin(login));
		}
	}
}