using System;
using Newtonsoft.Json;

namespace SEP_DataAPI.Model
{
    public class Account 
    {
    [JsonProperty]
    private String userName;
    [JsonProperty]
    private String password;
    [JsonProperty]
    private bool IsAdmin;

    public Account(String userName, String password, bool isAdmin) {
        this.userName = userName;
        this.password = password;
        this.IsAdmin = isAdmin;
    }

    public String getUserName() {
        return userName;
    }

    public void setUserName(String userName) {
        this.userName = userName;
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    public bool isAdmin() {
        return IsAdmin;
    }

    public void setAdmin(bool admin) {
        IsAdmin = admin;
    }
    }
}