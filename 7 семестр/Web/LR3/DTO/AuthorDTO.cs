namespace Books.DTO
{
	public class AuthorBaseDTO
	{
		public string? Name { get; set; }
		public string? Country { get; set; }
		public string? Genre { get; set; }
		public int? YearBirth { get; set; }
		public int? YearDeath { get; set; }
	}

	public class AuthorDTO : AuthorBaseDTO
	{
		public int Id { get; set; }
	}

}
