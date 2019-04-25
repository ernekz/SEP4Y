using System.Collections.Generic;
using Microsoft.AspNetCore.Mvc;
using SEP_DataAPI.Logic;
using SEP_DataAPI.Model;

namespace SEP_DataAPI.Controllers
{
    // controller for endpoint ~/api/Login in the webAPI

    [Route("[controller]")]
    [ApiController]
    public class AllAccountsController : ControllerBase
    {
        // GET /AllAccounts
        [HttpGet]
        public ActionResult<string> Get()
        {
            DatabaseHandler dbHandler = new DatabaseHandler();
            JsonHandler jsonHandler = new JsonHandler();
            List<Account> list = new List<Account>();
            string json = "";

            list = dbHandler.getAllAccs();
            json = jsonHandler.serializeAccounts(list);

            return json;
        }        
    } 
}
