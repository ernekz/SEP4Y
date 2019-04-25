using System.Collections.Generic;
using Microsoft.AspNetCore.Mvc;
using SEP_DataAPI.Logic;
using SEP_DataAPI.Model;

namespace SEP_DataAPI.Controllers
{
    [Route("[controller]")]
    [ApiController]
    public class RemoveAccountController : ControllerBase
    {
        // Get /RemoveAccount/43
        [HttpDelete("{id}")]
        public void Delete(int id)
        {
            DatabaseHandler dbHandler = new DatabaseHandler();

            dbHandler.removeAccount(id);
        }        
    } 
}
