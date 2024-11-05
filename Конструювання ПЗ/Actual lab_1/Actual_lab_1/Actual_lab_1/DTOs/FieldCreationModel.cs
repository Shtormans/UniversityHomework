using System.Drawing;

namespace Actual_lab_1.DTOs
{
    public class FieldCreationModel
    {
        public required Size FieldSize { get; init; }
        public required int BattleshipsAmount { get; init; }
        public required List<Size> BattleshipVariations { get; init; }
    }
}
