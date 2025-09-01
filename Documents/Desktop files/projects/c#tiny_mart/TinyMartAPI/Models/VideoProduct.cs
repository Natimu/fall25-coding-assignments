namespace TinyMartAPI.Models
{
    public class VideoProduct : Product
{
    // more member variables
    public NameType Director {get; set;}
    public FilmRateType FilmRate{get; set;}
    public int ReleaseYear {get; set;}
    public int RunTime {get; set;}
    public VideoProduct(): base("No Title Name", 0.0){
        Director = new NameType("Unknown", "Name");
        ReleaseYear = 0;
        RunTime = 0;
        FilmRate = FilmRateType.NotRated;

    }
    public VideoProduct(string aProdName, double price, NameType aDirectorName, int aReleaseYear, int aRunTime) : base(aProdName, price)
    {
         Director = aDirectorName;
         ReleaseYear = aReleaseYear;
         RunTime = aRunTime;
         FilmRate = FilmRateType.NotRated;
    }
    public override string getProdTypeStr()
    {
        return "Movie";
    }

    
    public override void displayContentsInfo()
    {
         Console.WriteLine($"Director: {Director.FirstName} {Director.LastName}");
        Console.WriteLine($"Release Year: {ReleaseYear}");
        Console.WriteLine($"Run Time: {RunTime}");
        Console.WriteLine($"Film Rate: {FilmRate}");
    }

}
}