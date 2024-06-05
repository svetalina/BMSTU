namespace Books.DTO
{
	public class BookBaseDTO
	{
		public string? Name { get; set; }
		public string? Genre { get; set; }
		public string? Language { get; set; }
		public int? Year { get; set; }
		public double? Rating { get; set; }
	}

	public class BookDTO : BookBaseDTO
	{
		public int Id { get; set; }
	}
}