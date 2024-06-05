using Books.Interfaces;
using Books.Models;

namespace Books.Repository
{
    public class BookshelfRepository : IBookshelfRepository
    {
        private readonly AppDBContext _appDBContext;

        public BookshelfRepository(AppDBContext appDBContext)
        {
            _appDBContext = appDBContext;
        }

        public void Add(Bookshelf model)
        {
            try
            {
                _appDBContext.Bookshelf.Add(model);
                _appDBContext.SaveChanges();
            }
            catch (Exception)
            {
                throw new Exception("Ошибка при добавлении книжной полки");
            }
        }

        public void Update(Bookshelf model)
        {
            try
            {
                _appDBContext.Bookshelf.Update(model);
                _appDBContext.SaveChanges();
            }
            catch (Exception)
            {
                throw new Exception("Ошибка при обновлении книжной полки");
            }
        }

        public void Delete(int id)
        {
            try
            {
                Bookshelf bookshelf = _appDBContext.Bookshelf.Find(id);

                if (bookshelf != null)
                {
                    _appDBContext.Bookshelf.Remove(bookshelf);
                    _appDBContext.SaveChanges();
                }
            }
            catch (Exception)
            {
                throw new Exception("Ошибка при удалении книжной полки");
            }
        }


        public IEnumerable<Bookshelf> GetAll()
        {
            return _appDBContext.Bookshelf.ToList();
        }

        public Bookshelf GetById(int id)
        {
            return _appDBContext.Bookshelf.Find(id);
        }

        public Bookshelf GetByName(string name)
        {
            return _appDBContext.Bookshelf.FirstOrDefault(elem => elem.Name == name);
        }
    }
}
