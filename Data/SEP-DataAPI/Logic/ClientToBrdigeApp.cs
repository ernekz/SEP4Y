using System.Threading.Tasks;
using System.Net.Http;
using Newtonsoft.Json;
using System.Text;
using System;
using System.Collections.Generic;

namespace SEP_DataAPI.Logic
{
    class ClientToBridgeApp
    {
        public ClientToBridgeApp() { }
        
        // Sends a basic get request to the specified URL
        public async void GetShutLED()
        {
            string url = "https://localhost:5001/api/login/";
            HttpClient client = new HttpClient();
            await client.GetAsync(url).ConfigureAwait(false);
        }  
    }
}
