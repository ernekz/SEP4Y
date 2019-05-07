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

        public int SensorsId { get; set; }

        public virtual ICollection<Fact> Facts { get; set; }
    }
}
