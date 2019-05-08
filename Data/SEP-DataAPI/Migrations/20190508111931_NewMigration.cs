using System;
using Microsoft.EntityFrameworkCore.Metadata;
using Microsoft.EntityFrameworkCore.Migrations;

namespace SEP_DataAPI.Migrations
{
    public partial class NewMigration : Migration
    {
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropColumn(
                name: "CO2",
                table: "Sensor_Dim");

            migrationBuilder.DropColumn(
                name: "Temp_c",
                table: "Sensor_Dim");

            migrationBuilder.DropColumn(
                name: "Temp_f",
                table: "Sensor_Dim");

            migrationBuilder.DropColumn(
                name: "Timespan",
                table: "Facts");

            migrationBuilder.RenameColumn(
                name: "Teacher",
                table: "Room_Dim",
                newName: "Name");

            migrationBuilder.AddColumn<decimal>(
                name: "CO2",
                table: "Facts",
                type: "decimal(10, 2)",
                nullable: true);

            migrationBuilder.AddColumn<double>(
                name: "Temp_c",
                table: "Facts",
                nullable: true);

            migrationBuilder.AddColumn<double>(
                name: "Temp_f",
                table: "Facts",
                nullable: true);

            migrationBuilder.AddColumn<int>(
                name: "Time_ID",
                table: "Facts",
                nullable: false,
                defaultValue: 0);

            migrationBuilder.AddColumn<int>(
                name: "Day",
                table: "Date_Dim",
                nullable: false,
                defaultValue: 0);

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

            migrationBuilder.CreateIndex(
                name: "IX_Facts_Time_ID",
                table: "Facts",
                column: "Time_ID");

            migrationBuilder.AddForeignKey(
                name: "FK_Facts_Time_Dim",
                table: "Facts",
                column: "Time_ID",
                principalTable: "Time_Dim",
                principalColumn: "Dim_ID",
                onDelete: ReferentialAction.Restrict);
        }

        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropForeignKey(
                name: "FK_Facts_Time_Dim",
                table: "Facts");

            migrationBuilder.DropTable(
                name: "Time_Dim");

            migrationBuilder.DropIndex(
                name: "IX_Facts_Time_ID",
                table: "Facts");

            migrationBuilder.DropColumn(
                name: "CO2",
                table: "Facts");

            migrationBuilder.DropColumn(
                name: "Temp_c",
                table: "Facts");

            migrationBuilder.DropColumn(
                name: "Temp_f",
                table: "Facts");

            migrationBuilder.DropColumn(
                name: "Time_ID",
                table: "Facts");

            migrationBuilder.DropColumn(
                name: "Day",
                table: "Date_Dim");

            migrationBuilder.RenameColumn(
                name: "Name",
                table: "Room_Dim",
                newName: "Teacher");

            migrationBuilder.AddColumn<decimal>(
                name: "CO2",
                table: "Sensor_Dim",
                type: "decimal(10, 2)",
                nullable: true);

            migrationBuilder.AddColumn<double>(
                name: "Temp_c",
                table: "Sensor_Dim",
                nullable: true);

            migrationBuilder.AddColumn<double>(
                name: "Temp_f",
                table: "Sensor_Dim",
                nullable: true);

            migrationBuilder.AddColumn<int>(
                name: "Timespan",
                table: "Facts",
                nullable: true);
        }
    }
}
