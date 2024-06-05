using Books.Models;
using Books.Services;

namespace Books.Interfaces
{
    public interface IAuthorService : IService<Author>
    {
        Author GetByName(string name);
        IEnumerable<Author> GetByYearBirth(int yearBirth);
        IEnumerable<Author> GetByYearDeath(int yearDeath);
        IEnumerable<Author> GetByCountry(string country);
        IEnumerable<Author> GetByLanguage(string language);
        IEnumerable<Author> GetByGenre(string genre);


        IEnumerable<Author> GetByParameters(string name, int yearBirth, int yaerDeath,
                                            string country, string language, string genre);
        IEnumerable<Author> GetSortAuthorsByOrder(IEnumerable<Author> players, AuthorSortOrder sortOrder);
    }
}
