namespace ConsoleEngine.Features.Output
{
    internal class OutputItem
    {
        public char Character { get; init; }

        public ConsoleColor Foreground { get; init; } = ConsoleColor.White;
        public ConsoleColor Background { get; init; } = ConsoleColor.Black;
    }
}
