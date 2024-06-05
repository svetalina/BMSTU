using System.ComponentModel.DataAnnotations;

namespace Books.Models
{
    public class Author
    {
        [Key]
        public int Id { get; set; }

        [Required]
        public string Name { get; set; }

        [Required]
        public uint YearBirth { get; set; }

        [Required]
        public uint YearDeath { get; set; }

        [Required]
        public string Country { get; set; }

        [Required]
        public string Language { get; set; }

        [Required]
        public string Genre { get; set; }
    }
}
