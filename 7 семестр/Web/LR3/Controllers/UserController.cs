using Books.Models;
using Books.Services;
using Books.ModelsBL;
using Microsoft.AspNetCore.Mvc;
using AutoMapper;
using Books.DTO;
using static Microsoft.EntityFrameworkCore.DbLoggerCategory;

namespace Books.Controllers
{
	[ApiController]
	[Route("/users")]
	public class UserController : Controller
	{
		private readonly IUserService userService;
		private readonly IBookshelfService bookshelfService;
		private readonly IMapper mapper;

		public UserController(IUserService userService,
							  IBookshelfService bookshelfService,
							  IMapper mapper)
		{
			this.userService = userService;
			this.bookshelfService = bookshelfService;
			this.mapper = mapper;
		}

		[HttpPost("register")]
		[ProducesResponseType(typeof(UserDTO), StatusCodes.Status201Created)]
		[ProducesResponseType(typeof(void), StatusCodes.Status400BadRequest)]
		[ProducesResponseType(typeof(void), StatusCodes.Status409Conflict)]
		public IActionResult Register(string login, string password)
		{
			var user = new UserBL
			{
				Login = login,
				Password = password,
				Permission = "user"
			};

			try
			{
				var added = userService.Add(user);

				bookshelfService.Add(new BookshelfBL{
					IdUser = userService.GetByLogin(login).Id});

				return Created("", mapper.Map<UserDTO>(added));
			}
			catch (Exception ex)
			{
				return Conflict(ex.Message);
			}
		}

		[HttpPost("login")]
		[ProducesResponseType(typeof(UserDTO), StatusCodes.Status200OK)]
		[ProducesResponseType(typeof(void), StatusCodes.Status400BadRequest)]
		[ProducesResponseType(typeof(void), StatusCodes.Status404NotFound)]
		public IActionResult Login(string login, string password)
		{
			var getted = userService.GetByLogin(login);

			if (getted != null && getted.Password == password)
				return Ok(mapper.Map<UserDTO>(getted));
			else
				return NotFound();
		}

		[HttpPatch("{id}")]
		[ProducesResponseType(typeof(UserDTO), StatusCodes.Status200OK)]
		[ProducesResponseType(typeof(void), StatusCodes.Status400BadRequest)]
		[ProducesResponseType(typeof(void), StatusCodes.Status401Unauthorized)]
		[ProducesResponseType(typeof(void), StatusCodes.Status404NotFound)]
		public IActionResult Patch(int id, string? password = null, string? permission = null)
		{
			var existed = userService.GetById(id);

			var created = new UserBL
			{
				Id = id,
				Login = existed.Login,
				Password = password ?? existed.Password,
				Permission = permission ?? existed.Permission
			};

			var updated = userService.Update(created);
			return updated != null ? Ok(mapper.Map<UserDTO>(updated)) : NotFound();
		}


		[HttpDelete("{id}")]
		[ProducesResponseType(typeof(UserDTO), StatusCodes.Status200OK)]
		[ProducesResponseType(typeof(void), StatusCodes.Status400BadRequest)]
		[ProducesResponseType(typeof(void), StatusCodes.Status401Unauthorized)]
		[ProducesResponseType(typeof(void), StatusCodes.Status404NotFound)]
		public IActionResult Delete(int id)
		{
			var deleted = userService.Delete(id);
			return deleted != null ? Ok(mapper.Map<UserDTO>(deleted)) : NotFound();
		}
	}
}
