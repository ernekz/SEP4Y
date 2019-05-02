using System;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Metadata;

namespace SEP_DataAPI.Model
{
    public partial class whateverContext : DbContext
    {
        public whateverContext()
        {
        }

        public whateverContext(DbContextOptions<whateverContext> options)
            : base(options)
        {
        }

        public virtual DbSet<DateDim> DateDim { get; set; }
        public virtual DbSet<Facts> Facts { get; set; }
        public virtual DbSet<RoomDim> RoomDim { get; set; }
        public virtual DbSet<SensorDim> SensorDim { get; set; }

        protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder)
        {
            if (!optionsBuilder.IsConfigured)
            {
#warning To protect potentially sensitive information in your connection string, you should move it out of source code. See http://go.microsoft.com/fwlink/?LinkId=723263 for guidance on storing connection strings.
                optionsBuilder.UseSqlServer("Server=10.200.131.2;Database=whatever;User Id=groupY1;Password=groupY1;Trusted_Connection=False;");
            }
        }

        protected override void OnModelCreating(ModelBuilder modelBuilder)
        {
            modelBuilder.HasAnnotation("ProductVersion", "2.2.4-servicing-10062");

            modelBuilder.Entity<DateDim>(entity =>
            {
                entity.HasKey(e => e.DimId);

                entity.ToTable("Date_Dim");

                entity.Property(e => e.DimId).HasColumnName("Dim_ID");

                entity.Property(e => e.Date).HasColumnType("date");

                entity.Property(e => e.DayOfWeek)
                    .IsRequired()
                    .HasMaxLength(10);
            });

            modelBuilder.Entity<Facts>(entity =>
            {
                entity.HasKey(e => e.FactId);

                entity.Property(e => e.FactId).HasColumnName("Fact_ID");

                entity.Property(e => e.DimId).HasColumnName("Dim_ID");

                entity.Property(e => e.RoomId).HasColumnName("Room_ID");

                entity.Property(e => e.SensorsId).HasColumnName("Sensors_ID");

                entity.HasOne(d => d.Dim)
                    .WithMany(p => p.Facts)
                    .HasForeignKey(d => d.DimId)
                    .OnDelete(DeleteBehavior.ClientSetNull)
                    .HasConstraintName("FK_Facts_Date_Dim");

                entity.HasOne(d => d.Room)
                    .WithMany(p => p.Facts)
                    .HasForeignKey(d => d.RoomId)
                    .OnDelete(DeleteBehavior.ClientSetNull)
                    .HasConstraintName("FK_Facts_Room_Dim");

                entity.HasOne(d => d.Sensors)
                    .WithMany(p => p.Facts)
                    .HasForeignKey(d => d.SensorsId)
                    .OnDelete(DeleteBehavior.ClientSetNull)
                    .HasConstraintName("FK_Facts_Sensor_Dim");
            });

            modelBuilder.Entity<RoomDim>(entity =>
            {
                entity.HasKey(e => e.RoomId);

                entity.ToTable("Room_Dim");

                entity.Property(e => e.RoomId).HasColumnName("Room_ID");

                entity.Property(e => e.DataCreated).HasColumnType("datetime");

                entity.Property(e => e.Teacher)
                    .HasMaxLength(50)
                    .IsUnicode(false);
            });

            modelBuilder.Entity<SensorDim>(entity =>
            {
                entity.HasKey(e => e.SensorsId);

                entity.ToTable("Sensor_Dim");

                entity.Property(e => e.SensorsId).HasColumnName("Sensors_ID");

                entity.Property(e => e.Co2)
                    .HasColumnName("CO2")
                    .HasColumnType("decimal(10, 2)");

                entity.Property(e => e.TempC).HasColumnName("Temp_c");

                entity.Property(e => e.TempF).HasColumnName("Temp_f");
            });
        }
    }
}
