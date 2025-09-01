namespace TinyMartAPI.Models
   
{
    public record NameType(string FirstName, string LastName)
    {
        public override string ToString() => $"{FirstName} {LastName}";
    }
}

