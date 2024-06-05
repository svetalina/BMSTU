using Books.Interfaces;
using Books.Models;
using Books.Repository;

namespace Books.Services
{
    public class BookshelfService : IBookshelfService
    {
        private readonly IBookshelfRepository _bookshelfRepository;

        public BookshelfService(IBookshelfRepository bookshelfRepository)
        {
            _bookshelfRepository = bookshelfRepository;
        }


        private bool IsExist(Bookshelf bookshelf)
        {
            return _bookshelfRepository.GetAll().FirstOrDefault(elem =>
                    elem.Name == bookshelf.Name) != null;
        }

        private bool IsNotExist(int id)
        {
            return _bookshelfRepository.GetById(id) == null;
        }


        public void Add(Bookshelf bookshelf)
        {
            if (IsExist(bookshelf))
                throw new Exception("Такая серия уже существует");

            _bookshelfRepository.Add(bookshelf);
        }

        public void Update(Bookshelf bookshelf)
        {
            if (IsNotExist(bookshelf.Id))
                throw new Exception("Такой серии не существует");

            _bookshelfRepository.Update(bookshelf);
        }

        public void Delete(Bookshelf bookshelf)
        {
            if (IsNotExist(bookshelf.Id))
                throw new Exception("Такой серии не существует");

            _bookshelfRepository.Delete(bookshelf.Id);
        }


        public IEnumerable<Bookshelf> GetAll()
        {
            return _bookshelfRepository.GetAll();
        }

        public Bookshelf GetById(int id)
        {
            return _bookshelfRepository.GetById(id);
        }

        public Bookshelf GetByName(string name)
        {
            return _bookshelfRepository.GetByName(name);
        }
    }
}
