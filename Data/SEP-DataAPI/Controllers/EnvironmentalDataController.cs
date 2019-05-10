using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using SEP_DataAPI.Model;

namespace SEP_DataAPI.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class EnvironmentalDataController : ControllerBase
    {
        private readonly DatabaseContext _context;

        public EnvironmentalDataController(DatabaseContext context)
        {
            _context = context;
        }

        // GET api/environmentaldata
        [HttpGet]
        public List<EnvironmentalData> Get()
        {
            List<EnvironmentalData> envDataList = new List<EnvironmentalData> { };
            var result = _context.Facts.GroupBy(x => x.RoomId)
                        .Select(x => x.OrderByDescending(y => y.DateId)
                        .OrderByDescending(z => z.TimeId).First());

            foreach (var x in result)
            {
                string roomName = _context.RoomDim.Find(x.RoomId).Name;
                string timeString = _context.TimeDim.Find(x.TimeId).Time.ToString();
                string dateString = _context.DateDim.Find(x.DateId).Date.ToShortDateString();
                EnvironmentalData envDataObject = new EnvironmentalData
                {
                location = roomName,
                temperature = x.TempC.ToString(),
                time = timeString,
                date = dateString,
                co2 = x.Co2.ToString()
                };
                envDataList.Add(envDataObject);
            }
            return envDataList;
        }

        // GET api/EnvironmentalData/1
        [HttpGet("{id}")]
        public EnvironmentalData Get(int id)
        {
            var result = _context.Facts.Where(x => x.RoomId == id)
                      .OrderByDescending(x => x.DateId)
                      .OrderByDescending(x => x.TimeId).First();
            string roomName = _context.RoomDim.Find(id).Name;
            string timeString = _context.TimeDim.Find(result.TimeId).Time.ToString();
            string dateString = _context.DateDim.Find(result.DateId).Date.ToShortDateString();
            EnvironmentalData data = new EnvironmentalData {
                location = roomName,
                temperature = result.TempC.ToString(),
                time = timeString,
                date = dateString,
                co2 = result.Co2.ToString()
            };
            return data;
        }

        // POST api/values
        [HttpPost]
        public void Post([FromBody] string value)
        {         
        }

        // PUT api/values/5
        [HttpPut("{id}")]
        public void Put(int id, [FromBody] string value)
        {
        }

        // DELETE api/values/5
        [HttpDelete("{id}")]
        public void Delete(int id)
        {
        }
    }
}