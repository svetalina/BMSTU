namespace Books.DTO
{
	public class BookshelfBaseDTO
	{
		public int Number { get; set; }
		public double Rating { get; set; }
	}

	public class BookshelfDTO : BookshelfBaseDTO
	{
		public int Id { get; set; }
		public int IdUser { get; set; }
	}

	public class BookshelfBooksDTO
	{
		public BookshelfBaseDTO Bookshelf { get; set; }
		public IEnumerable<BookBaseDTO> Books { get; set; }
	}

	public class BookshelfBookDTO
	{
		public int IdBookshelf { get; set; }
		public int IdBook { get; set; }
		public bool IsRead { get; set; }
	}
}
