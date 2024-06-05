using Books.Models;
using Books.Interfaces;
using Microsoft.EntityFrameworkCore;

namespace Books.Repository
{
    public class BookRepository : IBookRepository
    {
        private readonly AppDBContext _appDBContext;

        public BookRepository(AppDBContext appDBContext)
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

                if (book != null)
                {
                    _appDBContext.Book.Remove(book);
                    _appDBContext.SaveChanges();
                }
            }
            catch (Exception)
            {
                throw new Exception("Ошибка при удалении книги");
            }
        }


        public IEnumerable<Book> GetAll()
        {
            return _appDBContext.Book.ToList();
        }

        public Book GetById(int id)
        {
            return _appDBContext.Book.Find(id);
        }

        public Book GetByName(string name)
        {
            return _appDBContext.Book.FirstOrDefault(elem => elem.Name == name);
        }

        public IEnumerable<Book> GetByGenre(string genre)
        {
            return _appDBContext.Book.Where(elem => elem.Genre == genre).ToList();
        }

        public IEnumerable<Book> GetByLanguage(string language)
        {
            return _appDBContext.Book.Where(elem => elem.Language == language).ToList();
        }

        public IEnumerable<Book> GetByRating(int rating)
        {
            return _appDBContext.Book.Where(elem => elem.Rating == rating).ToList();
        }

        public IEnumerable<Book> GetByAuthor(string author)
        {
            return _appDBContext.Author
                .Where(a => a.Name == author)
                .Join(_appDBContext.BookAuthor, a => a.Id, ba => ba.IdAuthor, (a, ba) => new { Author = a, BookAuthor = ba })
                .Join(_appDBContext.Book, ab => ab.BookAuthor.IdBook, b => b.Id, (ab, b) => new { Author = ab.Author, Book = b })
                .Select(ab => ab.Book)
                .ToList();
        }

        public IEnumerable<Book> GetBySeries(string series)
        {
            return _appDBContext.Series
                .Where(s => s.Name == series)
                .Join(_appDBContext.BookSeries, s => s.Id, bs => bs.IdSeries, (s, bs) => new { Series = s, BookSeries = bs })
                .Join(_appDBContext.Book, sb => sb.BookSeries.IdBook, b => b.Id, (sb, b) => new { Series = sb.Series, Book = b })
                .Select(sb => sb.Book)
                .ToList();
        }

        public IEnumerable<Book> GetByBookshelf(string bookshelf)
        {
            return _appDBContext.Bookshelf
                .Where(sh => sh.Name == bookshelf)
                .Join(_appDBContext.BookBookshelf, sh => sh.Id, bsh => bsh.IdBookshelf, (sh, bsh) => new { Bookshelf = sh, BookBookshelf = bsh })
                .Join(_appDBContext.Book, shb => shb.BookBookshelf.IdBook, b => b.Id, (shb, b) => new { Bookshelf = shb.Bookshelf, Book = b })
                .Select(shb => shb.Book)
                .ToList();
        }
    }
}
