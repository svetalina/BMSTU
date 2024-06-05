namespace Books.ModelsBL
{
	public class AuthorBL
	{
		public int Id { get; set; }
		public string Name { get; set; }
		public string Country { get; set; }
		public string Genre { get; set; }
		public int YearBirth { get; set; }
		public int? YearDeath { get; set; }
	}
}
