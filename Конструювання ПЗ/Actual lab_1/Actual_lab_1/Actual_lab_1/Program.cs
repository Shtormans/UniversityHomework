using Actual_lab_1;
using Actual_lab_1.DTOs;
using Actual_lab_1.Enums;
using Actual_lab_1.Extensions;
using System.Drawing;

internal class Program
{
    private static void Main(string[] args)
    {
        GameData data = Init();
        Run(data);
    }

    private static GameData Init()
    {
        GameData gameData = new GameInitializer().GetGameData();
        Console.Clear();
        Console.CursorVisible = false;

        return gameData;
    }

    private static void Run(GameData data)
    {
        Point aim = new(0, 0);
        Size fieldSize = data.Field.GetSize();

        int bullets = data.Bullets;
        int shipCells = data.ShipCells;

        while (true)
        {
            OutputField(data.Field, aim);
            Console.WriteLine($"{StringConstants.BulletsLeft} {bullets}       ");

            ConsoleKey key = InputKey();

            if (key.IsArrow())
            {
                MoveAim(ref aim, key, fieldSize);
            }

            if (key == ConsoleKey.Spacebar)
            {
                TryFire(aim, data.Field, ref bullets, ref shipCells);
            }

            ClearConsole(fieldSize);

            if (shipCells == 0)
            {
                Console.Clear();
                Console.WriteLine(StringConstants.YouWon);
                break;
            }

            if (bullets == 0)
            {
                Console.Clear();
                Console.WriteLine(StringConstants.YouLost);
                break;
            }
        }
    }

    private static ConsoleKey InputKey()
    {
        return Console.ReadKey(true).Key;
    }

    private static bool TryFire(Point aim, FieldItem[,] field, ref int bulletsAmount, ref int shipCells)
    {
        if (field[aim.Y, aim.X] is FieldItem.Miss or FieldItem.Hit)
        {
            return false;
        }

        bulletsAmount--;

        if (field[aim.Y, aim.X] is FieldItem.Water)
        {
            field[aim.Y, aim.X] = FieldItem.Miss;
        }

        if (field[aim.Y, aim.X] is FieldItem.Battleship)
        {
            shipCells--;
            field[aim.Y, aim.X] = FieldItem.Hit;
        }

        return true;
    }

    private static void MoveAim(ref Point aim, ConsoleKey key, Size fieldSize)
    {
        switch (key)
        {
            case ConsoleKey.UpArrow:
                aim.Y = Math.Max(0, aim.Y - 1);
                break;
            case ConsoleKey.DownArrow:
                aim.Y = Math.Min(fieldSize.Height - 1, aim.Y + 1);
                break;
            case ConsoleKey.LeftArrow:
                aim.X = Math.Max(0, aim.X - 1);
                break;
            case ConsoleKey.RightArrow:
                aim.X = Math.Min(fieldSize.Width - 1, aim.X + 1);
                break;
        }
    }

    private static void OutputField(FieldItem[,] field, Point? aim)
    {
        Size fieldSize = field.GetSize();

        for (int i = 0; i < fieldSize.Height; i++)
        {
            for (int j = 0; j < fieldSize.Width; j++)
            {
                if (aim is not null && aim.Value.Y == i && aim.Value.X == j)
                {
                    Console.BackgroundColor = ConsoleColor.Red;
                }
                else
                {
                    Console.BackgroundColor = ConsoleColor.Black;
                }

                Console.Write(field[i, j].TranlateToOutput());
            }

            Console.WriteLine();
        }

        Console.BackgroundColor = ConsoleColor.Black;
    }

    private static void ClearConsole(Size fieldSize)
    {
        Console.BackgroundColor = ConsoleColor.Black;
        Console.SetCursorPosition(0, 0);

        for (int i = 0; i < fieldSize.Height + 1; i++)
        {
            for (int j = 0; j < fieldSize.Width; j++)
            {
                Console.Write(' ');
            }

            Console.WriteLine();
        }

        Console.SetCursorPosition(0, 0);
    }
}