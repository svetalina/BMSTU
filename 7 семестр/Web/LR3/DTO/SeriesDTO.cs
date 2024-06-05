namespace Books.DTO
{
	public class SeriesBaseDTO
	{
		public string? Name { get; set; }
		public string? Genre { get; set; }
		public string? Publisher { get; set; }
		public int? Year { get; set; }
		public int? Rating { get; set; }
	}

	public class SeriesDTO : SeriesBaseDTO
	{
		public int Id { get; set; }
	}

}
