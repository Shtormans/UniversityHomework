namespace Lab_1.Features.Output
{
    internal class OutputService : IOutputService
    {
        private const int MaxStringLength = 50;

        private OutputModel[,] _lastOutputMatrix;

        public OutputService()
        {
            _lastOutputMatrix = new OutputModel[0, 0];
        }

        public void DisplatString(string text, ConsoleColor foregroundColor = ConsoleColor.White, ConsoleColor backgroundColor = ConsoleColor.Black)
        {
            OutputModel[,] outputMatrix = ParseStringToMatrix(text, foregroundColor, backgroundColor);
            Display(outputMatrix);
        }

        public void Display(OutputModel[,] outputMatrix)
        {
            ClearScreen();
            OutputMatrix(outputMatrix);

            _lastOutputMatrix = outputMatrix;
        }

        private void ClearScreen()
        {
            int rowsAmount = _lastOutputMatrix.GetLength(0);
            int columnsAmount = _lastOutputMatrix.GetLength(1);

            Console.SetCursorPosition(0, 0);

            for (int row = 0; row < rowsAmount; row++)
            {
                Console.WriteLine(new string(' ', columnsAmount));
            }
        }

        private void OutputMatrix(OutputModel[,] outputMatrix)
        {
            int rowsAmount = outputMatrix.GetLength(0);
            int columnsAmount = outputMatrix.GetLength(1);

            Console.SetCursorPosition(0, 0);

            for (int row = 0; row < rowsAmount; row++)
            {
                for (int column = 0; column < columnsAmount; column++)
                {
                    OutputModel item = outputMatrix[row, column];

                    Console.ForegroundColor = item.Foreground;
                    Console.BackgroundColor = item.Background;

                    Console.Write(item.Character);
                }
            }
        }

        private OutputModel[,] ParseStringToMatrix(string text, ConsoleColor foregroundColor = ConsoleColor.White, ConsoleColor backgroundColor = ConsoleColor.Black)
        {
            char[] characters = text.ToCharArray();
            int rowsAmount = characters.Length / MaxStringLength + 1;

            OutputModel[,] outputMatrix = new OutputModel[rowsAmount, MaxStringLength];

            for (int i = 0; i < characters.Length; i++)
            {
                int row = i / MaxStringLength;
                int column = i % MaxStringLength;

                outputMatrix[row, column] = new OutputModel()
                {
                    Character = characters[i],
                    Foreground = foregroundColor,
                    Background = backgroundColor
                };
            }

            return outputMatrix;
        }
    }
}
