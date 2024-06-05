namespace Books.DTO
{
	public class UserBaseDTO
	{
		public string Login { get; set; }
		public string Permission { get; set; }
	}

	public class UserIdDTO : UserBaseDTO
	{
		public int Id { get; set; }
	}

	public class UserPasswordDTO : UserBaseDTO
	{
		public string Password { get; set; }
	}

	public class UserDTO : UserBaseDTO
	{
		public int Id { get; set; }
		public string Password { get; set; }
	}
}