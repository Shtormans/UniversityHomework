using Actual_lab_1.DTOs;
using Actual_lab_1.Enums;
using Actual_lab_1.Factories;
using System.Drawing;

namespace Actual_lab_1
{
    public class GameInitializer
    {
        private GameData _gameData = new();

        public GameData GetGameData()
        {
            _gameData.Field = InitField();
            _gameData.Bullets = InitCannon();

            return _gameData;
        }

        private FieldItem[,] InitField()
        {
            while (true)
            {
                Size fieldSize = InputFieldSize();

                FieldCreationModel fieldCreationModel = new()
                {
                    BattleshipsAmount = Constants.BattleShipsAmount,
                    BattleshipVariations = Constants.BattleShipsVariations,
                    FieldSize = fieldSize
                };

                bool success = new FieldFactory().TryCreateField(fieldCreationModel, out var field, out int shipCells);

                if (!success)
                {
                    DisplayText(StringConstants.FailedToCreateField, true);
                    WaitForKey();
                }
                else
                {
                    _gameData.ShipCells = shipCells;

                    return field;
                }
            }
        }

        private int InitCannon()
        {
            return InputInt(StringConstants.InputBulletsAmount);
        }

        private Size InputFieldSize()
        {
            int height = InputInt(StringConstants.InputFieldHeight);
            int width = InputInt(StringConstants.InputFieldWidth);

            return new Size(width, height);
        }

        private int InputInt(string inputText)
        {
            DisplayText(inputText);

            while (true)
            {
                try
                {
                    return InputInt();
                }
                catch (Exception)
                {
                    DisplayText(StringConstants.InputAgain);
                }
            }
        }

        private void DisplayText(string text, bool newLine = false)
        {
            if (newLine)
            {
                Console.WriteLine(text);
            }
            else
            {
                Console.Write(text);
            }
        }

        private void WaitForKey()
        {
            Console.ReadKey();
        }

        private int InputInt()
        {
            return int.Parse(Console.ReadLine()!);
        }
    }
}
