using Books.Models;
using Books.Interfaces;
using Books.Services;
using Moq;

namespace Books.UnitTests
{

    public class AuthorTests
    {
        private readonly IAuthorRepository _mockRepo;
        private readonly List<Author> _mockAuthors;
        private readonly IAuthorService _service;

        public AuthorTests()
        {
            _mockAuthors = new List<Author>
            {
                new Author()
                {
                    Id = 1,
                    Name = "Ghtyp",
                    YearBirth = 1789,
                    YearDeath = 4352,
                    Country = "txyuggjn",
                    Genre = "sdfdsf",
                    Language = "sadsf"
                },
                new Author()
                {
                    Id = 2,
                    Name = "yjtyh",
                    YearBirth = 1739,
                    YearDeath = 3521,
                    Country = "rtrth",
                    Genre = "gh8",
                    Language = "qw"
                }
            };

            var mockRepo = new Mock<IAuthorRepository>();

            mockRepo.Setup(repo => repo.GetAll()).Returns(_mockAuthors);
            mockRepo.Setup(repo => repo.GetByID(It.IsAny<int>())).Returns(
                (int id) => _mockAuthors.Find(x => x.Id == id));

            mockRepo.Setup(repo => repo.Update(It.IsAny<Author>())).Callback(
                (Author author) =>
                {
                    _mockAuthors
                        .FindAll(x => x.Id == author.Id)
                        .ForEach(x =>
                        {
                            x.Name = author.Name;
                            x.YearBirth = author.YearBirth;
                            x.YearDeath = author.YearDeath;
                            x.Country = author.Country;
                            x.Genre = author.Genre;
                            x.Language = author.Language;
                        });
                }
                );


            _mockRepo = mockRepo.Object;
            _service = new AuthorService(_mockRepo);
        }

        [Fact]
        public void UpdateAuthorTest()
        {
            var expectedCount = _mockAuthors.Count;
            
            var author = new Author()
            {
                Id = 1,
                Name = "Ghtyp",
                YearBirth = 1789,
                YearDeath = 4352,
                Country = "txyuggjn",
                Genre = "sdfdsf",
                Language = "sadsf"
            };

            var res = _service.GetAll();
            
            Assert.Equal(expectedCount, res.Count());

            _service.Update(author);

            res = _service.GetAll();

            Assert.Equal(expectedCount, res.Count());
            Assert.All(res, item => Assert.InRange(item.Id, low: 1, high: expectedCount));

            Author newVal = null;
            foreach (Author item in res)
            {
                if (item.Id == author.Id)
                    newVal = item;
            }
 
            Assert.NotNull(newVal);
            Assert.Equal(newVal?.Id, author.Id);
            Assert.Equal(newVal?.Name, author.Name);
            Assert.Equal(newVal?.YearBirth, author.YearBirth);
            Assert.Equal(newVal?.YearDeath, author.YearDeath);
            Assert.Equal(newVal?.Country, author.Country);
            Assert.Equal(newVal?.Genre, author.Genre);
            Assert.Equal(newVal?.Language, author.Language);
        }

    }
}
