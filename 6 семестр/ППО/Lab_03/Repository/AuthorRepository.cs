using Books.Models;
using Books.Interfaces;

namespace Books.Repository
{
    public class AuthorRepository : IAuthorRepository
    {
        public AuthorRepository() { }

        public void Add(Author model)
        {
            throw new NotImplementedException();
        }

        public void Update(Author model)
        {
            throw new NotImplementedException();
        }

        public void Delete(int id)
        {
            throw new NotImplementedException();
        }

        public IEnumerable<Author> GetAll()
        {
            throw new NotImplementedException();
        }

        public Author GetByID(int id)
        {
            throw new NotImplementedException();
        }

        public Author GetByName(string name)
        {
            throw new NotImplementedException();
        }


        public IEnumerable<Author> GetByYearBirth(uint yearBirth)
        {
            throw new NotImplementedException();
        }

        public IEnumerable<Author> GetByYearDeath(uint yearDeath)
        {
            throw new NotImplementedException();
        }

        public IEnumerable<Author> GetByCountry(string country)
        {
            throw new NotImplementedException();
        }

        public IEnumerable<Author> GetByLanguage(string language)
        {
            throw new NotImplementedException();
        }

        public IEnumerable<Author> GetByGenre(string genre)
        {
            throw new NotImplementedException();
        }
    }
}
