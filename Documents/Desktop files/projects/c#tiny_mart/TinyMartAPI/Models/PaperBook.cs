namespace TinyMartAPI.Models
{
    public class PaperBook : BookProduct
{
    public PaperBook(): base("!No Title", 0.0, new NameType ("Unknown", "Author"), 0){
    }
    public PaperBook(string aProdName, double price, NameType anAuthor, int apageNum) : base(aProdName, price, anAuthor, apageNum)
    {
    }
    public override string getProdTypeStr()
    {
        return "Paper Book";
    }
    
}
}