using Lab_1.Domain.Enums;
using Lab_1.Features.Output;

namespace Lab_1.Features.GameLoop.Field;

internal static class FieldItemOutputTranslator
{
    public static OutputModel TranlateToOutput(this FieldItem fieldItem)
    {
        return fieldItem switch
        {
            FieldItem.Water => new OutputModel(' ', ConsoleColor.White, ConsoleColor.Black),
            FieldItem.Battleship => new OutputModel(' ', ConsoleColor.White, ConsoleColor.Black),
            FieldItem.Miss => new OutputModel('.', ConsoleColor.White, ConsoleColor.Black),
            FieldItem.Hit => new OutputModel('H', ConsoleColor.Red, ConsoleColor.Black),
            _ => throw new NotImplementedException(),
        };
    }
}
