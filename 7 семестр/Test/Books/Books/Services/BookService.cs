using Books.Models;
using Books.Interfaces;
using Books.ViewModels;

namespace Books.Services
{
    public class BookService : IBookService
    {
		private readonly IBookRepository _bookRepository;

        public BookService(IBookRepository bookRepository)
        {
            _bookRepository = bookRepository;
        }


        private bool IsExist(Book book)
        {
            return _bookRepository.GetAll().FirstOrDefault(elem =>
                    elem.Name == book.Name) != null;
        }

        private bool IsNotExist(int id)
        {
            return _bookRepository.GetById(id) == null;
        }

		public void Add(Book book)
        {
            if (IsExist(book))
                throw new Exception("Такая книга уже существует");

            _bookRepository.Add(book);
        }

        public void Update(Book book)
        {
            if (IsNotExist(book.Id))
                throw new Exception("Такой книги не существует");

            _bookRepository.Update(book);
        }   

        public void Delete(Book book)
        {
            if (IsNotExist(book.Id))
                throw new Exception("Такой книги не существует");

            _bookRepository.Delete(book.Id);
        }

		
        public IEnumerable<Book> GetAll()
        {
			return _bookRepository.GetAll();
		}


        public Book GetByName(string name)
        {			
            return _bookRepository.GetByName(name);
        }


		public IEnumerable<Book> GetByParameters(Book parameters, 
                                                 SearchFlag yearFlag, 
                                                 SearchFlag ratingFlag)
        {
			var books = _bookRepository.GetAll();

            if (books.Count() != 0 && parameters.Name != null)
				books = books.Where(elem => elem.Name == parameters.Name);

            if (books.Count() != 0 && parameters.Genre != null)
				books = books.Where(elem => elem.Genre == parameters.Genre);

            if (books.Count() != 0 && parameters.Language != null)
				books = books.Where(elem => elem.Language == parameters.Language);

			if (books.Count() != 0 && parameters.Year != 0)
			{
				if (yearFlag == SearchFlag.Equal)
					books = books.Where(elem => elem.Year == parameters.Year);
				if (yearFlag == SearchFlag.More)
					books = books.Where(elem => elem.Year >= parameters.Year);
				if (yearFlag == SearchFlag.Less)
					books = books.Where(elem => elem.Year <= parameters.Year);
			}

			if (books.Count() != 0 && parameters.Rating != 0)
			{
				if (ratingFlag == SearchFlag.Equal)
					books = books.Where(elem => elem.Rating == parameters.Rating);
				if (ratingFlag == SearchFlag.More)
					books = books.Where(elem => elem.Rating >= parameters.Rating);
				if (ratingFlag == SearchFlag.Less)
					books = books.Where(elem => elem.Rating <= parameters.Rating);
			}

			return books;
        }
	}
}
