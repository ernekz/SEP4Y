using Microsoft.EntityFrameworkCore.Migrations;

namespace SEP_DataAPI.Migrations
{
    public partial class Renamed : Migration
    {
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.RenameColumn(
                name: "Dim_ID",
                table: "Facts",
                newName: "Date_ID");

            migrationBuilder.RenameIndex(
                name: "IX_Facts_Dim_ID",
                table: "Facts",
                newName: "IX_Facts_Date_ID");
        }

        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.RenameColumn(
                name: "Date_ID",
                table: "Facts",
                newName: "Dim_ID");

            migrationBuilder.RenameIndex(
                name: "IX_Facts_Date_ID",
                table: "Facts",
                newName: "IX_Facts_Dim_ID");
        }
    }
}
