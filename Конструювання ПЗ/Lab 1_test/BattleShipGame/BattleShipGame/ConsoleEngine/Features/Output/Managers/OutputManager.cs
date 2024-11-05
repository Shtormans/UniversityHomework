using ConsoleEngine.Domain.Abstractions;

namespace ConsoleEngine.Features.Output
{
    internal class OutputManager : GameManager
    {
        private OutputItem[,] _lastOutputMatrix;

        public override void Init()
        {
            _lastOutputMatrix = new OutputItem[0,0];
        }

        public void Output(OutputItem[,] ouputMatrix)
        {
            ClearScreen();
            OutputMatrix(ouputMatrix);

            _lastOutputMatrix = ouputMatrix;
        }

        private void ClearScreen()
        {
            int rowsAmount = _lastOutputMatrix.GetLength(0);
            int columnsAmount = _lastOutputMatrix.GetLength(1);

            Console.SetCursorPosition(0,0);
         
            for (int row = 0; row < rowsAmount; row++)
            {
                Console.WriteLine(new string(' ', columnsAmount));
            }
        }

        private void OutputMatrix(OutputItem[,] outputMatrix)
        {
            int rowsAmount = outputMatrix.GetLength(0);
            int columnsAmount = outputMatrix.GetLength(1);

            Console.SetCursorPosition(0, 0);

            for (int row = 0; row < rowsAmount; row++)
            {
                for (int column = 0; column < columnsAmount; column++)
                {
                    OutputItem item = outputMatrix[row, column];

                    Console.ForegroundColor = item.Foreground;
                    Console.BackgroundColor = item.Background;

                    Console.Write(item.Character);
                }
            }
        }
    }
}
