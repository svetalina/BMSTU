using Books.Models;
using Books.Interfaces;
using Books.Services;
using Moq;

namespace Books.UnitTests
{

    public class UserTests
    {
        private readonly IUserRepository _mockRepo;
        private readonly List<User> _mockUsers;
        private readonly IUserService _service;

        public UserTests()
        {
            _mockUsers = new List<User>
            {
                new User()
                {
                    Id = 1,
                    Login = "qwerty",
                    Password = "123456",
                    Permission = "user"
                },
                new User()
                {
                    Id = 2,
                    Login = "asdfg",
                    Password = "654321",
                    Permission = "user"
                }
            };

            var mockRepo = new Mock<IUserRepository>();
            
            mockRepo.Setup(repo => repo.GetAll()).Returns(_mockUsers);
            
            mockRepo.Setup(repo => repo.GetByID(It.IsAny<int>())).Returns(
                (int id) => _mockUsers.Find(x => x.Id == id));

            mockRepo.Setup(repo => repo.Add(It.IsAny<User>())).Callback(
               (User user) =>
               {
                   user.Id = _mockUsers.Count + 1;
                   _mockUsers.Add(user);
               }
               );
            
            mockRepo.Setup(repo => repo.Delete(It.IsAny<int>())).Callback(
                (int id) => _mockUsers.RemoveAll(x => x.Id == id));

            _mockRepo = mockRepo.Object;
            _service = new UserService(_mockRepo);
        }

        [Fact]
        public void GetAllUserTest()
        {
            var expectedCount = _mockUsers.Count;

            var res = _service.GetAll();

            Assert.IsType<List<User>>(res);
            Assert.Equal(expectedCount, res.Count());
            Assert.All(res, item => Assert.InRange(item.Id, low: 1, high: expectedCount));
        }

        [Fact]
        public void AddExistUserTest()
        {
            var user = new User()
            {
                Login = "qwerty",
                Password = "dghdjsf",
                Permission = "user"
            };

            void action() => _service.Add(user);

            Assert.Throws<Exception>(action);
        }

        [Fact]
        public void DeleteUserTest()
        {
            var expectedCount = _mockUsers.Count;
            var user = new User()
            {
                Id = 2,
                Login = "asdfg",
                Password = "654321",
                Permission = "user"
            };

            var res = _service.GetAll();
            Assert.Equal(expectedCount, res.Count());

            _service.Delete(user);

            res = _service.GetAll();

            Assert.Equal(expectedCount - 1, res.Count());
            Assert.Null(_mockUsers.Find(x => x.Id == user.Id));
        }

    }
}
