using Books.Enums;
using Books.Services;
using Books.ModelsBL;
using Microsoft.AspNetCore.Mvc;
using AutoMapper;
using Books.DTO;

namespace Books.Controllers
{
	[ApiController]
	[Route("/books")]
	public class BookController : Controller
	{
		private readonly IBookService bookService;
		private readonly IMapper mapper;

		public BookController(IBookService bookService, IMapper mapper)
		{
			this.bookService = bookService;
			this.mapper = mapper;
		}

		[HttpGet]
		[ProducesResponseType(typeof(IEnumerable<SearchDTO>), StatusCodes.Status200OK)]
		[ProducesResponseType(typeof(void), StatusCodes.Status400BadRequest)]
		[ProducesResponseType(typeof(void), StatusCodes.Status401Unauthorized)]
		public IActionResult Get(
				[FromQuery] string? name = null,
				[FromQuery] string? genre = null,
				[FromQuery] string? language = null,
				[FromQuery] int? year = null,
				[FromQuery] int? rating = null,
				[FromQuery] SearchFlag yearFlag = SearchFlag.Equal,
				[FromQuery] SearchFlag ratingFlag = SearchFlag.Equal)
		{
			var getted = bookService.GetByParameters(
				name, genre, language, year, rating, yearFlag, ratingFlag);

			var searched = new SearchDTO { Books = mapper.Map<IEnumerable<BookDTO>>(getted) };
			return Ok(searched);
		}

		[HttpPost]
		[ProducesResponseType(typeof(BookDTO), StatusCodes.Status201Created)]
		[ProducesResponseType(typeof(void), StatusCodes.Status400BadRequest)]
		[ProducesResponseType(typeof(void), StatusCodes.Status401Unauthorized)]
		[ProducesResponseType(typeof(void), StatusCodes.Status409Conflict)]
		public IActionResult Post(BookBaseDTO received)
		{
			try
			{
				var added = bookService.Add(mapper.Map<BookBL>(received));
				return Created("", mapper.Map<BookDTO>(added));
			}
			catch (Exception ex)
			{
				return Conflict(ex.Message);
			}
		}

		[HttpPatch("{id}")]
		[ProducesResponseType(typeof(BookDTO), StatusCodes.Status200OK)]
		[ProducesResponseType(typeof(void), StatusCodes.Status400BadRequest)]
		[ProducesResponseType(typeof(void), StatusCodes.Status401Unauthorized)]
		[ProducesResponseType(typeof(void), StatusCodes.Status404NotFound)]
		public IActionResult Patch(int id, BookBaseDTO getted)
		{
			var existing = bookService.GetById(id);

			var created = new BookBL
			{
				Id = id,
				Name = getted.Name ?? existing.Name,
				Genre = getted.Genre ?? existing.Genre,
				Year = getted.Year ?? existing.Year,
				Language = getted.Language ?? existing.Language,
				Rating = getted.Rating ?? existing.Rating,
			};

			var updated = bookService.Update(created);
			return updated != null ? Ok(mapper.Map<BookDTO>(updated)) : NotFound();
		}
	}
}
