using System;
using System.Collections.Generic;

namespace SEP_DataAPI.Model
{
    public partial class DateDim
    {
        public DateDim()
        {
            Facts = new HashSet<Fact>();
        }

        public int DimId { get; set; }
        public DateTime Date { get; set; }
        public int Year { get; set; }
        public int Quarter { get; set; }
        public int Month { get; set; }
        public int Week { get; set; }
        public string DayOfWeek { get; set; }

        public virtual ICollection<Fact> Facts { get; set; }
    }
}
