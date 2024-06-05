using AutoMapper;
using Books.Models;
using Books.Enums;
using Books.ModelsBL;
using Books.Repository;

namespace Books.Services
{
	public interface IAuthorService
	{
		AuthorBL Add(AuthorBL user);
		AuthorBL Update(AuthorBL user);

		AuthorBL GetById(int id);
		AuthorBL GetByName(string name);

		IEnumerable<AuthorBL> GetByParameters(
			string? name, string? contry, string? genre,
			int? yearBirth, int? yearDeath, 
			SearchFlag yearBirthFlag, SearchFlag yearDeathFlag);
	}

	public class AuthorService : IAuthorService
	{
		private readonly IAuthorRepository _authorRepository;
		private readonly IMapper _mapper;

		public AuthorService(IAuthorRepository authorRepository,
						      IMapper mapper)
		{
			_authorRepository = authorRepository;
			_mapper = mapper;
		}


		private bool IsExist(AuthorBL author)
		{
			return _authorRepository.GetAll().FirstOrDefault(elem =>
					elem.Name == author.Name) != null;
		}

		private bool IsNotExist(int id)
		{
			return _authorRepository.GetById(id) == null;
		}

		public AuthorBL Add(AuthorBL author)
		{
			if (IsExist(author))
				throw new Exception("Такой автор уже существует");

			return _mapper.Map<AuthorBL>(_authorRepository.Add(_mapper.Map<Author>(author)));

		}

		public AuthorBL Update(AuthorBL author)
		{
			if (IsNotExist(author.Id))
				throw new Exception("Такой автор не существует");

			return _mapper.Map<AuthorBL>(_authorRepository.Update(_mapper.Map<Author>(author)));
		}

		public AuthorBL GetById(int id)
		{
			return _mapper.Map<AuthorBL>(_authorRepository.GetById(id));
		}

		public AuthorBL GetByName(string name)
		{
			return _mapper.Map<AuthorBL>(_authorRepository.GetByName(name));
		}

		public IEnumerable<AuthorBL> GetByParameters(
			string? name, string? contry, string? genre,
			int? yearBirth, int? yearDeath,
			SearchFlag yearBirthFlag, SearchFlag yearDeathFlag)
		{
			var authors = _authorRepository.GetAll();

			if (authors.Count() != 0 && name != null)
				authors = authors.Where(elem => elem.Name == name);

			if (authors.Count() != 0 && contry != null)
				authors = authors.Where(elem => elem.Country == contry);

			if (authors.Count() != 0 && genre != null)
				authors = authors.Where(elem => elem.Genre == genre);

			if (authors.Count() != 0 && yearBirth != null)
			{
				if (yearBirthFlag == SearchFlag.Equal)
					authors = authors.Where(elem => elem.YearBirth == yearBirth);
				if (yearBirthFlag == SearchFlag.More)
					authors = authors.Where(elem => elem.YearBirth >= yearBirth);
				if (yearBirthFlag == SearchFlag.Less)
					authors = authors.Where(elem => elem.YearBirth <= yearBirth);
			}

			if (authors.Count() != 0 && yearDeath != null)
			{
				if (yearDeathFlag == SearchFlag.Equal)
					authors = authors.Where(elem => elem.YearDeath == yearDeath);
				if (yearDeathFlag == SearchFlag.More)
					authors = authors.Where(elem => elem.YearDeath >= yearDeath);
				if (yearDeathFlag == SearchFlag.Less)
					authors = authors.Where(elem => elem.YearDeath <= yearDeath);
			}

			return _mapper.Map<IEnumerable<AuthorBL>>(authors);

		}
	}
}
