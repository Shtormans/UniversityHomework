using System.Drawing;

namespace Lab_1.Features.GameLoop.Field;

internal class FieldCreationModel
{
    public required Size FieldSize { get; init; }
    public required int BattleshipsAmount { get; init; }
    public required List<Size> BattleshipVariations { get; init; }
}
