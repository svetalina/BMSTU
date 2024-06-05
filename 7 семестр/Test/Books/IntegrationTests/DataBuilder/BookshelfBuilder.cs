using Books.Models;

namespace IntegrationTests.DataBuilder
{
	public class BookshelfBuilder
	{
		private Bookshelf _bookshelf;

		public BookshelfBuilder()
		{
			_bookshelf = new Bookshelf();
		}

		public BookshelfBuilder WithId(int id)
		{
			_bookshelf.Id = id;
			return this;
		}

		public BookshelfBuilder WithIdUser(int idUser)
		{
			_bookshelf.IdUser = idUser;
			return this;
		}

		public BookshelfBuilder WithNumber(int number)
		{
			_bookshelf.Number = number;
			return this;
		}

		public BookshelfBuilder WithRating(double rating)
		{
			_bookshelf.Rating = rating;
			return this;
		}

		public Bookshelf Build()
		{
			return _bookshelf;
		}
	}

	public class BookshelfBookBuilder
	{
		private BookshelfBook _bookshelfBook;

		public BookshelfBookBuilder()
		{
			_bookshelfBook = new BookshelfBook();
		}

		public BookshelfBookBuilder WithIdBookshelf(int idBookshelf)
		{
			_bookshelfBook.IdBookshelf = idBookshelf;
			return this;
		}

		public BookshelfBookBuilder WithIdBook(int idBook)
		{
			_bookshelfBook.IdBook = idBook;
			return this;
		}

		public BookshelfBookBuilder WithIsRead(bool isRead)
		{
			_bookshelfBook.IsRead = isRead;
			return this;
		}

		public BookshelfBook Build()
		{
			return _bookshelfBook;
		}
	}

}
