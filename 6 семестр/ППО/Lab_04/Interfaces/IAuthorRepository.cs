using Books.Models;

namespace Books.Interfaces
{
    public interface IAuthorRepository : IRepository<Author>
    {
        Author GetByName(string name);

        IEnumerable<Author> GetByYearBirth(int yearBirth);

        IEnumerable<Author> GetByYearDeath(int yearDeath);

        IEnumerable<Author> GetByCountry(string country);

        IEnumerable<Author> GetByLanguage(string language);

        IEnumerable<Author> GetByGenre(string genre);
    }
}
