using Actual_lab_1.Enums;

namespace Actual_lab_1.DTOs
{
    public class GameData
    {
        public FieldItem[,] Field { get; set; }
        public int Bullets { get; set; }
        public int ShipCells { get; set; }
    }
}
