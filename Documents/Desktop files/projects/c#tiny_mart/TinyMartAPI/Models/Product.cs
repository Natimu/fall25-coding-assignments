using System;
namespace TinyMartAPI.Models
{
    using prod_id_t = System.Int32;
    

    public abstract class Product
    {
        public prod_id_t ProductID { get; private set; } // productID setter is private because outside classes should not have access for it
        public string ProductName { get; set; }
        
        private double _price;
        public double Price
        {
            get => _price;
            set
            {
                if (value < 0 || value > 1000)
                    throw new ArgumentOutOfRangeException(nameof(Price), "Price must be between 0 and 1,000.");
                _price = value;
            }
        }

        public float ReviewRate { get; set; }

        // Static (class) member
        private static prod_id_t nextID = 1;

        // Static method to generate a unique product ID
        public static prod_id_t CreateNewID()
        {
            return nextID++;
        }

        public Product(string aProdName, double price)
        {
            // initial control 
        /* if (string.IsNullOrWhiteSpace(aProdName)){
                ProductName = "!No Name Product!";
            }
            else{
                ProductName = aProdName;
            }*/


            ProductName = string.IsNullOrWhiteSpace(aProdName) ? "!No Name Product!": aProdName;   
            Price = price;
            ReviewRate = 0.0f;
            ProductID = CreateNewID();
        }

        public void SetProdID(prod_id_t id) => ProductID = id;  // this will give optional access to set product id manually

        public abstract string getProdTypeStr();  // abstract methods (pure virtual functions) must be implemented in the child class
        public abstract void displayContentsInfo();
        public virtual void displayProductInfo(){ // virtual methods (non-pure virtual functions) child class may override it
            Console.WriteLine($"Product ID: {ProductID}");
            Console.WriteLine($"Product Name: {ProductName}");
            Console.WriteLine($"Product Price: ${Price}");
            Console.WriteLine($"Product Rating: {ReviewRate}");
            displayContentsInfo();
        }

    }

    }