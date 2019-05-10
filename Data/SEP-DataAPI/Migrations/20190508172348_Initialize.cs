using System;
using Microsoft.EntityFrameworkCore.Metadata;
using Microsoft.EntityFrameworkCore.Migrations;

namespace SEP_DataAPI.Migrations
{
    public partial class Initialize : Migration
    {
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.CreateTable(
                name: "Accounts",
                columns: table => new
                {
                    username = table.Column<string>(maxLength: 50, nullable: false),
                    password = table.Column<string>(maxLength: 50, nullable: false),
                    isAdmin = table.Column<bool>(nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_Accounts", x => x.username);
                });

            migrationBuilder.CreateTable(
                name: "Date_Dim",
                columns: table => new
                {
                    Dim_ID = table.Column<int>(nullable: false)
                        .Annotation("SqlServer:ValueGenerationStrategy", SqlServerValueGenerationStrategy.IdentityColumn),
                    Date = table.Column<DateTime>(type: "date", nullable: false),
                    Year = table.Column<int>(nullable: false),
                    Quarter = table.Column<int>(nullable: false),
                    Month = table.Column<int>(nullable: false),
                    Week = table.Column<int>(nullable: false),
                    Day = table.Column<int>(nullable: false),
                    DayOfWeek = table.Column<string>(maxLength: 10, nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_Date_Dim", x => x.Dim_ID);
                });

            migrationBuilder.CreateTable(
                name: "Room_Dim",
                columns: table => new
                {
                    Room_ID = table.Column<int>(nullable: false)
                        .Annotation("SqlServer:ValueGenerationStrategy", SqlServerValueGenerationStrategy.IdentityColumn),
                    Name = table.Column<string>(unicode: false, maxLength: 50, nullable: true),
                    DataCreated = table.Column<DateTime>(type: "datetime", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_Room_Dim", x => x.Room_ID);
                });

            migrationBuilder.CreateTable(
                name: "Sensor_Dim",
                columns: table => new
                {
                    Sensors_ID = table.Column<int>(nullable: false)
                        .Annotation("SqlServer:ValueGenerationStrategy", SqlServerValueGenerationStrategy.IdentityColumn)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_Sensor_Dim", x => x.Sensors_ID);
                });

            migrationBuilder.CreateTable(
                name: "Time_Dim",
                columns: table => new
                {
                    Dim_ID = table.Column<int>(nullable: false)
                        .Annotation("SqlServer:ValueGenerationStrategy", SqlServerValueGenerationStrategy.IdentityColumn),
                    Time = table.Column<TimeSpan>(type: "time", nullable: false),
                    Hour = table.Column<int>(nullable: false),
                    Minute = table.Column<int>(nullable: false),
                    Second = table.Column<int>(nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_Time_Dim", x => x.Dim_ID);
                });

            migrationBuilder.CreateTable(
                name: "Facts",
                columns: table => new
                {
                    Fact_ID = table.Column<int>(nullable: false)
                        .Annotation("SqlServer:ValueGenerationStrategy", SqlServerValueGenerationStrategy.IdentityColumn),
                    Dim_ID = table.Column<int>(nullable: false),
                    Time_ID = table.Column<int>(nullable: false),
                    Room_ID = table.Column<int>(nullable: false),
                    Sensor_ID = table.Column<int>(nullable: false),
                    Temp_c = table.Column<double>(nullable: true),
                    Temp_f = table.Column<double>(nullable: true),
                    CO2 = table.Column<decimal>(type: "decimal(10, 2)", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_Facts", x => x.Fact_ID);
                    table.ForeignKey(
                        name: "FK_Facts_Date_Dim",
                        column: x => x.Dim_ID,
                        principalTable: "Date_Dim",
                        principalColumn: "Dim_ID",
                        onDelete: ReferentialAction.Restrict);
                    table.ForeignKey(
                        name: "FK_Facts_Room_Dim",
                        column: x => x.Room_ID,
                        principalTable: "Room_Dim",
                        principalColumn: "Room_ID",
                        onDelete: ReferentialAction.Restrict);
                    table.ForeignKey(
                        name: "FK_Facts_Sensor_Dim",
                        column: x => x.Sensor_ID,
                        principalTable: "Sensor_Dim",
                        principalColumn: "Sensors_ID",
                        onDelete: ReferentialAction.Restrict);
                    table.ForeignKey(
                        name: "FK_Facts_Time_Dim",
                        column: x => x.Time_ID,
                        principalTable: "Time_Dim",
                        principalColumn: "Dim_ID",
                        onDelete: ReferentialAction.Restrict);
                });

            migrationBuilder.CreateIndex(
                name: "IX_Facts_Dim_ID",
                table: "Facts",
                column: "Dim_ID");

            migrationBuilder.CreateIndex(
                name: "IX_Facts_Room_ID",
                table: "Facts",
                column: "Room_ID");

            migrationBuilder.CreateIndex(
                name: "IX_Facts_Sensor_ID",
                table: "Facts",
                column: "Sensor_ID");

            migrationBuilder.CreateIndex(
                name: "IX_Facts_Time_ID",
                table: "Facts",
                column: "Time_ID");
        }

        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropTable(
                name: "Accounts");

            migrationBuilder.DropTable(
                name: "Facts");

            migrationBuilder.DropTable(
                name: "Date_Dim");

            migrationBuilder.DropTable(
                name: "Room_Dim");

            migrationBuilder.DropTable(
                name: "Sensor_Dim");

            migrationBuilder.DropTable(
                name: "Time_Dim");
        }
    }
}
