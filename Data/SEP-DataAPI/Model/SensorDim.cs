using System;
using System.Collections.Generic;

namespace SEP_DataAPI.Model
{
    public partial class SensorDim
    {
        public SensorDim()
        {
            Facts = new HashSet<Fact>();
        }

        public int SensorId { get; set; }

        public virtual ICollection<Fact> Facts { get; set; }
    }
}
