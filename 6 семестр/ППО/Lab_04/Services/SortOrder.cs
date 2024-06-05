namespace Books.Services
{
    public enum AuthorSortOrder
    {
        IdAsc,
        IdDesc,

        NameAsc,
        NameDesc,

        YearBirthAsc,
        YearBirthDesc,

        YearDeathAsc,
        YearDeathDesc,

        CountryAsc,
        CountryDesc,

        LanguageAsc,
        LanguageDesc,

        GenreAsc,
        GenreDesc,
    }

    public enum BookSortOrder
    {
        IdAsc,
        IdDesc,

        NameAsc,
        NameDesc,

        LanguageAsc,
        LanguageDesc,

        GenreAsc,
        GenreDesc,

        RatingAsc,
        RatingDesc
    }

    public enum SeriesSortOrder
    {
        IdAsc,
        IdDesc,

        NameAsc,
        NameDesc,

        GenreAsc,
        GenreDesc,

        PublisherAsc,
        PublisherDesc,

        YearAsc,
        YearDesc,

        RatingAsc,
        RatingDesc
    }

    public enum UserSortOrder
    {
        IdAsc,
        IdDesc,

        LoginAsc,
        LoginDesc,

        PermissionAsc,
        PermissionDesc,
    }
}
