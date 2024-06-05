using Books.Models;

namespace IntegrationTests.DataBuilder
{
	public class SeriesBuilder
	{
		private Series _series;

		public SeriesBuilder()
		{
			_series = new Series();
		}

		public SeriesBuilder WithId(int id)
		{
			_series.Id = id;
			return this;
		}

		public SeriesBuilder WithName(string name)
		{
			_series.Name = name;
			return this;
		}

		public SeriesBuilder WithGenre(string genre)
		{
			_series.Genre = genre;
			return this;
		}

		public SeriesBuilder WithPublisher(string publisher)
		{
			_series.Publisher = publisher;
			return this;
		}

		public SeriesBuilder WithYear(int year)
		{
			_series.Year = year;
			return this;
		}

		public SeriesBuilder WithRating(double rating)
		{
			_series.Rating = rating;
			return this;
		}

		public Series Build()
		{
			return _series;
		}
	}

}
