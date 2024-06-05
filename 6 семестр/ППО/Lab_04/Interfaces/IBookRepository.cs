using Books.Models;

namespace Books.Interfaces
{
    public interface IBookRepository : IRepository<Book>
    {
        Book GetByName(string name);

        IEnumerable<Book> GetByGenre(string genre);

        IEnumerable<Book> GetByLanguage(string language);

        IEnumerable<Book> GetByRating(int rating);


        IEnumerable<Book> GetByAuthor(string author);
        IEnumerable<Book> GetBySeries(string series);
        IEnumerable<Book> GetByBookshelf(string bookshelf);
    }
}