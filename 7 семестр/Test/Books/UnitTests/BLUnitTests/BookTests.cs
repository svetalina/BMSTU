using Xunit;
using Allure.Xunit.Attributes;
using Books.Interfaces;
using Books.Services;
using Moq;
using UnitTests.ObjectMother;
using Books.Models;
using UnitTests.DataBuilder;

namespace UnitTests.BLUnitTests
{
	[TestCaseOrderer(
		ordererTypeName: "UnitTests.Order.RandomOrder",
		ordererAssemblyName: "UnitTests")]
	[AllureSuite("BookServiceSuite")]
	public class BookTests
	{
		private List<Book> _mockList;
		private readonly IBookService _service;

		public BookTests()
		{
			var book = new BookObjectMother().Book_1();
			book.Id = 1;

			_mockList = new List<Book>
			{
				book
			};

			var mockRepo = new Mock<IBookRepository>();

			mockRepo.Setup(repo => repo.Add(It.IsAny<Book>())).Callback(
			   (Book x) =>
			   {
				   x.Id = _mockList.Count + 1;
				   _mockList.Add(x);
			   }
			   );

			mockRepo.Setup(repo => repo.Update(It.IsAny<Book>())).Callback<Book>(
				(Book x) =>
				{
					var existing = _mockList.FirstOrDefault(y => y.Id == x.Id);
					if (existing != null)
					{
						existing.Name = x.Name;
						existing.Genre = x.Genre;
						existing.Language = x.Language;
						existing.Year = x.Year;
						existing.Rating = x.Rating;
					}
				}
				);

			mockRepo.Setup(repo => repo.Delete(It.IsAny<int>())).Callback(
			   (int id) => _mockList.RemoveAll(x => x.Id == id));

			mockRepo.Setup(repo => repo.GetAll()).Returns(_mockList);

			mockRepo.Setup(repo => repo.GetById(It.IsAny<int>())).Returns(
				(int id) => _mockList.Find(x => x.Id == id));

			mockRepo.Setup(repo => repo.GetByName(It.IsAny<string>())).Returns(
				(string name) => _mockList.Find(x => x.Name == name));

			_service = new BookService(mockRepo.Object);
		}

		[AllureXunit]
		public void TestAdd()
		{
			var expected = new BookObjectMother().Book_2();

			_service.Add(expected);

			var actual = _service.GetByName(expected.Name);

			Assert.Equal(expected.Name, actual.Name);
			Assert.Equal(expected.Genre, actual.Genre);
			Assert.Equal(expected.Language, actual.Language);
			Assert.Equal(expected.Year, actual.Year);
			Assert.Equal(expected.Rating, actual.Rating);
		}

		[AllureXunit]
		public void TestAddException()
		{
			var expected = new BookObjectMother().Book_1();

			var exception = Assert.Throws<Exception>(() => _service.Add(expected));

			Assert.Equal("Такая книга уже существует", exception.Message);
		}

		[AllureXunit]
		public void TestUpdate()
		{
			var expected = new BookObjectMother().Book_2();
			expected.Id = 1;

			_service.Update(expected);

			var actual = _service.GetByName(expected.Name);

			Assert.Equal(expected.Id, actual.Id);
			Assert.Equal(expected.Name, actual.Name);
			Assert.Equal(expected.Genre, actual.Genre);
			Assert.Equal(expected.Language, actual.Language);
			Assert.Equal(expected.Year, actual.Year);
			Assert.Equal(expected.Rating, actual.Rating);
		}

		[AllureXunit]
		public void TestUpdateException()
		{
			var expected = new BookObjectMother().Book_2();
			expected.Id = 2;

			var exception = Assert.Throws<Exception>(() => _service.Update(expected));

			Assert.Equal("Такой книги не существует", exception.Message);
		}

		[AllureXunitTheory]
		[InlineData(1, "name_1")]
		public void TestDelete(int _id, string _name)
		{
			var expected = new BookBuilder()
								.WithId(_id)
								.WithName(_name)
								.Build();

			_service.Delete(expected);

			var actual = _service.GetByName(expected.Name);

			Assert.Null(actual);
		}

		[AllureXunitTheory]
		[InlineData(2)]
		public void TestDeleteException(int _id)
		{
			var expected = new BookBuilder()
								.WithId(_id)
								.Build();

			var exception = Assert.Throws<Exception>(() => _service.Delete(expected));

			Assert.Equal("Такой книги не существует", exception.Message);
		}


		[AllureXunit]
		public void TestGetAll()
		{
			var actual = _service.GetAll();

			Assert.Equal(_mockList.Count(), actual.Count());
		}


		[AllureXunit]
		public void TestGetByName()
		{
			var expected = new BookObjectMother().Book_1();
			expected.Id = 1;

			var actual = _service.GetByName(expected.Name);

			Assert.Equal(expected.Id, actual.Id);
			Assert.Equal(expected.Name, actual.Name);
			Assert.Equal(expected.Genre, actual.Genre);
			Assert.Equal(expected.Language, actual.Language);
			Assert.Equal(expected.Year, actual.Year);
			Assert.Equal(expected.Rating, actual.Rating);
		}

		[AllureXunitTheory]
		[InlineData("genre_1")]
		public void TestGetByParameters(string _genre)
		{

			var expected = new List<Book>
			{
				new BookObjectMother().Book_1()
			};

			var parameters = new BookBuilder()
									.WithGenre(_genre)
									.Build();

			var actual = _service.GetByParameters(parameters);

			Assert.Equal(expected[0].Name, actual.First().Name);
			Assert.Equal(expected[0].Genre, actual.First().Genre);
			Assert.Equal(expected[0].Language, actual.First().Language);
			Assert.Equal(expected[0].Year, actual.First().Year);
			Assert.Equal(expected[0].Rating, actual.First().Rating);
		}
	}
}
