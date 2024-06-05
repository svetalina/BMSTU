using Books.Models;

namespace Books.Interfaces
{
    public interface IBookRepository : IRepository<Book>
    {
		Book GetByName(string name);

		IEnumerable<Author> GetAuthors(int idBook);
	}
}