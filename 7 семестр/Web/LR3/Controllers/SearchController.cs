using AutoMapper;
using Books.DTO;
using Books.Services;
using Microsoft.AspNetCore.Mvc;
using System.Collections.Generic;

namespace Books.Controllers
{
	[ApiController]
	[Route("/search")]
	public class SearchController : Controller
	{
		private readonly IAuthorService authorService;
		private readonly IBookService bookService;
		private readonly ISeriesService seriesService;
		private readonly IMapper mapper;

		public SearchController(IAuthorService authorService,
								IBookService bookService,
								ISeriesService seriesService,
								IMapper mapper)
		{
			this.authorService = authorService;
			this.bookService = bookService;
			this.seriesService = seriesService;
			this.mapper = mapper;
		}

		[HttpGet]
		[ProducesResponseType(typeof(IEnumerable<SearchDTO>), StatusCodes.Status200OK)]
		[ProducesResponseType(typeof(void), StatusCodes.Status400BadRequest)]
		public IActionResult Get([FromQuery] string name)
		{
			var searched = new SearchDTO();

			var gettedAuthor = authorService.GetByName(name);
			var gettedAuthors = Enumerable.Repeat(gettedAuthor, 1);
			searched.Authors = mapper.Map<IEnumerable<AuthorDTO>>(gettedAuthors);

			var gettedBook = bookService.GetByName(name);
			var gettedBooks = Enumerable.Repeat(gettedBook, 1);
			searched.Books = mapper.Map<IEnumerable<BookDTO>>(gettedBooks);

			var gettedSeries = seriesService.GetByName(name);
			var gettedSeriess = Enumerable.Repeat(gettedSeries, 1);
			searched.Seriess = mapper.Map<IEnumerable<SeriesDTO>>(gettedSeriess);

			return Ok(searched);
		}
	}
}
