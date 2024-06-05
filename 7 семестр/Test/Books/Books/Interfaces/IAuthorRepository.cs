using Books.Models;

namespace Books.Interfaces
{
    public interface IAuthorRepository : IRepository<Author>
    {
		Author GetByName(string name);
	}
}
