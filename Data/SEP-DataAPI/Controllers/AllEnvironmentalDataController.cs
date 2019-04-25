using System.Collections.Generic;
using Microsoft.AspNetCore.Mvc;
using SEP_DataAPI.Logic;
using SEP_DataAPI.Model;

namespace SEP_DataAPI.Controllers
{
    [Route("[controller]")]
    [ApiController]
    public class AllEnvironmentalDataController : ControllerBase
    {
        // Get /AllEnvironmentalData
        [HttpGet]
        public string Get()
        {
            DatabaseHandler dbHandler = new DatabaseHandler();
            JsonHandler jsonHandler = new JsonHandler();
            List<EnvironmentalData> list = new List<EnvironmentalData>();
            string json = "";

            list = dbHandler.getAllEnvironmentalData();
            json = jsonHandler.serializeEnvironmentalData(list);

            return json;
        }        
    } 
}
