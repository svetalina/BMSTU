using System.ComponentModel.DataAnnotations.Schema;
using System.ComponentModel.DataAnnotations;

namespace Books.Models
{
    public class BookSeries
    {
        [Key]
        public int Id { get; set; }

        [ForeignKey("Book")]
        public int IdBook { get; set; }

        [ForeignKey("Series")]
        public int IdSeries { get; set; }
    }
}
