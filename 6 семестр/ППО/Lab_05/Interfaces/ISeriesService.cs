using Books.Models;
using Books.Services;

namespace Books.Interfaces
{
    public interface ISeriesService : IService<Series>
    {
        Series GetByName(string name);
        IEnumerable<Series> GetByGenre(string genre);
        IEnumerable<Series> GetByPublisher(string publisher);
        IEnumerable<Series> GetByYear(int year);
        IEnumerable<Series> GetByRating(int rating);

        IEnumerable<Series> GetByParameters(string name, string genre, string publisher,
                                                    int minYear, int maxYear,
                                                    int minRating, int maxRating);
        IEnumerable<Series> GetSortSeriesByOrder(IEnumerable<Series> series, SeriesSortOrder sortOrder);
    }
}
