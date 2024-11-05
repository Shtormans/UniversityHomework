namespace Lab_1.Features.Output
{
    internal class OutputModel
    {
        public OutputModel() { }

        public OutputModel(char character, ConsoleColor foreground, ConsoleColor background)
        {
            Character = character;
            Foreground = foreground;
            Background = background;
        }

        public char Character { get; init; } = ' ';
        public ConsoleColor Foreground { get; init; } = ConsoleColor.White;
        public ConsoleColor Background { get; init; } = ConsoleColor.Black;
    }
}
