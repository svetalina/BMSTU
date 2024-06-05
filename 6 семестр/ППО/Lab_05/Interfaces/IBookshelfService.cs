using Books.Models;

namespace Books.Interfaces
{
    public interface IBookshelfService : IService<Bookshelf>
    {
        Bookshelf GetByName(string name);
    }
}