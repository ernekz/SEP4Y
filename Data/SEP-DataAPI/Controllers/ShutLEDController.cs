using System.Collections.Generic;
using Microsoft.AspNetCore.Mvc;
using SEP_DataAPI.Logic;
using SEP_DataAPI.Model;

namespace SEP_DataAPI.Controllers
{
    [Route("[controller]")]
    [ApiController]
    public class ShutLEDController : ControllerBase
    {
        // GET /ShutLED
        // HTTP request receiver for shutting down the LED
        [HttpGet]
        public void Get()
        {
            ClientToBridgeApp client = new ClientToBridgeApp();
            client.GetShutLED();
        }        
    } 
}
