using System;
using System.Collections.Generic;

namespace SEP_DataAPI.Model
{
    public partial class RoomDim
    {
        public RoomDim()
        {
            Facts = new HashSet<Fact>();
        }

        public int RoomId { get; set; }
        public string Teacher { get; set; }
        public DateTime? DataCreated { get; set; }

        public virtual ICollection<Fact> Facts { get; set; }
    }
}
