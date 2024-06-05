using Books.Models;

namespace Books.Repository
{
    public interface IBookshelfRepository
	{
		void Add(Bookshelf model);

		Bookshelf GetById(int id);
        List<Book> GetBooksByIdBookshelf(int idBookshelf);

        BookshelfBook GetBookshelfBookByIds(int idBookshelf, int idBook);
        BookshelfBook AddBook(BookshelfBook model);
		BookshelfBook UpdateBook(BookshelfBook model);
        BookshelfBook DeleteBook(BookshelfBook model);
	}

	public class BookshelfRepository : IBookshelfRepository
    {
        private readonly AppDbContext _appDBContext;

        public BookshelfRepository(AppDbContext appDBContext)
        {
            _appDBContext = appDBContext;
        }

        public void Add(Bookshelf model)
        {
			_appDBContext.Bookshelf.Add(model);
			_appDBContext.SaveChanges();
		}

        public Bookshelf GetById(int id)
        {
            return _appDBContext.Bookshelf.Find(id);
        }

		public Bookshelf GetByIdUser(int idUser)
		{
			return _appDBContext.Bookshelf.Find(idUser);
		}

		public List<Book> GetBooksByIdBookshelf(int idBookshelf)
        {
            return _appDBContext.Book
            .Join(
                _appDBContext.BookshelfBook,
                book => book.Id,
                bookshelfBook => bookshelfBook.IdBook,
                (book, bookshelfBook) => new { Book = book, BookshelfBook = bookshelfBook }
            )
            .Where(joinedData => joinedData.BookshelfBook.IdBookshelf == idBookshelf)
            .Select(joinedData => joinedData.Book)
            .ToList();
        }


		public BookshelfBook GetBookshelfBookByIds(int idBookshelf, int idBook)
		{
			return _appDBContext.BookshelfBook.FirstOrDefault(
				book => book.IdBookshelf == idBookshelf && book.IdBook == idBook);
		}


		public BookshelfBook AddBook(BookshelfBook model)
        {
            try
            {
                _appDBContext.BookshelfBook.Add(model);
                _appDBContext.SaveChanges();

				return _appDBContext.BookshelfBook.FirstOrDefault(
					b => b.IdBookshelf == model.IdBookshelf && b.IdBook == model.IdBook);

			}
            catch (Exception)
            {
                throw new Exception("Ошибка при добавлении книги на книжную полку");
            }
        }

		public BookshelfBook UpdateBook(BookshelfBook model)
		{
			try
			{
				_appDBContext.BookshelfBook.Update(model);
				_appDBContext.SaveChanges();

				return _appDBContext.BookshelfBook.FirstOrDefault(
				    b => b.IdBookshelf == model.IdBookshelf && b.IdBook == model.IdBook);
			}
			catch (Exception)
			{
				throw new Exception("Ошибка при обновлении книги на книжной полке");
			}
		}

		public BookshelfBook DeleteBook(BookshelfBook model)
		{
			try
			{
				_appDBContext.BookshelfBook.Remove(model);
				_appDBContext.SaveChanges();

                return model;
			}
			catch (Exception)
			{
				throw new Exception("Ошибка при удалении книги с книжной полки");
			}
		}
	}
}
