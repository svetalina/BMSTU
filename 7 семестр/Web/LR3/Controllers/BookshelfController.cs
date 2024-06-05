using AutoMapper;
using Books.DTO;
using Books.Models;
using Books.Services;
using Microsoft.AspNetCore.Mvc;

namespace Books.Controllers
{
	[ApiController]
	[Route("/bookshelves")]
	public class BookshelfController : Controller
	{
		private readonly IBookshelfService bookshelfService;
		private readonly IBookService bookService;
		private readonly IUserService userService;
		private readonly IMapper mapper;

		public BookshelfController(IBookshelfService bookshelfService, 
								   IBookService bookService,
								   IUserService userService,
								   IMapper mapper)
		{
			this.bookService = bookService;
			this.bookshelfService = bookshelfService;
			this.userService = userService;
			this.mapper = mapper;
		}

		[HttpGet("{id}")]
		[ProducesResponseType(typeof(IEnumerable<BookshelfBooksDTO>), StatusCodes.Status200OK)]
		[ProducesResponseType(typeof(void), StatusCodes.Status400BadRequest)]
		[ProducesResponseType(typeof(void), StatusCodes.Status401Unauthorized)]
		[ProducesResponseType(typeof(void), StatusCodes.Status404NotFound)]
		public IActionResult Get(int id)
		{
			var bookshelfBooks = new BookshelfBooksDTO();

			bookshelfBooks.Bookshelf = mapper.Map<BookshelfBaseDTO>(bookshelfService.GetById(id));
			bookshelfBooks.Books = mapper.Map<IEnumerable<BookBaseDTO>>
				(bookshelfService.GetBooksByIdBookshelf(id));

			return bookshelfBooks != null ? 
				Ok(mapper.Map<BookshelfBooksDTO>(bookshelfBooks)) : NotFound();
		}

		[HttpPost("{idBookshelf}/books/{idBook}")]
		[ProducesResponseType(typeof(IEnumerable<BookshelfBookDTO>), StatusCodes.Status201Created)]
		[ProducesResponseType(typeof(void), StatusCodes.Status400BadRequest)]
		[ProducesResponseType(typeof(void), StatusCodes.Status401Unauthorized)]
		[ProducesResponseType(typeof(void), StatusCodes.Status404NotFound)]
		public IActionResult Post(int idBookshelf, int idBook)
		{
			var added = bookshelfService.AddBook(idBookshelf, idBook);

			return added != null ?
				Created("", mapper.Map<BookshelfBookDTO>(added)) : NotFound();
		}

		[HttpPatch("{idBookshelf}/books/{idBook}")]
		[ProducesResponseType(typeof(IEnumerable<BookshelfBookDTO>), StatusCodes.Status200OK)]
		[ProducesResponseType(typeof(void), StatusCodes.Status400BadRequest)]
		[ProducesResponseType(typeof(void), StatusCodes.Status401Unauthorized)]
		[ProducesResponseType(typeof(void), StatusCodes.Status404NotFound)]
		public IActionResult Patch(int idBookshelf, int idBook)
		{
			var updated = bookshelfService.UpdateBook(idBookshelf, idBook);

			return updated != null ?
				Ok(mapper.Map<BookshelfBookDTO>(updated)) : NotFound();
		}

		[HttpDelete("{idBookshelf}/books/{idBook}")]
		[ProducesResponseType(typeof(IEnumerable<BookshelfBookDTO>), StatusCodes.Status200OK)]
		[ProducesResponseType(typeof(void), StatusCodes.Status400BadRequest)]
		[ProducesResponseType(typeof(void), StatusCodes.Status401Unauthorized)]
		[ProducesResponseType(typeof(void), StatusCodes.Status404NotFound)]
		public IActionResult Delete(int idBookshelf, int idBook)
		{
			var deleted = bookshelfService.DeleteBook(idBookshelf, idBook);

			return deleted != null ?
				Ok(mapper.Map<BookshelfBookDTO>(deleted)) : NotFound();
		}
	}
}
