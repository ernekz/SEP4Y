using System;
using System.Collections.Generic;

namespace SEP_DataAPI.Model
{
    public partial class Fact
    {
        public int FactId { get; set; }
        public int DimId { get; set; }
        public int TimeId { get; set; }
        public int RoomId { get; set; }
        public int SensorsId { get; set; }
        public double? TempC { get; set; }
        public double? TempF { get; set; }
        public decimal? Co2 { get; set; }
        public virtual DateDim Date { get; set; }
        public virtual TimeDim Time { get; set; }
        public virtual RoomDim Room { get; set; }
        public virtual SensorDim Sensors { get; set; }
    }
}
