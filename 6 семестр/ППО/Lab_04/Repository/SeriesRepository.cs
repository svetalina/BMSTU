using Books.Interfaces;
using Books.Models;

namespace Books.Repository
{
    public class SeriesRepository : ISeriesRepository
    {
        private readonly AppDBContext _appDBContext;

        public SeriesRepository(AppDBContext appDBContext)
        {
            _appDBContext = appDBContext;
        }

        public void Add(Series model)
        {
            try
            {
                _appDBContext.Series.Add(model);
                _appDBContext.SaveChanges();
            }
            catch (Exception)
            {
                throw new Exception("Ошибка при добавлении серии");
            }
        }

        public void Update(Series model)
        {
            try
            {
                _appDBContext.Series.Update(model);
                _appDBContext.SaveChanges();
            }
            catch (Exception)
            {
                throw new Exception("Ошибка при обновлении серии");
            }
        }

        public void Delete(int id)
        {
            try
            {
                Series series = _appDBContext.Series.Find(id);

                if (series != null)
                {
                    _appDBContext.Series.Remove(series);
                    _appDBContext.SaveChanges();
                }
            }
            catch (Exception)
            {
                throw new Exception("Ошибка при удалении серии");
            }
        }

        public IEnumerable<Series> GetAll()
        {
            return _appDBContext.Series.ToList();
        }

        public Series GetById(int id)
        {
            return _appDBContext.Series.Find(id);
        }

        public Series GetByName(string name)
        {
            return _appDBContext.Series.FirstOrDefault(elem => elem.Name == name);
        }


        public IEnumerable<Series> GetByGenre(string genre)
        {
            return _appDBContext.Series.Where(elem => elem.Genre == genre).ToList();
        }

        public IEnumerable<Series> GetByPublisher(string publisher)
        {
            return _appDBContext.Series.Where(elem => elem.Publisher == publisher).ToList();
        }

        public IEnumerable<Series> GetByYear(int year)
        {
            return _appDBContext.Series.Where(elem => elem.Year == year).ToList();
        }

        public IEnumerable<Series> GetByRating(int rating)
        {
            return _appDBContext.Series.Where(elem => elem.Rating == rating).ToList();
        }
    }
}
