namespace TinyMartAPI.Models
{
    public class EBook : BookProduct
    {
        // no additional member variable

        public EBook(): base("!No Title", 0.0, new NameType ("Unknown", "Author"), 0){
        }
        public EBook(string aProdName, double price, NameType anAuthor, int apageNum) : base(aProdName, price, anAuthor, apageNum)
        {
        }
        // implementing abstract methods passed from product to BookProducts then to EBook
        public override string getProdTypeStr()
        {
            return "E Book";
        }

    }
}