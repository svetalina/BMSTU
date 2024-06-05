using Xunit;
using Allure.Xunit.Attributes;
using Books.Models;
using Books.Interfaces;
using Books.Services;
using Books.Repository;

namespace E2ETests
{
	[TestCaseOrderer(
	ordererTypeName: "E2ETests.Order.RandomOrder",
	ordererAssemblyName: "E2ETests")]
	[AllureSuite("E2ESuite")]
	public class E2ETests
	{
		AppDbContext _dbContext;
		
		IBookRepository _bookRepository;
		IBookService _bookService;

		IBookshelfRepository _bookshelfRepository;
		IBookshelfService _bookshelfService;

		IUserRepository _userRepository;
		IUserService _userService;

		public E2ETests()
		{
			_dbContext = new DbContext().GetDbContext();

			_bookRepository = new BookRepository(_dbContext);
			_bookService = new BookService(_bookRepository);

			_bookshelfRepository = new BookshelfRepository(_dbContext);
			_bookshelfService = new BookshelfService(_bookshelfRepository);

			_userRepository = new UserRepository(_dbContext);
			_userService = new UserService(_userRepository);
		}

		[AllureXunit]
		public void TestAdd()
		{
			var transaction = _dbContext.Database.BeginTransaction();

			User user = new User
			{
				Login = "alina",
				Password = "alina2606",
				Permission = "user"
			};

			Book book = new Book
			{
				Name = "name_1",
				Genre = "genre_1",
				Language = "language_1",
				Year = 1,
				Rating = 1,
			};


			_userService.Add(user);

			Bookshelf bookshelf = new Bookshelf
			{
				IdUser = _userService.GetByLogin(user.Login).Id,
				Number = 0,
				Rating = 0
			};

			_bookshelfService.Add(bookshelf);

			_bookshelfService.AddBook(
				new BookshelfBook {
					IdBookshelf = _bookshelfService.GetByIdUser(bookshelf.IdUser).Id,
					IdBook = _bookService.GetByName(book.Name).Id,
					IsRead = false});

			var getted_books = _bookshelfService.GetBooksByIdBookshelf(
				_bookshelfService.GetByIdUser(bookshelf.IdUser).Id);

			Assert.Equal(book.Name, getted_books.First().Name);
			Assert.Equal(book.Genre, getted_books.First().Genre);
			Assert.Equal(book.Language, getted_books.First().Language);
			Assert.Equal(book.Year, getted_books.First().Year);
			Assert.Equal(book.Rating, getted_books.First().Rating);

			transaction.Rollback();
		}
	}
}