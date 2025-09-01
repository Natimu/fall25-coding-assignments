using Microsoft.AspNetCore.Mvc;
using System.Collections.Generic;
using System.Linq;
using TinyMartAPI.Models;
namespace TinyMartAPI.Controllers
{
    [ApiController]
    [Route("api/[controller]")]

    public class PaperBookController : ControllerBase
    {
        private static List<BookProduct> _books = new List<BookProduct>();

        [HttpGet]
        public ActionResult<IEnumerable<BookProduct>> GetAllBooks()
        {
            return Ok(_books);
        }

        [HttpGet("{id}")]
        public ActionResult<BookProduct> GetBooks(int id)
        {
            var book = _books.FirstOrDefault(b => b.ProductID == id);
            if (book == null) return NotFound();
            return Ok(book);
        }

        [HttpPost]
        public ActionResult<BookProduct> AllBooks(BookProduct newBook)
        {
            _books.Add(newBook);
            return CreatedAtAction(nameof(GetBooks), new { id = newBook.ProductID }, newBook);

        }

        [HttpPut]
        public ActionResult UpdateBooks(int id, BookProduct updatedBook)
        {
            var book = _books.FirstOrDefault(b => b.ProductID == id);
            if (book == null) return NotFound();

            book.Author = updatedBook.Author;
            book.Price = updatedBook.Price;
            book.ProductName = updatedBook.ProductName;
            book.Pages = updatedBook.Pages;

            return NoContent();
        }

                [HttpDelete("{id}")]
        public ActionResult DeleteAudio(int id)
        {
            var audio = _books.FirstOrDefault(a => a.ProductID == id);
            if (audio == null) return NotFound();
            _books.Remove(audio);
            return NoContent();

        }


    }
}