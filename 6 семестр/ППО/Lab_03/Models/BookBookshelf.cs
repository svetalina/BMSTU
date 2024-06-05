using System.ComponentModel.DataAnnotations.Schema;
using System.ComponentModel.DataAnnotations;

namespace Books.Models
{
    public class BookBookshelf
    {
        [Key]
        public int Id { get; set; }

        [ForeignKey("Book")]
        public int IdBook { get; set; }

        [ForeignKey("Bookshelf")]
        public int IdBookshelf { get; set; }
    }
}
