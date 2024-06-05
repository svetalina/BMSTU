using Books.Models;

namespace IntegrationTests.ObjectMother
{
	public class UserObjectMother
	{
		public User User_1()
		{
			var user = new User();
			user.Login = "login_1";
			user.Password = "password_1";
			user.Permission = "user";
			return user;
		}

		public User User_2()
		{
			var user = new User();
			user.Login = "login_2";
			user.Password = "password_2";
			user.Permission = "user";
			return user;
		}
	}

	public class AuthorObjectMother
	{
		public Author Author_1()
		{
			var author = new Author();
			author.Name = "name_1";
			author.Genre = "genre_1";
			author.Country = "country_1";
			author.YearBirth = 1;
			author.YearDeath = 1;
			return author;
		}

		public Author Author_2()
		{
			var author = new Author();
			author.Name = "name_2";
			author.Genre = "genre_2";
			author.Country = "country_2";
			author.YearBirth = 2;
			author.YearDeath = 2;
			return author;
		}
	}

	public class BookObjectMother
	{
		public Book Book_1()
		{
			var book = new Book();
			book.Name = "name_1";
			book.Genre = "genre_1";
			book.Language = "language_1";
			book.Year = 1;
			book.Rating = 1;
			return book;
		}

		public Book Book_2()
		{
			var book = new Book();
			book.Name = "name_2";
			book.Genre = "genre_2";
			book.Language = "language_2";
			book.Year = 2;
			book.Rating = 2;
			return book;
		}

		public BookAuthor BookAuthor_1()
		{
			var bookAuthor = new BookAuthor();
			bookAuthor.IdBook = 1;
			bookAuthor.IdAuthor = 1;
			return bookAuthor;
		}
	}

	public class SeriesObjectMother
	{
		public Series Series_1()
		{
			var series = new Series();
			series.Name = "name_1";
			series.Genre = "genre_1";
			series.Publisher = "publisher_1";
			series.Year = 1;
			series.Rating = 1;
			return series;
		}

		public Series Series_2()
		{
			var series = new Series();
			series.Name = "name_2";
			series.Genre = "genre_2";
			series.Publisher = "publisher_2";
			series.Year = 2;
			series.Rating = 2;
			return series;
		}
	}

	public class BookshelfObjectMother
	{
		public Bookshelf Bookshelf_1()
		{
			var bookshelf = new Bookshelf();
			bookshelf.IdUser = 1;
			bookshelf.Number = 0;
			bookshelf.Rating = 0;
			return bookshelf;
		}

		public BookshelfBook BookshelfBook_1()
		{
			var bookshelfBook = new BookshelfBook();
			bookshelfBook.IdBookshelf = 1;
			bookshelfBook.IdBook = 1;
			bookshelfBook.IsRead = false;
			return bookshelfBook;
		}

		public BookshelfBook BookshelfBook_2()
		{
			var bookshelfBook = new BookshelfBook();
			bookshelfBook.IdBookshelf = 1;
			bookshelfBook.IdBook = 2;
			bookshelfBook.IsRead = true;
			return bookshelfBook;
		}
	}
}
