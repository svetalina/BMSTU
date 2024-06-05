using Books.Models;
using Books.Interfaces;

namespace Books.Repository
{
    public class BookRepository : IBookRepository
    {
        public BookRepository() { }

        public void Add(Book model)
        {
            throw new NotImplementedException();
        }

        public void Update(Book model)
        {
            throw new NotImplementedException();
        }

        public void Delete(int id)
        {
            throw new NotImplementedException();
        }

        public IEnumerable<Book> GetAll()
        {
            throw new NotImplementedException();
        }

        public Book GetByID(int id)
        {
            throw new NotImplementedException();
        }

        public Book GetByName(string name)
        {
            throw new NotImplementedException();
        }

        public IEnumerable<Book> GetByGenre(string genre)
        {
            throw new NotImplementedException();
        }

        public IEnumerable<Book> GetByLanguage(string language)
        {
            throw new NotImplementedException();
        }

        public IEnumerable<Book> GetByRating(uint rating)
        {
            throw new NotImplementedException();
        }

        public IEnumerable<Book> GetByAuthor(string author)
        {
            throw new NotImplementedException();
        }

        public IEnumerable<Book> GetBySeries(string series)
        {
            throw new NotImplementedException();
        }

        public IEnumerable<Book> GetByBookshelf(string bookshelf)
        {
            throw new NotImplementedException();
        }
    }
}
