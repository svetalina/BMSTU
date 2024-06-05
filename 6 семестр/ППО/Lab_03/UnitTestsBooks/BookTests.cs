using Books.Models;
using Books.Interfaces;
using Books.Services;
using Moq;

namespace Books.UnitTests
{

    public class BookTests
    {
        private readonly IBookRepository _mockRepo;
        private readonly List<Book> _mockBooks;
        private readonly IBookService _service;

        public BookTests()
        {
            _mockBooks = new List<Book>
            {
                new Book()
                {
                    Id = 1,
                    Name = "qwerty",
                    Genre = "sdfg",
                    Language = "fghj",
                    Rating = 4
                },
                new Book()
                {
                    Id = 2,
                    Name = "vghj",
                    Genre = "sdfg",
                    Language = "iuhj",
                    Rating = 6
                }
            };

            var mockRepo = new Mock<IBookRepository>();

            mockRepo.Setup(repo => repo.GetAll()).Returns(_mockBooks);



            mockRepo.Setup(repo => repo.Add(It.IsAny<Book>())).Callback(
                (Book book) =>
                {
                    book.Id = _mockBooks.Count + 1;
                     _mockBooks.Add(book);
                }
            );

            _mockRepo = mockRepo.Object;
            _service = new BookService(_mockRepo);
        }

        [Fact]
        public void AddBookTest()
        {
            var expectedCount = _mockBooks.Count;
            var expectedCount2 = expectedCount + 1;
            var res = _service.GetAll();

            var book = new Book()
            {
                Id = 3,
                Name = "jkl",
                Genre = "cssdfgh",
                Language = "okj",
                Rating = 7
            };

            Assert.Equal(expectedCount, res.Count());

            _service.Add(book);

            res = _service.GetAll();

            Assert.Equal(expectedCount2, res.Count());
            Assert.All(res, item => Assert.InRange(item.Id, low: 1, high: expectedCount2));
        }

    }
}
