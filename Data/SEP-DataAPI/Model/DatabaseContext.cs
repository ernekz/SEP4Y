using System;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Metadata;

namespace SEP_DataAPI.Model
{
    public partial class DatabaseContext : DbContext
    {
        public DatabaseContext()
        {
        }

        public DatabaseContext(DbContextOptions<DatabaseContext> options)
            : base(options)
        {
        }

        public virtual DbSet<DateDim> DateDim { get; set; }
        public virtual DbSet<Fact> Facts { get; set; }
        public virtual DbSet<RoomDim> RoomDim { get; set; }
        public virtual DbSet<SensorDim> SensorDim { get; set; }
        public virtual DbSet<Account> Accounts { get; set; }

        protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder)
        {
            if (!optionsBuilder.IsConfigured)
            {
                optionsBuilder.UseSqlServer("DefaultConnection");
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

            modelBuilder.Entity<Fact>(entity =>
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

            modelBuilder.Entity<Account>(entity =>
            {
                entity.HasKey(e => e.Username);

                entity.Property(e => e.Password)
                    .IsRequired()
                    .HasColumnName("password")
                    .HasMaxLength(50);

                entity.Property(e => e.Username)
                    .IsRequired()
                    .HasColumnName("username")
                    .HasMaxLength(50);
            });
        }
    }
}