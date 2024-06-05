using Books.Models;

namespace IntegrationTests.DataBuilder
{
	public class BookBuilder
	{
		private Book _book;

		public BookBuilder()
		{
			_book = new Book();
		}

		public BookBuilder WithId(int id)
		{
			_book.Id = id;
			return this;
		}

		public BookBuilder WithName(string name)
		{
			_book.Name = name;
			return this;
		}

		public BookBuilder WithGenre(string genre)
		{
			_book.Genre = genre;
			return this;
		}

		public BookBuilder WithYear(int year)
		{
			_book.Year = year;
			return this;
		}

		public BookBuilder WithLanguage(string language)
		{
			_book.Language = language;
			return this;
		}

		public BookBuilder WithRating(double rating)
		{
			_book.Rating = rating;
			return this;
		}

		public Book Build()
		{
			return _book;
		}
	}

	public class BookAuthorBuilder
	{
		private BookAuthor _bookAuthor;

		public BookAuthorBuilder()
		{
			_bookAuthor = new BookAuthor();
		}

		public BookAuthorBuilder WithIdBook(int idBook)
		{
			_bookAuthor.IdBook = idBook;
			return this;
		}

		public BookAuthorBuilder WithIdAuthor(int idAuthor)
		{
			_bookAuthor.IdAuthor = idAuthor;
			return this;
		}

		public BookAuthor Build()
		{
			return _bookAuthor;
		}
	}

}
