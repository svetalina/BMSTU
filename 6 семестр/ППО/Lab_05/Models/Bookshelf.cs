using System.ComponentModel.DataAnnotations;

namespace Books.Models
{
    public class Bookshelf
    {
        [Key]
        public int Id { get; set; }

        [Required]
        public string Name { get; set; }
    }
}
