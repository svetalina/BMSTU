using Books.Models;

namespace Books.Interfaces
{
    public interface ISeriesRepository : IRepository<Series>
    {
        Series GetByName(string name);

        IEnumerable<Series> GetByGenre(string genre);

        IEnumerable<Series> GetByPublisher(string language);

        IEnumerable<Series> GetByYear(uint rating);

        IEnumerable<Series> GetByRating(uint rating);
       
    }
}
