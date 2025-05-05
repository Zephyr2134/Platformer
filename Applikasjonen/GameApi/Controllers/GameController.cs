using Microsoft.AspNetCore.Mvc;
using GameApi.Models;

namespace GameApi.Controllers;

[ApiController]
[Route("[controller]")]
public class GameController : ControllerBase
{
    [HttpPost]
    public ActionResult login([FromBody]LoginInfo info)
    {
        if(info.Username == "admin" && info.Password == "password")
        {
        return Ok(NoContent());
        }
        return BadRequest();
    }
}
