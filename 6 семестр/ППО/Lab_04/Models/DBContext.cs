using Microsoft.EntityFrameworkCore;

namespace Books.Models
{
    public class AppDBContext : DbContext
    {
        public AppDBContext(DbContextOptions<AppDBContext> options) : base(options) { }

        public DbSet<Author> Author { get; set; }
        public DbSet<Book> Book { get; set; }
        public DbSet<BookAuthor> BookAuthor { get; set; }
        public DbSet<BookBookshelf> BookBookshelf { get; set; }
        public DbSet<BookSeries> BookSeries { get; set; }
        public DbSet<Bookshelf> Bookshelf { get; set; }
        public DbSet<Series> Series { get; set; }
        public DbSet<User> User { get; set; }
    }
}