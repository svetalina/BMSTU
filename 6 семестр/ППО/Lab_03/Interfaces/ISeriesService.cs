using Books.Models;
using Books.Services;

namespace Books.Interfaces
{
    public interface ISeriesService : IService<Series>
    {
        Series GetByName(string name);
        IEnumerable<Series> GetByGenre(string genre);
        IEnumerable<Series> GetByPublisher(string publisher);
        IEnumerable<Series> GetByYear(uint year);
        IEnumerable<Series> GetByRating(uint rating);

        IEnumerable<Series> GetByParameters(string name, string genre, string publisher,
                                                    uint minYear, uint maxYear,
                                                    uint minRating, uint maxRating);
        IEnumerable<Series> GetSortSeriesByOrder(IEnumerable<Series> series, SeriesSortOrder sortOrder);
    }
}
