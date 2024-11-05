using Actual_lab_1.Enums;

namespace Actual_lab_1.Extensions
{
    public static class EnumExtensions
    {
        public static char TranlateToOutput(this FieldItem fieldItem)
        {
            return fieldItem switch
            {
                FieldItem.Water => '-',
                FieldItem.Battleship => '-',
                FieldItem.Miss => '.',
                FieldItem.Hit => 'X',
                _ => throw new NotImplementedException(),
            };
        }

        public static bool IsArrow(this ConsoleKey key)
        {
            return key is ConsoleKey.UpArrow or ConsoleKey.DownArrow or ConsoleKey.LeftArrow or ConsoleKey.RightArrow;
        }
    }
}
