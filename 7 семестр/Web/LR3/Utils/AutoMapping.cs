using AutoMapper;
using Books.DTO;
using Books.ModelsBL;
using Books.Models;

namespace Books.Utils
{
	public class AutoMappingProfile : Profile
	{
		public AutoMappingProfile()
		{
			CreateMap<Author, AuthorBL>().ReverseMap();
			CreateMap<AuthorDTO, AuthorBL>().ReverseMap();
			CreateMap<AuthorBaseDTO, AuthorBL>().ReverseMap();

			CreateMap<Book, BookBL>().ReverseMap();
			CreateMap<BookDTO, BookBL>().ReverseMap();
			CreateMap<BookBaseDTO, BookBL>().ReverseMap();

			CreateMap<Series, SeriesBL>().ReverseMap();
			CreateMap<SeriesDTO, SeriesBL>().ReverseMap();
			CreateMap<SeriesBaseDTO, SeriesBL>().ReverseMap();

			CreateMap<Bookshelf, BookshelfBL>().ReverseMap();
			CreateMap<BookshelfDTO, BookshelfBL>().ReverseMap();
			CreateMap<BookshelfBaseDTO, BookshelfBL>().ReverseMap();
			CreateMap<BookshelfBook, BookshelfBookBL>().ReverseMap();
			CreateMap<BookshelfBookDTO, BookshelfBookBL>().ReverseMap();

			CreateMap<User, UserBL>().ReverseMap();
			CreateMap<UserDTO, UserBL>().ReverseMap();
			CreateMap<UserIdDTO, UserBL>().ReverseMap(); 
			CreateMap<UserPasswordDTO, UserBL>().ReverseMap();
			CreateMap<UserBaseDTO, UserBL>().ReverseMap();
		}
	}
}