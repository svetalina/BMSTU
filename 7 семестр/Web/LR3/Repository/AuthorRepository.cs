using Books.Models;

namespace Books.Repository
{
    public interface IAuthorRepository
    {
		public Author Add(Author model);
		public Author Update(Author model);

        public IEnumerable<Author> GetAll();
        public Author GetById(int id);
        public Author GetByName(string name);
	}


	public class AuthorRepository : IAuthorRepository
    {
        private readonly AppDbContext _appDBContext;

        public AuthorRepository(AppDbContext appDBContext)
        {
            _appDBContext = appDBContext;
        }

        public Author Add(Author model)
        {
            try
            {
                _appDBContext.Author.Add(model);
                _appDBContext.SaveChanges();

				return _appDBContext.Author.FirstOrDefault(elem => elem.Id == model.Id);
			}
            catch (Exception)
            {
                throw new Exception("Ошибка при добавлении автора");
            }
        }

        public Author Update(Author model)
        {
			try
			{
				var curModel = _appDBContext.Author.FirstOrDefault(elem => elem.Id == model.Id);
				_appDBContext.Entry(curModel).CurrentValues.SetValues(model);

				_appDBContext.SaveChanges();

				return _appDBContext.Author.FirstOrDefault(elem => elem.Id == model.Id);
			}
			catch (Exception)
			{
				throw new Exception("Ошибка при обновлении автора");
			}
		}

        public void Delete(int id)
        {
            try
            {
                Author author = _appDBContext.Author.Find(id);

                _appDBContext.Author.Remove(author);
                _appDBContext.SaveChanges();
            }
            catch (Exception)
            {
                throw new Exception("Ошибка при удалении автора");
            }
        }

		public IEnumerable<Author> GetAll()
		{
			return _appDBContext.Author.ToList();
		}


		public Author GetById(int id)
        {
            return _appDBContext.Author.Find(id);
        }

		public Author GetByName(string name)
        {
            return _appDBContext.Author.FirstOrDefault(elem => elem.Name == name);
        }
    }
}
