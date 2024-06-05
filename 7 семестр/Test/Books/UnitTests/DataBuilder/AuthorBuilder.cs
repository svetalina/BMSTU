using Books.Models;

namespace UnitTests.DataBuilder
{
	public class AuthorBuilder
	{
		private Author _author;

		public AuthorBuilder()
		{
			_author = new Author();
		}

		public AuthorBuilder WithId(int id)
		{
			_author.Id = id;
			return this;
		}

		public AuthorBuilder WithName(string name)
		{
			_author.Name = name;
			return this;
		}

		public AuthorBuilder WithYearBirth(int yearBirth)
		{
			_author.YearBirth = yearBirth;
			return this;
		}

		public AuthorBuilder WithYearDeath(int? yearDeath)
		{
			_author.YearDeath = yearDeath;
			return this;
		}

		public AuthorBuilder WithCountry(string country)
		{
			_author.Country = country;
			return this;
		}

		public AuthorBuilder WithGenre(string genre)
		{
			_author.Genre = genre;
			return this;
		}

		public Author Build()
		{
			return _author;
		}
	}

}
