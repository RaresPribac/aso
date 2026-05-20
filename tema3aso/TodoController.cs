using Microsoft.AspNetCore.Mvc;
using System.Collections.Generic;
using System.Linq;

namespace TodoASO.Controllers
{
    [ApiController]
    [Route("api/[controller]")]
    public class TodoController : ControllerBase
    {
        private static List<TodoItem> listaSarcini = new List<TodoItem>
        {
            new TodoItem { Id = 1, Titlu = "Invata pentru laboratorul de ASO", EsteFinalizat = false }
        };

        [HttpGet]
        public ActionResult<IEnumerable<TodoItem>> ObtineToate()
        {
            return listaSarcini;
        }

        [HttpPost]
        public ActionResult<TodoItem> AdaugaSarcina(TodoItem sarcinaNoua)
        {
            sarcinaNoua.Id = listaSarcini.Count > 0 ? listaSarcini.Max(x => x.Id) + 1 : 1;
            listaSarcini.Add(sarcinaNoua);

            return Ok(sarcinaNoua);
        }

        [HttpDelete("{id}")]
        public IActionResult StergeSarcina(int id)
        {
            var sarcinaDeSters = listaSarcini.FirstOrDefault(x => x.Id == id);

            if (sarcinaDeSters == null)
            {
                return NotFound(); 
            }

            listaSarcini.Remove(sarcinaDeSters);
            return NoContent(); 
        }
    }
}