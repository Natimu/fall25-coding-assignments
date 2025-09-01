namespace TinyMartAPI.Models
{
    public class AudioProduct : Product //inherits from product(base class)
    {
        public NameType Singer { get; set; } // both initiation and implementation of getter and setter
        public GenreType Genre { get; set; }

        //Default constructor
        public AudioProduct() : base("UnknownAudio", 0.0)
        {
            Singer = new NameType("Unknown", "Singer");
            Genre = GenreType.NoGenre;

        }
        public AudioProduct(string aProdName, double price, NameType aSinger) : base(aProdName, price)
        {
            Singer = aSinger;
            Genre = GenreType.NoGenre;

        }

        // implementing inherited abstract methods
        public override string getProdTypeStr()
        {
            return "Music";
        }

        public override void displayContentsInfo()
        {
            Console.WriteLine($"Singer: {Singer.FirstName} {Singer.LastName}");
            Console.WriteLine($"Genre: {Genre}");

        }
    }
}