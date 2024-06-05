using Books.Models;
using Books.Repository;
using Books.Services;
using Microsoft.EntityFrameworkCore;
using Microsoft.Extensions.Configuration;


namespace IntegrationTests
{
    public class BookTests
    {
        private DbContextOptions<AppDBContext> _options;

        public BookTests()
        {
            IConfigurationRoot configuration = new ConfigurationBuilder()
                .AddJsonFile("appsettings.json")
                .Build();

            string connectionString = configuration.GetConnectionString("DefaultConnection");

            _options = new DbContextOptionsBuilder<AppDBContext>()
                .UseSqlServer(connectionString)
                .Options;
        }

        [Fact]
        public void AddBookTest()
        {
            using (var dbContext = new AppDBContext(_options))
            {
                var bookRepository = new BookRepository(dbContext);
                var bookService = new BookService(bookRepository);

                var book = new Book
                {
                    Name = "War and Piece",
                    Genre = "Fiction",
                    Language = "Russia",
                    Rating = 8
                };

                bookService.Add(book);

                var addedBook = bookService.GetByName(book.Name);
                
                Assert.NotNull(addedBook);
                Assert.Equal(book.Name, addedBook.Name);
                Assert.Equal(book.Genre, addedBook.Genre);
                Assert.Equal(book.Language, addedBook.Language);
                Assert.Equal(book.Rating, addedBook.Rating);
            }
        }

        [Fact]
        public void UpdateBookTest()
        {
            using (var dbContext = new AppDBContext(_options))
            {
                var bookRepository = new BookRepository(dbContext);
                var bookService = new BookService(bookRepository);

                var book = new Book
                {
                    Id = 2,
                    Name = "Sample Book",
                    Genre = "Fiction",
                    Language = "Russia",
                    Rating = 7
                };

                bookService.Update(book);

                var updatedBook = bookService.GetByName(book.Name);

                Assert.NotNull(updatedBook);
                Assert.Equal(book.Name, updatedBook.Name);
                Assert.Equal(book.Genre, updatedBook.Genre);
                Assert.Equal(book.Language, updatedBook.Language);
                Assert.Equal(book.Rating, updatedBook.Rating);
            }
        }

        [Fact]
        public void DeleteBookTest()
        {
            using (var dbContext = new AppDBContext(_options))
            {
                var bookRepository = new BookRepository(dbContext);
                var bookService = new BookService(bookRepository);

                var book = new Book
                {
                    Id = 1
                };

                bookService.Delete(book);

                var deletedBook = bookService.GetByName(book.Name);

                Assert.Null(deletedBook);
            }
        }

        [Fact]
        public void GetAllBookTest()
        {
            using (var dbContext = new AppDBContext(_options))
            {
                var bookRepository = new BookRepository(dbContext);
                var bookService = new BookService(bookRepository);

                var books = bookService.GetAll();

                Assert.Equal(10, books.Count());
            }
        }

        [Fact]
        public void GetByIdBookTest()
        {
            using (var dbContext = new AppDBContext(_options))
            {
                var bookRepository = new BookRepository(dbContext);
                var bookService = new BookService(bookRepository);

                var book = new Book
                {
                    Id = 4,
                    Name = "1984",
                    Genre = "Dystopian",
                    Language = "English",
                    Rating = 5
                };

                var getedBook = bookService.GetById(book.Id);

                Assert.NotNull(book);
                Assert.Equal(book.Name, getedBook.Name);
                Assert.Equal(book.Genre, getedBook.Genre);
                Assert.Equal(book.Language, getedBook.Language);
                Assert.Equal(book.Rating, getedBook.Rating);
            }
        }

        [Fact]
        public void GetByAuthorBookTest()
        {
            using (var dbContext = new AppDBContext(_options))
            {
                var bookRepository = new BookRepository(dbContext);
                var bookService = new BookService(bookRepository);

                var getedBook = bookService.GetByAuthor("Jane Austen");
                Assert.NotNull(getedBook);

                Assert.Contains("To Kill a Mockingbird", getedBook.Select(b => b.Name));
                Assert.Contains("1984", getedBook.Select(b => b.Name));
                Assert.Contains("The Chronicles of Narnia", getedBook.Select(b => b.Name));

            }
        }
    }
}