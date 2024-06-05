using Books.Models;
using Books.Services;
using Books.Interfaces;
using Books.Repository;
using Microsoft.EntityFrameworkCore;
using System.Security.Cryptography;

public class TechUI
{
    static void Main(string[] args)
    {
        var configuration = new ConfigurationBuilder()
            .AddJsonFile("appsettings.json")
            .Build();

        string connectionString = configuration.GetConnectionString("DefaultConnection");

        var optionsBuilder = new DbContextOptionsBuilder<AppDBContext>();
        optionsBuilder.UseSqlServer(connectionString);

        var dbContext = new AppDBContext(optionsBuilder.Options);
        
        var auothorRepository = new AuthorRepository(dbContext);
        var authorService = new AuthorService(auothorRepository);

        var bookRepository = new BookRepository(dbContext);
        var bookService = new BookService(bookRepository);

        var bookshelfRepository = new BookshelfRepository(dbContext);
        var bookshelfService = new BookshelfService(bookshelfRepository);

        var seriesRepository = new SeriesRepository(dbContext);
        var seriesService = new SeriesService(seriesRepository);

        var userRepository = new UserRepository(dbContext);
        var userService = new UserService(userRepository);


        bool flag = true;

        while (flag)
        {
            PrintMenu();
            var option = Convert.ToInt32(Console.ReadLine());

            switch (option)
            {
                case 0:
                    flag = false;
                    break;
                case 1:
                    Register(userService, bookshelfService);
                    break;
                case 2:
                    Login(userService);
                    break;
                case 3:
                    FindAuthor(authorService);
                    break;
                case 4:
                    FindBook(bookService);
                    break;
                case 5:
                    FindBooks(bookService);
                    break;
                case 6:
                    FindAuthor(authorService);
                    break;
                case 7:
                    FindSeries(seriesService);
                    break;
                case 8:
                    FindBookByParameteres(bookService);
                    break;
                default:
                    break;
            }
        }
    }
    public static void PrintMenu()
    {
        Console.WriteLine("����:");
        Console.WriteLine("1) ������������������");
        Console.WriteLine("2) ����������������");
        Console.WriteLine("3) ����� ������");
        Console.WriteLine("4) ����� �����");
        Console.WriteLine("5) ���������� ��� �����");
        Console.WriteLine("6) ����������� ���� �������");
        Console.WriteLine("7) ����������� ��� �����");
        Console.WriteLine("8) ����� ����� �� ����������");
        Console.WriteLine("0) ��������� ������");
        Console.Write("������� ����� ����: ");
    }

    private static string HashPassword(string password, byte[] salt)
    {
        using (var pbkdf2 = new Rfc2898DeriveBytes(password, salt, 10000, HashAlgorithmName.SHA256))
        {
            byte[] hash = pbkdf2.GetBytes(32);
            byte[] saltAndHash = new byte[36];
            Buffer.BlockCopy(salt, 0, saltAndHash, 0, 4);
            Buffer.BlockCopy(hash, 0, saltAndHash, 4, 32);
            return Convert.ToBase64String(saltAndHash);
        }
    }

    public static bool VerifyPassword(string password, string hashedPassword)
    {
        byte[] saltAndHash = Convert.FromBase64String(hashedPassword);
        byte[] salt = new byte[16]; 
        Buffer.BlockCopy(saltAndHash, 0, salt, 0, 16);

        string hashToCheck = HashPassword(password, salt); 
        byte[] hashBytes = Convert.FromBase64String(hashedPassword); 

        return hashBytes.SequenceEqual(Convert.FromBase64String(hashToCheck));
    }

    private static byte[] GenerateSalt()
    {
        byte[] salt = new byte[4]; 
        using (var rng = new RNGCryptoServiceProvider())
        {
            rng.GetBytes(salt);
        }
        return salt;
    }

    public static int Register(IUserService userService,
                               IBookshelfService bookshelfService)
    {
        Console.Write("������� �����: ");
        string login = Console.ReadLine();

        Console.Write("������� ������: ");
        string password = Console.ReadLine();

        byte[] salt = GenerateSalt();
        string hashedPassword = HashPassword(password, salt);

        if (VerifyPassword(password, hashedPassword))
        {
            Console.WriteLine("sfsdfsdgsdgsdgsdgsdgsdg");
        }

        var user = new User
        {
            Login = login,
            Password = hashedPassword,
            Permission = "user"
        };

        var bookshelf = new Bookshelf
        {
            Name = user.Login
        };

        try
        {
            bookshelfService.Add(bookshelf);
        }
        catch (Exception ex)
        {
            Console.WriteLine(ex.Message);
            return 1;
        }

        try 
        { 
            user.IdBookshelf = bookshelfService.GetByName(user.Login).Id;
            userService.Add(user);
        }
        catch (Exception ex)
        {
            Console.WriteLine(ex.Message);
            return 2;
        }

        return 0;
    }

