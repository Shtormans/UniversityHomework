namespace Lab_1.Features.Output
{
    internal interface IOutputService
    {
        public void Display(OutputModel[,] ouputMatrix);
        public void DisplatString(string text, ConsoleColor foregroundColor = ConsoleColor.White, ConsoleColor backgroundColor = ConsoleColor.Black);
    }
}
