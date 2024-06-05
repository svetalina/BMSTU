using Books.Enums;
using Books.Services;
using Books.ModelsBL;
using Microsoft.AspNetCore.Mvc;
using AutoMapper;
using Books.DTO;

namespace Books.Controllers
{
	[ApiController]
	[Route("/series")]
	public class SeriesController : Controller
	{
		private readonly ISeriesService seriesService;
		private readonly IMapper mapper;

		public SeriesController(ISeriesService seriesService,
							    IMapper mapper)
		{
			this.seriesService = seriesService;
			this.mapper = mapper;
		}

		[HttpGet]
		[ProducesResponseType(typeof(IEnumerable<SearchDTO>), StatusCodes.Status200OK)]
		[ProducesResponseType(typeof(void), StatusCodes.Status400BadRequest)]
		[ProducesResponseType(typeof(void), StatusCodes.Status401Unauthorized)]
		public IActionResult Get(
				[FromQuery] string? name = null,
				[FromQuery] string? genre = null,
				[FromQuery] string? publisher = null,
				[FromQuery] int? year = null,
				[FromQuery] int? rating = null,
				[FromQuery] SearchFlag yearFlag = SearchFlag.Equal,
				[FromQuery] SearchFlag ratingFlag = SearchFlag.Equal)
		{
			var getted = seriesService.GetByParameters(
				name, genre, publisher, year, rating, yearFlag, ratingFlag);

			var searched = new SearchDTO { Seriess = mapper.Map<IEnumerable<SeriesDTO>>(getted) };
			return Ok(searched);
		}

		[HttpPost]
		[ProducesResponseType(typeof(IEnumerable<SeriesDTO>), StatusCodes.Status201Created)]
		[ProducesResponseType(typeof(void), StatusCodes.Status400BadRequest)]
		[ProducesResponseType(typeof(void), StatusCodes.Status401Unauthorized)]
		[ProducesResponseType(typeof(void), StatusCodes.Status403Forbidden)]
		[ProducesResponseType(typeof(void), StatusCodes.Status409Conflict)]
		public IActionResult Post(SeriesBaseDTO getted)
		{
			try
			{
				var added = seriesService.Add(mapper.Map<SeriesBL>(getted));
				return Created("", mapper.Map<SeriesDTO>(added));
			}
			catch (Exception ex)
			{
				return Conflict(ex.Message);
			}
		}

		[HttpPatch("{id}")]
		[ProducesResponseType(typeof(SeriesDTO), StatusCodes.Status200OK)]
		[ProducesResponseType(typeof(void), StatusCodes.Status400BadRequest)]
		[ProducesResponseType(typeof(void), StatusCodes.Status401Unauthorized)]
		[ProducesResponseType(typeof(void), StatusCodes.Status403Forbidden)]
		[ProducesResponseType(typeof(void), StatusCodes.Status404NotFound)]
		public IActionResult Patch(int id, SeriesBaseDTO getted)
		{
			var existed = seriesService.GetById(id);

			var created = new SeriesBL
			{
				Id = id,
				Name = getted.Name ?? existed.Name,
				Genre = getted.Genre ?? existed.Genre,
				Publisher = getted.Publisher ?? existed.Publisher,
				Year = getted.Year ?? existed.Year,
				Rating = getted.Rating ?? existed.Rating,
			};

			var updated = seriesService.Update(created);
			return updated != null ? Ok(mapper.Map<SeriesDTO>(updated)) : NotFound();
		}
	}
}