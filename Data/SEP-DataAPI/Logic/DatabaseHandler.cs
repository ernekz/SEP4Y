using System.Collections.Generic;
using SEP_DataAPI.Model;

namespace SEP_DataAPI.Logic
{
    public class DatabaseHandler
    {
        public List<Account> getAllAccs()
        {
            List<Account> list = new List<Account>();
            Account acc = new Account("Joe", "Joe's pw", false);
            Account acc2 = new Account("Joe2", "Joe's pw2", false);

            list.Add(acc);
            list.Add(acc2);

            return list;
        }

        public Account getAccById(int id)
        {
            Account acc = new Account("Joe's sample acc that got queried", "Joe's pw", false);
            return acc;
        }

        public void editAccount(Account Account)
        {
            System.Console.WriteLine("edit ready");

        }

        public void removeAccount(int id)
        {
            System.Console.WriteLine("remove ready");
        }

        public List<EnvironmentalData> getAllEnvironmentalData()
        {
            List<EnvironmentalData> list = new List<EnvironmentalData>();
            EnvironmentalData aTestEnvironmentalData1 = new EnvironmentalData("D304", 767, 24, "2012");
            EnvironmentalData aTestEnvironmentalData2 = new EnvironmentalData("C201", 891, 22, "2013");

            list.Add(aTestEnvironmentalData1);
            list.Add(aTestEnvironmentalData2);

            return list;
        }

    }
}