using Books.Models;
using Microsoft.EntityFrameworkCore;

namespace UnitTests.DAUnitTests
{
	public class DbContext
	{
		public AppDbContext GetDbContext()
		{
			string connectionString =
				"Data Source=localhost,1433;" +
				"Initial Catalog=BookDatabaseTest;" +
				"User ID=SA;" +
				"Password=PasswordSa2606!;" +
				"TrustServerCertificate=true;";

			return new AppDbContext(new DbContextOptionsBuilder<AppDbContext>()
											.UseSqlServer(connectionString)
											.Options);
		}

	}
}