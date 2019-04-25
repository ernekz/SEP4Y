using System.Collections.Generic;
using Microsoft.AspNetCore.Mvc;
using SEP_DataAPI.Logic;
using SEP_DataAPI.Model;

namespace SEP_DataAPI.Controllers
{
    // controller for endpoint ~/api/Login in the webAPI

    [Route("[controller]")]
    [ApiController]
    public class AccountController : ControllerBase
    {
        // GET /Account/1
         [HttpGet("{id}")]
        public ActionResult<string> Get(int id)
        {
            DatabaseHandler dbHandler = new DatabaseHandler();
            JsonHandler jsonHandler = new JsonHandler();
            List<Account> list = new List<Account>();
            string json = "";

            
            list.Add(dbHandler.getAccById(id));
            json = jsonHandler.serializeAccounts(list);

            return json;
            
        }  
    } 
}
