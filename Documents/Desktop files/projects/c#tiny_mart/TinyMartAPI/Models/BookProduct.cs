namespace TinyMartAPI.Models
{
    public abstract class BookProduct : Product
{
    public NameType Author{get; set;}
    public int Pages {get; set;}
    public BookProduct() : base("NoTitle", 0.0){
       Author = new NameType("Unknown","Author");
       Pages = 0;
    }
    
    public BookProduct(string aProdName, double price, NameType anAuthor, int apageNum) : base(aProdName, price)
    {
       Author = anAuthor;
       Pages = apageNum;

    }

    // implementing inherited abstract methods
    public override void displayContentsInfo()
    {
         Console.WriteLine($"Author: {Author.FirstName} {Author.LastName}");
        Console.WriteLine($"Number of Pages: {Pages}");
    }
}
}