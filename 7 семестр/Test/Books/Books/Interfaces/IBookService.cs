using Books.Models;
using Books.ViewModels;

namespace Books.Interfaces
{
    public interface IBookService : IService<Book>
    {
		Book GetByName(string name);

		IEnumerable<Book> GetByParameters(Book parameters,
										  SearchFlag yearFlag = SearchFlag.Equal,
										  SearchFlag ratingFlag = SearchFlag.Equal);
	}
}
