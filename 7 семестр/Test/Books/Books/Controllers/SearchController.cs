using System.Diagnostics;
using Books.Models;
using Books.Interfaces;
using Microsoft.AspNetCore.Mvc;
using Books.ViewModels;
using Books.Services;

namespace Books.Controllers
{
	public class SearchController : Controller
	{
		IAuthorService authorService;
		IBookService bookService;
		ISeriesService seriesService;

		public SearchController(IAuthorService authorService,
							  IBookService bookService,
							  ISeriesService seriesService)
		{
			this.authorService = authorService;
			this.bookService = bookService;
			this.seriesService = seriesService;
		}

		[HttpGet]
		public IActionResult SimpleSearch()
		{
			return View();
		}

		[HttpPost]
		public IActionResult SimpleSearch(string name)
		{
			Author author = authorService.GetByName(name);
			var authors = new List<Author> { author };

			Book book = bookService.GetByName(name);
			var books = new List<Book> { book };

			Series series = seriesService.GetByName(name);
			var seriess = new List<Series> { series };

			var searchDisplayViewModel = new SearchDisplayViewModel
			{
				Author = authors,
				Book = books,
				Series = seriess
			};

			return View("Display", searchDisplayViewModel);
		}

		[HttpGet]
		public IActionResult BookSearch()
		{
			return View();
		}

		[HttpPost]
		public IActionResult BookSearch(BookSearchViewModel model)
		{
			var books = bookService.GetByParameters(model.Book, model.YearFlag, model.RatingFlag);

			var searchDisplayViewModel = new SearchDisplayViewModel
			{
				Book = books,
				AuthorName = model.AuthorName,
				SeriesName = model.SeriesName
			};

			return View("Display", searchDisplayViewModel);
		}

		[HttpGet]
		public IActionResult AuthorSearch()
		{
			return View();
		}

		[HttpPost]
		public IActionResult AuthorSearch(AuthorSearchViewModel model)
		{
			IEnumerable<Author> authors = authorService.GetByParameters(model.Author,
																		model.YearBirthFlag,
																		model.YearDeathFlag);

			var searchDisplayViewModel = new SearchDisplayViewModel
			{
				Author = authors
			};

			return View("Display", searchDisplayViewModel);
		}

		[HttpGet]
		public IActionResult SeriesSearch()
		{
			return View();
		}

		[HttpPost]
		public IActionResult SeriesSearch(SeriesSearchViewModel model)
		{
			IEnumerable<Series> series = seriesService.GetByParameters(model.Series,
																		model.YearFlag,
																		model.RatingFlag);

			var searchDisplayViewModel = new SearchDisplayViewModel
			{
				Series = series
			};

			return View("Display", searchDisplayViewModel);
		}
	}
}