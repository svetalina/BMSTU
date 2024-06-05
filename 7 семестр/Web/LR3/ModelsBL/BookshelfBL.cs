namespace Books.ModelsBL
{
	public class BookshelfBL
	{
		public int Id { get; set; }
		public int IdUser { get; set; }
		public int Number { get; set; }
		public double Rating { get; set; }
	}

	public class BookshelfBookBL
	{
		public int IdBookshelf { get; set; }
		public int IdBook { get; set; }
		public bool IsRead { get; set; }
	}
}
