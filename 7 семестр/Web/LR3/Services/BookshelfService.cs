using AutoMapper;
using Books.Models;
using Books.ModelsBL;
using Books.Repository;

namespace Books.Services
{
    public interface IBookshelfService
	{
		//BookshelfBL Add(BookshelfBL bookshelf);
		//BookshelfBL Update(BookshelfBL bookshelf);

		void Add(BookshelfBL bookshelf);

		BookshelfBL GetById(int id);
		IEnumerable<BookBL> GetBooksByIdBookshelf(int idBookshelf);

		BookshelfBookBL AddBook(int idBookshelf, int idBook);
		BookshelfBookBL UpdateBook(int idBookshelf, int idBook);
		BookshelfBookBL DeleteBook(int idBookshelf, int idBook);
	}


    public class BookshelfService : IBookshelfService
    {
        private readonly IBookshelfRepository _bookshelfRepository;
		private readonly IMapper _mapper;

		public BookshelfService(IBookshelfRepository bookshelfRepository,
                                IMapper mapper)
        {
            _bookshelfRepository = bookshelfRepository;
			_mapper = mapper;
		}

		public void Add(BookshelfBL bookshelf)
		{
			_bookshelfRepository.Add(_mapper.Map<Bookshelf>(bookshelf));
		}

		public BookshelfBL GetById(int id)
		{
            return _mapper.Map<BookshelfBL>(_bookshelfRepository.GetById(id));
        }

		public IEnumerable<BookBL> GetBooksByIdBookshelf(int idBookshelf)
		{
			return _mapper.Map<IEnumerable<BookBL>>
                (_bookshelfRepository.GetBooksByIdBookshelf(idBookshelf));
		}

		private bool IsExistBookBookshelf(int idBookshelf, int idBook)
		{
			return _bookshelfRepository.GetBookshelfBookByIds(idBookshelf, idBook) != null;
		}

		public BookshelfBookBL AddBook(int idBookshelf, int idBook)
		{
			if (IsExistBookBookshelf(idBookshelf, idBook))
				throw new Exception("Такая книга уже существует на книжной полке");

			return _mapper.Map<BookshelfBookBL>(_bookshelfRepository.AddBook(
				new BookshelfBook { IdBookshelf = idBookshelf, IdBook = idBook}));
		}

		public BookshelfBookBL UpdateBook(int idBookshelf, int idBook)
		{
			return _mapper.Map<BookshelfBookBL>(_bookshelfRepository.UpdateBook(
				new BookshelfBook { IdBookshelf = idBookshelf, IdBook = idBook, IsRead = true}));
		}

		public BookshelfBookBL DeleteBook(int idBookshelf, int idBook)
		{
			return _mapper.Map<BookshelfBookBL>(_bookshelfRepository.DeleteBook(
				new BookshelfBook { IdBookshelf = idBookshelf, IdBook = idBook}));
		}
	}
}
