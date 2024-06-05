using Books.Models;

namespace Books.Repository
{
	public interface IBookRepository
	{
		Book Add(Book model);
		Book Update(Book model);


		IEnumerable<Book> GetAll();
		Book GetById(int id);
		Book GetByName(string name);
	}

	public class BookRepository : IBookRepository
	{
		private readonly AppDbContext _appDbContext;

		public BookRepository(AppDbContext appDbContext)
		{
			_appDbContext = appDbContext;
		}

		public Book Add(Book model)
		{
			try
			{
				_appDbContext.Book.Add(model);
				_appDbContext.SaveChanges();

				return _appDbContext.Book.FirstOrDefault(elem => elem.Id == model.Id);
			}
			catch (Exception)
			{
				throw new Exception("Ошибка при добавлении книги");
			}
		}

		public Book Update(Book model)
		{
			try
			{
				var curModel = _appDbContext.Book.FirstOrDefault(elem => elem.Id == model.Id);
				_appDbContext.Entry(curModel).CurrentValues.SetValues(model);
				
				_appDbContext.SaveChanges();

				return _appDbContext.Book.FirstOrDefault(elem => elem.Id == model.Id);

			}
			catch (Exception)
			{
				throw new Exception("Ошибка при обновлении книги");
			}
		}

		public void Delete(int id)
		{
			try
			{
				Book book = _appDbContext.Book.Find(id);

				_appDbContext.Book.Remove(book);
				_appDbContext.SaveChanges();
			}
			catch (Exception)
			{
				throw new Exception("Ошибка при удалении книги");
			}
		}

		public IEnumerable<Book> GetAll()
		{
			return _appDbContext.Book.ToList();
		}

		public Book GetById(int id)
		{
			return _appDbContext.Book.Find(id);
		}

		public Book GetByName(string name)
		{
			return _appDbContext.Book.FirstOrDefault(elem => elem.Name == name);
		}
	}
}

