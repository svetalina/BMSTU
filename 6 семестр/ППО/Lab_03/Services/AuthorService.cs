using Books.Models;
using Books.Interfaces;
using Books.Services;

namespace Books.Services
{
    public class AuthorService : IAuthorService
    {

        private readonly IAuthorRepository _authorRepository;

        public AuthorService(IAuthorRepository authorRepository)
        {
            _authorRepository = authorRepository;
        }


        private bool IsExist(Author author)
        {
            return _authorRepository.GetAll().FirstOrDefault(elem =>
                    elem.Name == author.Name) != null;
        }

        private bool IsNotExist(int id)
        {
            return _authorRepository.GetByID(id) == null;
        }


        public void Add(Author author)
        {
            if (IsExist(author))
                throw new Exception("Такой автор уже существует");

            _authorRepository.Add(author);
        }

        public void Update(Author author)
        {
            if (IsNotExist(author.Id))
                throw new Exception("Такой автор не существует");

            _authorRepository.Update(author);
        }

        public void Delete(Author author)
        {
            if (IsNotExist(author.Id))
                throw new Exception("Такой автор не существует");

            _authorRepository.Delete(author.Id);
        }


        public IEnumerable<Author> GetAll()
        {
            return _authorRepository.GetAll();
        }

        public Author GetByID(int id)
        {
            return _authorRepository.GetByID(id);
        }


        public Author GetByName(string name)
        {
            return _authorRepository.GetByName(name);
        }

        public IEnumerable<Author> GetByYearBirth(uint yearBirth)
        {
            return _authorRepository.GetByYearBirth(yearBirth);
        }

        public IEnumerable<Author> GetByYearDeath(uint yearDeath)
        {
            return _authorRepository.GetByYearDeath(yearDeath);
        }

        public IEnumerable<Author> GetByCountry(string country)
        {
            return _authorRepository.GetByCountry(country);
        }

        public IEnumerable<Author> GetByLanguage(string language)
        {
            return _authorRepository.GetByLanguage(language);
        }

        public IEnumerable<Author> GetByGenre(string genre)
        {
            return _authorRepository.GetByGenre(genre);
        }


        public IEnumerable<Author> GetByParameters(string name, uint yearBirth, uint yaerDeath, 
                                                   string country, string language, string genre)
        {
            IEnumerable<Author> authors = _authorRepository.GetAll();

            if (authors.Count() != 0 && name != null)
                authors = authors.Where(elem => elem.Name == name);

            if (authors.Count() != 0 && yearBirth != 0)
                authors = authors.Where(elem => elem.YearBirth >= yearBirth);

            if (authors.Count() != 0 && yaerDeath != 0)
                authors = authors.Where(elem => elem.YearDeath <= yaerDeath);

            if (authors.Count() != 0 && country != null)
                authors = authors.Where(elem => elem.Country == country);

            if (authors.Count() != 0 && language != null)
                authors = authors.Where(elem => elem.Language == language);

            if (authors.Count() != 0 && genre != null)
                authors = authors.Where(elem => elem.Genre == genre);

            return authors;
        }

        public IEnumerable<Author> GetSortAuthorsByOrder(IEnumerable<Author> authors, AuthorSortOrder sortOrder)
        {
            IEnumerable<Author> sortedAuthors = sortOrder switch
            {
                AuthorSortOrder.IdAsc => authors.OrderBy(elem => elem.Id),
                AuthorSortOrder.IdDesc => authors.OrderByDescending(elem => elem.Id),

                AuthorSortOrder.NameAsc => authors.OrderBy(elem => elem.Name),
                AuthorSortOrder.NameDesc => authors.OrderByDescending(elem => elem.Name),

                AuthorSortOrder.YearBirthAsc => authors.OrderBy(elem => elem.YearBirth),
                AuthorSortOrder.YearBirthDesc => authors.OrderByDescending(elem => elem.YearBirth),

                AuthorSortOrder.YearDeathAsc => authors.OrderBy(elem => elem.YearDeath),
                AuthorSortOrder.YearDeathDesc => authors.OrderByDescending(elem => elem.YearDeath),

                AuthorSortOrder.CountryAsc => authors.OrderBy(elem => elem.Country),
                AuthorSortOrder.CountryDesc => authors.OrderByDescending(elem => elem.Country),

                AuthorSortOrder.GenreAsc => authors.OrderBy(elem => elem.Genre),
                AuthorSortOrder.GenreDesc => authors.OrderByDescending(elem => elem.Genre),

                AuthorSortOrder.LanguageAsc => authors.OrderBy(elem => elem.Language),
                AuthorSortOrder.LanguageDesc => authors.OrderByDescending(elem => elem.Language),
            };

            return sortedAuthors;
        }
    }
}
