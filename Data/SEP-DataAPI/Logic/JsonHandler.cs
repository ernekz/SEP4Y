using System.Collections.Generic;
using Newtonsoft.Json;
using SEP_DataAPI.Model;

namespace SEP_DataAPI.Logic
{
    public class JsonHandler
    {
        public string serializeAccounts(List<Account> list)
        {
            string Json = JsonConvert.SerializeObject(list);
            return Json;
        }

        // Serializes a list of environmental data
        public string serializeEnvironmentalData(List<EnvironmentalData> list)
        {
            string Json = JsonConvert.SerializeObject(list);
            return Json;
        }

        // deserializes a json to a single account object
        public Account deSerializeAccount(string json)
        {
            Account account = (Account) JsonConvert.DeserializeObject(json);
            return account;
        }


    }
}