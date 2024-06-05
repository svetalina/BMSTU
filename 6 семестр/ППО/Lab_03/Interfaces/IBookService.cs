using Books.Models;
using Books.Services;

namespace Books.Interfaces
{
    public interface IBookService : IService<Book>
    {
        Book GetByName(string name);
        IEnumerable<Book> GetByGenre(string genre);
        IEnumerable<Book> GetByLanguage(string language);
        IEnumerable<Book> GetByRating(uint rating);

        IEnumerable<Book> GetByAuthor(string author);
        IEnumerable<Book> GetBySeries(string services);
        IEnumerable<Book> GetByBookshelf(string bookshelf);

        IEnumerable<Book> GetByParameters(string name, string genre, string language,
                                          uint minRating, uint maxRating);
        IEnumerable<Book> GetSortBooksByOrder(IEnumerable<Book> players, BookSortOrder sortOrder);
    }
}
