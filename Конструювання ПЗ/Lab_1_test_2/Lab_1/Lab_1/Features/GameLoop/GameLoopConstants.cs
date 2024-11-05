using System.Drawing;

namespace Lab_1.Features.GameLoop;

internal static class GameLoopConstants
{
    public const int BattleShipsAmount = 2;
    public static readonly List<Size> BattleShipsVariations = [new Size(3, 1), new Size(1, 3)];

    public static class Texts
    {
        public const string InputFieldHeight = "Field height: ";
        public const string InputFieldWidth = "Field width: ";
        public const string InputBulletsAmount = "Bullets amount: ";
        public const string InputAgain = "Failed! Input again: ";
        public const string FailedToCreateField = "Failed to create field! Try again!";
    }
}
