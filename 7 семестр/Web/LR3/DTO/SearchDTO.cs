namespace Books.DTO
{
	public class SearchDTO
	{
		public IEnumerable<AuthorDTO>? Authors { get; set; }

		public IEnumerable<BookDTO>? Books { get; set; }

		public IEnumerable<SeriesDTO>? Seriess { get; set; }
	}
}
