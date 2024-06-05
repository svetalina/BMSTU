using Books.Models;

namespace Books.Interfaces
{
    public interface IBookshelfRepository : IRepository<Bookshelf>
    {
        Bookshelf GetByName(string name);
    }
}
