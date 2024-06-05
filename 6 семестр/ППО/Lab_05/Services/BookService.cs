using Books.Models;
using Books.Interfaces;
using static Books.Services.SortOrder;

namespace Books.Services
{
    public class BookService : IBookService
    {
        private readonly IBookRepository _bookRepository;

        public BookService(IBookRepository bookRepository)
        {
            _bookRepository = bookRepository;
        }


        private bool IsExist(Book book)
        {
            return _bookRepository.GetAll().FirstOrDefault(elem =>
                    elem.Name == book.Name) != null;
        }

        private bool IsNotExist(int id)
        {
            return _bookRepository.GetById(id) == null;
        }


        public void Add(Book book)
        {
            if (IsExist(book))
                throw new Exception("Такая книга уже существует");

            _bookRepository.Add(book);
        }

        public void Update(Book book)
        {
            if (IsNotExist(book.Id))
                throw new Exception("Такой книги не существует");

            _bookRepository.Update(book);
        }   

        public void Delete(Book book)
        {
            if (IsNotExist(book.Id))
                throw new Exception("Такой книги не существует");

            _bookRepository.Delete(book.Id);
        }


        public IEnumerable<Book> GetAll()
        {
            return _bookRepository.GetAll();
        }

        public Book GetById(int id)
        {
            return _bookRepository.GetById(id);
        }

        public Book GetByName(string name)
        {
            return _bookRepository.GetByName(name);
        }

        public IEnumerable<Book> GetByGenre(string genre)
        {
            return _bookRepository.GetByGenre(genre);
        }

        public IEnumerable<Book> GetByLanguage(string language)
        {
            return _bookRepository.GetByLanguage(language);
        }

        public IEnumerable<Book> GetByRating(int rating)
        {
            return _bookRepository.GetByRating(rating);
        }


        public IEnumerable<Book> GetByAuthor(string author)
        {
            return _bookRepository.GetByAuthor(author);
        }

        public IEnumerable<Book> GetBySeries(string series)
        {
            return _bookRepository.GetBySeries(series);
        }

        public IEnumerable<Book> GetByBookshelf(string bookshelf)
        {
            return _bookRepository.GetByBookshelf(bookshelf);
        }

        public IEnumerable<Book> GetByParameters(string name, string genre, 
                                                 string language, int minRating, 
                                                 int maxRating)
        {
            IEnumerable<Book> books = _bookRepository.GetAll();

            if (books.Count() != 0 && name != null)
                books = books.Where(elem => elem.Name == name);

            if (books.Count() != 0 && genre != null)
                books = books.Where(elem => elem.Genre == genre);

            if (books.Count() != 0 && language != null)
                books = books.Where(elem => elem.Language == language);

            if (books.Count() != 0 && minRating != 0)
                books = books.Where(elem => elem.Rating >= minRating);

            if (books.Count() != 0 && maxRating != 0)
                books = books.Where(elem => elem.Rating <= maxRating);

            return books;
        }

        public IEnumerable<Book> GetSortBooksByOrder(IEnumerable<Book> books, BookSortOrder sortOrder)
        {
            IEnumerable<Book> sortedbooks = sortOrder switch
            {
                BookSortOrder.IdAsc => books.OrderBy(elem => elem.Id),
                BookSortOrder.IdDesc => books.OrderByDescending(elem => elem.Id),

                BookSortOrder.NameAsc => books.OrderBy(elem => elem.Name),
                BookSortOrder.NameDesc => books.OrderByDescending(elem => elem.Name),

                BookSortOrder.GenreAsc => books.OrderBy(elem => elem.Genre),
                BookSortOrder.GenreDesc => books.OrderByDescending(elem => elem.Genre),

                BookSortOrder.LanguageAsc => books.OrderBy(elem => elem.Language),
                BookSortOrder.LanguageDesc => books.OrderByDescending(elem => elem.Language),

                BookSortOrder.RatingAsc => books.OrderBy(elem => elem.Rating),
                BookSortOrder.RatingDesc => books.OrderByDescending(elem => elem.Rating),

            };

            return sortedbooks;
        }
    }
}
