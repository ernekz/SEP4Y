using System;
using System.Collections.Generic;

namespace SEP_DataAPI.Model
{
    public partial class Facts
    {
        public int FactId { get; set; }
        public int DimId { get; set; }
        public int RoomId { get; set; }
        public int SensorsId { get; set; }
        public int? Timespan { get; set; }

        public virtual DateDim Dim { get; set; }
        public virtual RoomDim Room { get; set; }
        public virtual SensorDim Sensors { get; set; }
    }
}
