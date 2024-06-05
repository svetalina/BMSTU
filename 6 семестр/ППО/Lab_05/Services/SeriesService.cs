using Books.Interfaces;
using Books.Models;

namespace Books.Services
{
    public class SeriesService : ISeriesService
    {

        private readonly ISeriesRepository _seriesRepository;

        public SeriesService(ISeriesRepository seriesRepository)
        {
            _seriesRepository = seriesRepository;
        }


        private bool IsExist(Series series)
        {
            return _seriesRepository.GetAll().FirstOrDefault(elem =>
                    elem.Name == series.Name) != null;
        }

        private bool IsNotExist(int id)
        {
            return _seriesRepository.GetById(id) == null;
        }


        public void Add(Series series)
        {
            if (IsExist(series))
                throw new Exception("Такая серия уже существует");

            _seriesRepository.Add(series);
        }

        public void Update(Series series)
        {
            if (IsNotExist(series.Id))
                throw new Exception("Такой серии не существует");

            _seriesRepository.Update(series);
        }

        public void Delete(Series series)
        {
            if (IsNotExist(series.Id))
                throw new Exception("Такой серии не существует");

            _seriesRepository.Delete(series.Id);
        }


        public IEnumerable<Series> GetAll()
        {
            return _seriesRepository.GetAll();
        }

        public Series GetById(int id)
        {
            return _seriesRepository.GetById(id);
        }

        public Series GetByName(string name)
        {
            return _seriesRepository.GetByName(name);
        }

        public IEnumerable<Series> GetByGenre(string genre)
        {
            return _seriesRepository.GetByGenre(genre);
        }

        public IEnumerable<Series> GetByPublisher(string publisher)
        {
            return _seriesRepository.GetByPublisher(publisher);
        }

        public IEnumerable<Series> GetByYear(int rating)
        {
            return _seriesRepository.GetByYear(rating);
        }

        public IEnumerable<Series> GetByRating(int rating)
        {
            return _seriesRepository.GetByRating(rating);
        }

        public IEnumerable<Series> GetByParameters(string name, string genre, string publisher,
                                                    int minYear, int maxYear,
                                                    int minRating, int maxRating)
        {
            IEnumerable<Series> series = _seriesRepository.GetAll();

            if (series.Count() != 0 && name != null)
                series = series.Where(elem => elem.Name == name);

            if (series.Count() != 0 && genre != null)
                series = series.Where(elem => elem.Genre == genre);

            if (series.Count() != 0 && publisher != null)
                series = series.Where(elem => elem.Publisher == publisher);

            if (series.Count() != 0 && minYear != 0)
                series = series.Where(elem => elem.Year >= minYear);

            if (series.Count() != 0 && maxYear != 0)
                series = series.Where(elem => elem.Year <= maxYear);

            if (series.Count() != 0 && minRating != 0)
                series = series.Where(elem => elem.Rating >= minRating);

            if (series.Count() != 0 && maxRating != 0)
                series = series.Where(elem => elem.Rating <= maxRating);

            return series;
        }

        public IEnumerable<Series> GetSortSeriesByOrder(IEnumerable<Series> series, SeriesSortOrder sortOrder)
        {
            IEnumerable<Series> sortedSeriess = sortOrder switch
            {
                SeriesSortOrder.IdAsc => series.OrderBy(elem => elem.Id),
                SeriesSortOrder.IdDesc => series.OrderByDescending(elem => elem.Id),

                SeriesSortOrder.NameAsc => series.OrderBy(elem => elem.Name),
                SeriesSortOrder.NameDesc => series.OrderByDescending(elem => elem.Name),

                SeriesSortOrder.GenreAsc => series.OrderBy(elem => elem.Genre),
                SeriesSortOrder.GenreDesc => series.OrderByDescending(elem => elem.Genre),

                SeriesSortOrder.PublisherAsc => series.OrderBy(elem => elem.Publisher),
                SeriesSortOrder.PublisherDesc => series.OrderByDescending(elem => elem.Publisher),

                SeriesSortOrder.YearAsc => series.OrderBy(elem => elem.Year),
                SeriesSortOrder.YearDesc => series.OrderByDescending(elem => elem.Year),

                SeriesSortOrder.RatingAsc => series.OrderBy(elem => elem.Rating),
                SeriesSortOrder.RatingDesc => series.OrderByDescending(elem => elem.Rating),

            };

            return sortedSeriess;
        }
    }
}
