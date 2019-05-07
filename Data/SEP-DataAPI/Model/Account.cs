using System;
using System.Collections.Generic;

namespace SEP_DataAPI.Model
{
    public partial class Account
    {
        public string Username { get; set; }
        public string Password { get; set; }
        public bool isAdmin {get; set;}
    }
}
