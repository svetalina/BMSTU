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
        Console.WriteLine("Меню:");
        Console.WriteLine("1) зарегистрироваться");
        Console.WriteLine("2) авторизироваться");
        Console.WriteLine("3) найти автора");
        Console.WriteLine("4) найти книгу");
        Console.WriteLine("5) посмотреть все книги");
        Console.WriteLine("6) просмотреть всех авторов");
        Console.WriteLine("7) просмотреть все серии");
        Console.WriteLine("8) найти книгу по параметрам");
        Console.WriteLine("0) завершить работу");
        Console.Write("Введите пункт меню: ");
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
        Console.Write("Введите логин: ");
        string login = Console.ReadLine();

        Console.Write("Введите пароль: ");
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
        Console.Write("Введите логин: ");
        string login = Console.ReadLine();

        Console.Write("Введите пароль: ");
        string password = Console.ReadLine();

        User user = userService.GetByLogin(login);

        if (user != null)
        {
            if (VerifyPassword(password, user.Password))
            {
                Console.WriteLine("Неверный пароль");
                return 3;
            }
            else 
            {
                Console.WriteLine("Выполнен вход");
            }
        }
        else
        {
            Console.WriteLine("Неверный логин");
            return 4;
        }

        return 0;
    }

    public static int FindAuthor(IAuthorService authorService)
    {
        Console.Write("Введите имя автора: ");
        string authorName = Console.ReadLine();

        Author author = authorService.GetByName(authorName);

        if (author != null)
        {
            Console.WriteLine("ID: " + author.Id);
            Console.WriteLine("Имя: " + author.Name);
            Console.WriteLine("Год рождения: " + author.YearBirth);
            Console.WriteLine("Год смерти: " + author.YearDeath);
            Console.WriteLine("Страна проживания: " + author.Country);
            Console.WriteLine("Язык произведений: " + author.Language);
            Console.WriteLine("Основной жанр: " + author.Genre);
        }
        else
        {
            Console.WriteLine("Неверное имя автора");
            return 5;
        }

        return 0;
    }

    public static int FindBook(IBookService bookService)
    {
        Console.Write("Введите название произведения: ");
        string bookName = Console.ReadLine();

        Book book = bookService.GetByName(bookName);

        if (book != null)
        {
            Console.WriteLine("ID: " + book.Id);   
            Console.WriteLine("Название: " + book.Name);
            Console.WriteLine("Язык оригинала: " + book.Language);
            Console.WriteLine("Жанр: " + book.Genre);
            Console.WriteLine("Оценка: " + book.Rating);
        }
        else
        {
            Console.WriteLine("Неверное название произведения");
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
            Console.WriteLine("Название: " + curBook.Name);
            Console.WriteLine("Язык оригинала: " + curBook.Language);
            Console.WriteLine("Жанр: " + curBook.Genre);
            Console.WriteLine("Оценка: " + curBook.Rating);
        }

        return 0;
    }

    public static int FindAuthors(IAuthorService authorService)
    {
        IEnumerable<Author> authors = authorService.GetAll();

        foreach (var curAuthor in authors)
        {
            Console.WriteLine("ID: " + curAuthor.Id);
            Console.WriteLine("Имя: " + curAuthor.Name);
            Console.WriteLine("Год рождения: " + curAuthor.YearBirth);
            Console.WriteLine("Год смерти: " + curAuthor.YearDeath);
            Console.WriteLine("Страна проживания: " + curAuthor.Country);
            Console.WriteLine("Язык произведений: " + curAuthor.Language);
            Console.WriteLine("Основной жанр: " + curAuthor.Genre);
        }

        return 0;
    }

    public static int FindSeries(ISeriesService seriesService)
    {
        IEnumerable<Series> series = seriesService.GetAll();

        foreach (var curSeries in series)
        {
            Console.WriteLine("ID: " + curSeries.Id);
            Console.WriteLine("Название: " + curSeries.Name);
            Console.WriteLine("Издатель: " + curSeries.Publisher);
            Console.WriteLine("Основной жанр: " + curSeries.Genre);
            Console.WriteLine("Год основания: " + curSeries.Year);
            Console.WriteLine("Оценка: " + curSeries.Rating);
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
        Console.Write("Введите те параметры, по которым будет осущесвляться поиск: \n");

        string? bookName = DetermineStringParameteres("Название: ");
        string? bookLanguage = DetermineStringParameteres("Язык оригинала: ");
        string? bookGenre = DetermineStringParameteres("Жанр: ");
        int bookMinRating = DetermineIntParameteres("Минимальная оценка: ");
        int bookMaxRating = DetermineIntParameteres("Максимальная оценка: ");

        IEnumerable<Book> books = bookService.GetByParameters(bookName, bookGenre, bookLanguage, bookMinRating, bookMaxRating);

        if (books != null)
        {
            foreach (var curBook in books)
            {
                Console.WriteLine("ID: " + curBook.Id);
                Console.WriteLine("Название: " + curBook.Name);
                Console.WriteLine("Язык оригинала: " + curBook.Language);
                Console.WriteLine("Жанр: " + curBook.Genre);
                Console.WriteLine("Оценка: " + curBook.Rating);
            }
        }
        else 
        {
            Console.WriteLine("Не найдены книги по заданным параметрам");
            return 6;
        }

        return 0;
    }
}