    public static int Login(IUserService userService)
    {
        Console.Write("������� �����: ");
        string login = Console.ReadLine();

        Console.Write("������� ������: ");
        string password = Console.ReadLine();

        User user = userService.GetByLogin(login);

        if (user != null)
        {
            if (VerifyPassword(password, user.Password))
            {
                Console.WriteLine("�������� ������");
                return 3;
            }
            else 
            {
                Console.WriteLine("�������� ����");
            }
        }
        else
        {
            Console.WriteLine("�������� �����");
            return 4;
        }

        return 0;
    }

    public static int FindAuthor(IAuthorService authorService)
    {
        Console.Write("������� ��� ������: ");
        string authorName = Console.ReadLine();

        Author author = authorService.GetByName(authorName);

        if (author != null)
        {
            Console.WriteLine("ID: " + author.Id);
            Console.WriteLine("���: " + author.Name);
            Console.WriteLine("��� ��������: " + author.YearBirth);
            Console.WriteLine("��� ������: " + author.YearDeath);
            Console.WriteLine("������ ����������: " + author.Country);
            Console.WriteLine("���� ������������: " + author.Language);
            Console.WriteLine("�������� ����: " + author.Genre);
        }
        else
        {
            Console.WriteLine("�������� ��� ������");
            return 5;
        }

        return 0;
    }

    public static int FindBook(IBookService bookService)
    {
        Console.Write("������� �������� ������������: ");
        string bookName = Console.ReadLine();

        Book book = bookService.GetByName(bookName);

        if (book != null)
        {
            Console.WriteLine("ID: " + book.Id);   
            Console.WriteLine("��������: " + book.Name);
            Console.WriteLine("���� ���������: " + book.Language);
            Console.WriteLine("����: " + book.Genre);
            Console.WriteLine("������: " + book.Rating);
        }
        else
        {
            Console.WriteLine("�������� �������� ������������");
            return 4;
        }

        return 0;
    }

    public static int FindBooks(IBookService bookService)
    {
        IEnumerable<Book> books = bookService.GetAll();

        foreach (var curBook in books)
        {
            Console.WriteLine("ID: " + curBook.Id);
            Console.WriteLine("��������: " + curBook.Name);
            Console.WriteLine("���� ���������: " + curBook.Language);
            Console.WriteLine("����: " + curBook.Genre);
            Console.WriteLine("������: " + curBook.Rating);
        }

        return 0;
    }

    public static int FindAuthors(IAuthorService authorService)
    {
        IEnumerable<Author> authors = authorService.GetAll();

        foreach (var curAuthor in authors)
        {
            Console.WriteLine("ID: " + curAuthor.Id);
            Console.WriteLine("���: " + curAuthor.Name);
            Console.WriteLine("��� ��������: " + curAuthor.YearBirth);
            Console.WriteLine("��� ������: " + curAuthor.YearDeath);
            Console.WriteLine("������ ����������: " + curAuthor.Country);
            Console.WriteLine("���� ������������: " + curAuthor.Language);
            Console.WriteLine("�������� ����: " + curAuthor.Genre);
        }

        return 0;
    }

    public static int FindSeries(ISeriesService seriesService)
    {
        IEnumerable<Series> series = seriesService.GetAll();

        foreach (var curSeries in series)
        {
            Console.WriteLine("ID: " + curSeries.Id);
            Console.WriteLine("��������: " + curSeries.Name);
            Console.WriteLine("��������: " + curSeries.Publisher);
            Console.WriteLine("�������� ����: " + curSeries.Genre);
            Console.WriteLine("��� ���������: " + curSeries.Year);
            Console.WriteLine("������: " + curSeries.Rating);
        }

        return 0;
    }

    private static string? DetermineStringParameteres(string nameParameter)
    {
        Console.WriteLine(nameParameter);
        string parameter = Console.ReadLine();
        if (string.IsNullOrWhiteSpace(parameter))
        {
            return null;
        }

        return parameter;
    }

    private static int DetermineIntParameteres(string nameParameter)
    {
        Console.WriteLine(nameParameter);
        string parameter = Console.ReadLine();
        if (string.IsNullOrWhiteSpace(parameter))
        {
            return 0;
        }

        return Convert.ToInt32(parameter);
    }

    public static int FindBookByParameteres(IBookService bookService)
    {
        Console.Write("������� �� ���������, �� ������� ����� ������������� �����: \n");

        string? bookName = DetermineStringParameteres("��������: ");
        string? bookLanguage = DetermineStringParameteres("���� ���������: ");
        string? bookGenre = DetermineStringParameteres("����: ");
        int bookMinRating = DetermineIntParameteres("����������� ������: ");
        int bookMaxRating = DetermineIntParameteres("������������ ������: ");

        IEnumerable<Book> books = bookService.GetByParameters(bookName, bookGenre, bookLanguage, bookMinRating, bookMaxRating);

        if (books != null)
        {
            foreach (var curBook in books)
            {
                Console.WriteLine("ID: " + curBook.Id);
                Console.WriteLine("��������: " + curBook.Name);
                Console.WriteLine("���� ���������: " + curBook.Language);
                Console.WriteLine("����: " + curBook.Genre);
                Console.WriteLine("������: " + curBook.Rating);
            }
        }
        else 
        {
            Console.WriteLine("�� ������� ����� �� �������� ����������");
            return 6;
        }

        return 0;
    }
}
