using Books.Models;
using Books.Services;

namespace Books.Interfaces
{
    public interface IAuthorService : IService<Author>
    {
        Author GetByName(string name);
        IEnumerable<Author> GetByYearBirth(uint yearBirth);
        IEnumerable<Author> GetByYearDeath(uint yearDeath);
        IEnumerable<Author> GetByCountry(string country);
        IEnumerable<Author> GetByLanguage(string language);
        IEnumerable<Author> GetByGenre(string genre);


        IEnumerable<Author> GetByParameters(string name, uint yearBirth, uint yaerDeath,
                                            string country, string language, string genre);
        IEnumerable<Author> GetSortAuthorsByOrder(IEnumerable<Author> players, AuthorSortOrder sortOrder);
    }
}
