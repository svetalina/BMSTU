using System.ComponentModel.DataAnnotations.Schema;
using System.ComponentModel.DataAnnotations;

namespace Books.Models
{
    public class BookAuthor
    {
        [Key]
        public int Id { get; set; }

        [ForeignKey("Book")]
        public int IdBook { get; set; }

        [ForeignKey("Author")]
        public int IdAuthor { get; set; }
    }
}
