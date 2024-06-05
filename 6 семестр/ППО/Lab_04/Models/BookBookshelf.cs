using System.ComponentModel.DataAnnotations.Schema;
using System.ComponentModel.DataAnnotations;
using Microsoft.EntityFrameworkCore;

namespace Books.Models
{
    [PrimaryKey(nameof(IdBook), nameof(IdBookshelf))]
    public class BookBookshelf
    {

        [ForeignKey("Book")]
        public int IdBook { get; set; }

        [ForeignKey("Bookshelf")]
        public int IdBookshelf { get; set; }
    }
}
