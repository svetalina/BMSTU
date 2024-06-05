using AutoMapper;
using Books.Models;
using Books.Enums;
using Books.ModelsBL;
using Books.Repository;

namespace Books.Services
{
	public interface IBookService
	{
		BookBL Add(BookBL book);
		BookBL Update(BookBL book);

		BookBL GetById(int id);
		BookBL GetByName(string name);

		IEnumerable<BookBL> GetByParameters(
			string? name, string? genre, string? language,
			int? year, int? rating,
			SearchFlag yearFlag, SearchFlag ratingFlag);
	}

	public class BookService : IBookService
	{
		private readonly IBookRepository _bookRepository;
		private readonly IMapper _mapper;

		public BookService(IBookRepository bookRepository, IMapper mapper)
		{
			_bookRepository = bookRepository;
			_mapper = mapper;
		}

		private bool IsExist(BookBL book)
		{
			return _bookRepository.GetAll().FirstOrDefault(elem =>
				elem.Name == book.Name) != null;
		}

		private bool IsNotExist(int id)
		{
			return _bookRepository.GetById(id) == null;
		}

		public BookBL Add(BookBL book)
		{
			if (IsExist(book))
				throw new Exception("Такая книга уже существует");

			return _mapper.Map<BookBL>(_bookRepository.Add(_mapper.Map<Book>(book)));
		}

		public BookBL Update(BookBL book)
		{
			if (IsNotExist(book.Id))
				throw new Exception("Такой книги не существует");

			return _mapper.Map<BookBL>(_bookRepository.Update(_mapper.Map<Book>(book)));
		}

		public BookBL GetById(int id)
		{
			return _mapper.Map<BookBL>(_bookRepository.GetById(id));
		}

		public BookBL GetByName(string name)
		{
			return _mapper.Map<BookBL>(_bookRepository.GetByName(name));
		}

		public IEnumerable<BookBL> GetByParameters(
			string? name, string? genre, string? language,
			int? year, int? rating,
			SearchFlag yearFlag, SearchFlag ratingFlag)
		{
			var books = _bookRepository.GetAll();

			if (books.Count() != 0 && name != null)
				books = books.Where(elem => elem.Name == name);

			if (books.Count() != 0 && genre != null)
				books = books.Where(elem => elem.Genre == genre);

			if (books.Count() != 0 && language != null)
				books = books.Where(elem => elem.Language == language);

			if (books.Count() != 0 && year != null)
			{
				if (yearFlag == SearchFlag.Equal)
					books = books.Where(elem => elem.Year == year);
				if (yearFlag == SearchFlag.More)
					books = books.Where(elem => elem.Year >= year);
				if (yearFlag == SearchFlag.Less)
					books = books.Where(elem => elem.Year <= year);
			}

			if (books.Count() != 0 && rating != null)
			{
				if (ratingFlag == SearchFlag.Equal)
					books = books.Where(elem => elem.Rating == rating);
				if (ratingFlag == SearchFlag.More)
					books = books.Where(elem => elem.Rating >= rating);
				if (ratingFlag == SearchFlag.Less)
					books = books.Where(elem => elem.Rating <= rating);
			}

			return _mapper.Map<IEnumerable<BookBL>>(books);

		}
	}
}
