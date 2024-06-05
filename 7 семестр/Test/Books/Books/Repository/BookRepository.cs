using Books.Models;
using Books.Interfaces;
using Microsoft.EntityFrameworkCore;

namespace Books.Repository
{
    public class BookRepository : IBookRepository
    {
        private readonly AppDbContext _appDBContext;

        public BookRepository(AppDbContext appDBContext)
        {
            _appDBContext = appDBContext;
        }

        public void Add(Book model)
        {
            try
            {
                _appDBContext.Book.Add(model);
                _appDBContext.SaveChanges();
            }
            catch (Exception)
            {
                throw new Exception("Ошибка при добавлении книги");
            }
        }

        public void Update(Book model)
        {
            try
            {
                var curModel = _appDBContext.Book.FirstOrDefault(elem => elem.Id == model.Id);
                _appDBContext.Entry(curModel).CurrentValues.SetValues(model);
                
                _appDBContext.SaveChanges();
            }
            catch (Exception)
            {
                throw new Exception("Ошибка при обновлении книги");
            }
        }

        public void Delete(int id)
        {
            try
            {
                Book book = _appDBContext.Book.Find(id);

                _appDBContext.Book.Remove(book);
                _appDBContext.SaveChanges();
            }
            catch (Exception)
            {
                throw new Exception("Ошибка при удалении книги");
            }
        }

        public Book GetById(int id)
        {
            return _appDBContext.Book.Find(id);
        }

		public IEnumerable<Book> GetAll()
		{
			return _appDBContext.Book.ToList();
		}

		public Book GetByName(string name)
        {
			return _appDBContext.Book.FirstOrDefault(elem => elem.Name == name);
        }

		public IEnumerable<Author> GetAuthors(int idBook)
		{
			return _appDBContext.Book
				.Where(b => b.Id == idBook)
				.Join(_appDBContext.BookAuthor, b => b.Id, ba => ba.IdBook, (b, ba) => new { Book = b, BookAuthor = ba })
				.Join(_appDBContext.Author, ab => ab.BookAuthor.IdAuthor, a => a.Id, (ab, a) => a)
				.ToList();
		}
	}
}
