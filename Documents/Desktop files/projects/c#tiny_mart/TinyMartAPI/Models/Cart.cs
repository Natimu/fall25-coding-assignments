using System.Collections.Generic;
using System.Linq;

namespace TinyMartAPI.Models
{
    public class Cart
    {
        public NameType Owner { get; private set; }
        private List<Product> items = new List<Product>();

        public Cart(NameType owner)
        {
            Owner = owner;
        }

        public bool AddItem(Product p)
        {
            if (p == null) return false;
            items.Add(p);
            return true;
        }

        public bool RemoveItem(string prodName)
        {
            var item = items.FirstOrDefault(p => p.ProductName == prodName);
            if (item == null) return false;
            items.Remove(item);
            return true;
        }

        public IEnumerable<Product> GetItems() => items;
        public double GetTotalPrice() => items.Sum(p => p.Price);
    }
}
