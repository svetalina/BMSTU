using Books.Models;

namespace Books.Interfaces
{
    public interface ISeriesRepository : IRepository<Series>
    {
		Series GetByName(string name);
	}
}
