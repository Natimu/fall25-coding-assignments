using Microsoft.AspNetCore.Mvc;
using System.Collections.Generic;
using System.Linq;
using TinyMartAPI.Models;


namespace TinyMartAPI.Controllers
{
    [ApiController]
    [Route("api/[controller]")]

    public class AudioController : ControllerBase
    {
        private static List<AudioProduct> _audios = new List<AudioProduct>();

        [HttpGet]
        public ActionResult<IEnumerable<AudioProduct>> GetAllAudio()
        {
            return Ok(_audios);
        }

        [HttpGet("{id}")]
        public ActionResult<AudioProduct> GetAudio(int id)
        {
            var audio = _audios.FirstOrDefault(a => a.ProductID == id);
            if (audio == null) return NotFound();
            return Ok(audio);
        }

        [HttpPost]
        public ActionResult<AudioProduct> AddAudio(AudioProduct newAudio)
        {
            if (newAudio.ProductID == 0) // only set if not already provided
            {
                newAudio.SetProdID(Product.CreateNewID());
            }
            _audios.Add(newAudio);
            return CreatedAtAction(nameof(GetAudio), new { id = newAudio.ProductID }, newAudio);
        }

        [HttpPut("{id}")]
        public ActionResult UpdateAudio(int id, AudioProduct updatedAudio)
        {
            var audio = _audios.FirstOrDefault(a => a.ProductID == id);
            if (audio == null) return NotFound();

            audio.Genre = updatedAudio.Genre;
            audio.Price = updatedAudio.Price;
            audio.ProductName = updatedAudio.ProductName;
            audio.Singer = updatedAudio.Singer;

            return NoContent();

        }

        [HttpDelete("{id}")]
        public ActionResult DeleteAudio(int id)
        {
            var audio = _audios.FirstOrDefault(a => a.ProductID == id);
            if (audio == null) return NotFound();
            _audios.Remove(audio);
            return NoContent();

        }
    }
}