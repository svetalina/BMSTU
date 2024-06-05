using Books.Enums;
using Books.Services;
using Books.ModelsBL;
using Microsoft.AspNetCore.Mvc;
using AutoMapper;
using Books.DTO;

namespace Books.Controllers
{
	[ApiController]
	[Route("/authors")]
	public class AuthorController : Controller
	{
		private readonly IAuthorService authorService;
		private readonly IMapper mapper;

		public AuthorController(IAuthorService authorService,
							    IMapper mapper)
		{
			this.authorService = authorService;
			this.mapper = mapper;
		}

		[HttpGet]
		[ProducesResponseType(typeof(IEnumerable<SearchDTO>), StatusCodes.Status200OK)]
		[ProducesResponseType(typeof(void), StatusCodes.Status400BadRequest)]
		[ProducesResponseType(typeof(void), StatusCodes.Status401Unauthorized)]
		public IActionResult Get(
				[FromQuery] string? name = null,
				[FromQuery] string? country = null,
				[FromQuery] string? genre = null,
				[FromQuery] int? yearBirth = null,
				[FromQuery] int? yearDeath = null,
				[FromQuery] SearchFlag yearBirthFlag = SearchFlag.Equal,
				[FromQuery] SearchFlag yearDeathFlag = SearchFlag.Equal)
		{
			var getted = authorService.GetByParameters(
				name, country, genre, yearBirth, yearDeath, yearBirthFlag, yearDeathFlag);

			var searched = new SearchDTO { Authors = mapper.Map<IEnumerable<AuthorDTO>>(getted) };
			return Ok(searched);
		}

		[HttpPost]
		[ProducesResponseType(typeof(IEnumerable<AuthorDTO>), StatusCodes.Status201Created)]
		[ProducesResponseType(typeof(void), StatusCodes.Status400BadRequest)]
		[ProducesResponseType(typeof(void), StatusCodes.Status401Unauthorized)]
		[ProducesResponseType(typeof(void), StatusCodes.Status403Forbidden)]
		[ProducesResponseType(typeof(void), StatusCodes.Status409Conflict)]
		public IActionResult Post(AuthorBaseDTO getted)
		{
			try
			{
				var added = authorService.Add(mapper.Map<AuthorBL>(getted));
				return Created("", mapper.Map<AuthorDTO>(added));
			}
			catch (Exception ex)
			{
				return Conflict(ex.Message);
			}
		}

		[HttpPatch("{id}")]
		[ProducesResponseType(typeof(AuthorDTO), StatusCodes.Status200OK)]
		[ProducesResponseType(typeof(void), StatusCodes.Status400BadRequest)]
		[ProducesResponseType(typeof(void), StatusCodes.Status401Unauthorized)]
		[ProducesResponseType(typeof(void), StatusCodes.Status403Forbidden)]
		[ProducesResponseType(typeof(void), StatusCodes.Status404NotFound)]
		public IActionResult Patch(int id, AuthorBaseDTO getted)
		{
			var existed = authorService.GetById(id);

			var created = new AuthorBL
			{
				Id = id,
				Name = getted.Name ?? existed.Name,
				Country = getted.Country ?? existed.Country,
				Genre = getted.Genre ?? existed.Genre,
				YearBirth = getted.YearBirth ?? existed.YearBirth,
				YearDeath = getted.YearDeath ?? existed.YearDeath,
			};

			var updated = authorService.Update(created);
			return updated != null ? Ok(mapper.Map<AuthorDTO>(updated)) : NotFound();
		}
	}
}