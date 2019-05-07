using System;
using System.Collections.Generic;

namespace SEP_DataAPI.Model
{
    public partial class TimeDim
    {
        public TimeDim()
        {
            Facts = new HashSet<Fact>();
        }

        public int TimeId { get; set; }
        public DateTime Time { get; set; }
        public int Hour { get; set; }
        public int Minute { get; set; }
        public int Second { get; set; }
    
        public virtual ICollection<Fact> Facts { get; set; }
    }
}
