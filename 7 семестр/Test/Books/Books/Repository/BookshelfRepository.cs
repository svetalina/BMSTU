using Books.Interfaces;
using Books.Models;
using System.Data;

namespace Books.Repository
{
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

        public void Update(Bookshelf model)
        {
			throw new NotImplementedException();
		}

        public void Delete(int id)
        {
			throw new NotImplementedException();
		}

		public Bookshelf GetById(int id)
		{
			throw new NotImplementedException();
		}


		public IEnumerable<Bookshelf> GetAll()
        {
		    throw new NotImplementedException();
		}

		public Bookshelf GetByIdUser(int idUser)
		{
			return _appDBContext.Bookshelf.FirstOrDefault(elem => elem.IdUser == idUser);
		}


		public BookshelfBook GetBookshelfBookByIds(int idBookshelf, int idBook)
        {
            return _appDBContext.BookshelfBook.FirstOrDefault(
                book => book.IdBookshelf == idBookshelf && book.IdBook == idBook);
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


        public void AddBook(BookshelfBook model)
        {
            try
            {
                _appDBContext.BookshelfBook.Add(model);
                _appDBContext.SaveChanges();
            }
            catch (Exception)
            {
                throw new Exception("Ошибка при добавлении книги на книжную полку");
            }
        }

		public void UpdateBook(BookshelfBook model)
		{
			try
			{
				_appDBContext.BookshelfBook.Update(model);
				_appDBContext.SaveChanges();
			}
			catch (Exception)
			{
				throw new Exception("Ошибка при обновлении книги на книжной полке");
			}
		}

		public void DeleteBook(BookshelfBook model)
		{
			try
			{
				_appDBContext.BookshelfBook.Remove(model);
				_appDBContext.SaveChanges();
			}
			catch (Exception)
			{
				throw new Exception("Ошибка при удалении книги с книжной полки");
			}
		}
	}
}
