﻿using Books.Models;

namespace Books.Repository
{
    public interface ISeriesRepository
    {
        public Series Add(Series model);
        public Series Update(Series model);

        public IEnumerable<Series> GetAll();
        public Series GetById(int id);
        public Series GetByName(string name);

	}

	public class SeriesRepository : ISeriesRepository
    {
        private readonly AppDbContext _appDBContext;

        public SeriesRepository(AppDbContext appDBContext)
        {
            _appDBContext = appDBContext;
        }

        public Series Add(Series model)
        {
            try
            {
                _appDBContext.Series.Add(model);
                _appDBContext.SaveChanges();

				return _appDBContext.Series.FirstOrDefault(elem => elem.Id == model.Id);
			}
            catch (Exception)
            {
                throw new Exception("Ошибка при добавлении серии");
            }
		}

        public Series Update(Series model)
        {
            try
            {
				var curModel = _appDBContext.Series.FirstOrDefault(elem => elem.Id == model.Id);
				_appDBContext.Entry(curModel).CurrentValues.SetValues(model);

				_appDBContext.SaveChanges();

				return _appDBContext.Series.FirstOrDefault(elem => elem.Id == model.Id);
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

                _appDBContext.Series.Remove(series);
                _appDBContext.SaveChanges();
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
    }
}
