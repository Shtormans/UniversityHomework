using Actual_lab_1.DTOs;
using Actual_lab_1.Enums;
using Actual_lab_1.Extensions;
using System.Drawing;

namespace Actual_lab_1.Factories
{
    public class FieldFactory
    {
        private readonly Random _random = new Random();

        public bool TryCreateField(FieldCreationModel creationModel, out FieldItem[,] field, out int shipCells)
        {
            if (creationModel.FieldSize.Height < 1 || creationModel.FieldSize.Width < 1)
            {
                field = null;
                shipCells = 0;

                return false;
            }

            field = new FieldItem[creationModel.FieldSize.Height, creationModel.FieldSize.Width];

            return TryCreateBattleShips(field, creationModel.BattleshipsAmount, creationModel.BattleshipVariations, out shipCells);
        }

        private bool TryCreateBattleShips(FieldItem[,] field, int amount, List<Size> variations, out int shipCells)
        {
            List<List<(Size, Point)>> suitableOptions = CreateBattleShip(field, variations, amount);

            if (suitableOptions.Count == 0)
            {
                shipCells = 0;
                return false;
            }

            List<(Size, Point)> variationList = suitableOptions[_random.Next(suitableOptions.Count)];

            shipCells = 0;

            foreach (var variation in variationList)
            {
                shipCells += variation.Item1.Width * variation.Item1.Height;

                PlaceShip(field, variation.Item2, variation.Item1);
            }

            return true;
        }

        private List<List<(Size, Point)>> CreateBattleShip(FieldItem[,] field, List<Size> variations, int shipAmount)
        {
            Size fieldSize = field.GetSize();
            List<List<(Size, Point)>> suitableOptions = new();

            foreach (Size shipSize in variations)
            {
                int maxStartX = fieldSize.Width - shipSize.Width + 1;
                int maxStartY = fieldSize.Height - shipSize.Height + 1;

                int repetitionsAmount = maxStartX * maxStartY;

                for (int i = 0; i < repetitionsAmount; i++)
                {
                    int x = i % maxStartX;
                    int y = i / maxStartX;

                    Point shipPosition = new(x, y);

                    if (CanPlace(field, shipPosition, shipSize, fieldSize))
                    {
                        (Size, Point) currentOption = (shipSize, new(x, y));

                        if (shipAmount == 1)
                        {
                            suitableOptions.Add([currentOption]);
                        }
                        else
                        {
                            PlaceShip(field, shipPosition, shipSize);

                            List<List<(Size, Point)>> innerShipsOptions = CreateBattleShip(field, variations, shipAmount - 1);

                            if (innerShipsOptions.Count != 0)
                            {
                                foreach (var option in innerShipsOptions)
                                {
                                    option.Insert(0, currentOption);
                                }

                                suitableOptions = suitableOptions.Concat(innerShipsOptions).ToList();
                            }

                            UnplaceShip(field, shipPosition, shipSize);
                        }
                    }
                }
            }

            return suitableOptions;
        }

        private bool CanPlace(FieldItem[,] field, Point shipPosition, Size shipSize, Size boardSize)
        {
            int minY = Math.Max(0, shipPosition.Y - 1);
            int maxY = Math.Min(shipPosition.Y + shipSize.Height, boardSize.Height - 1);

            int minX = Math.Max(0, shipPosition.X - 1);
            int maxX = Math.Min(shipPosition.X + shipSize.Width, boardSize.Width - 1);

            for (int y = minY; y <= maxY; y++)
            {
                for (int x = minX; x <= maxX; x++)
                {
                    if (field[y, x] != FieldItem.Water)
                    {
                        return false;
                    }
                }
            }

            return true;
        }

        private void PlaceShip(FieldItem[,] field, Point shipPosition, Size shipSize)
        {
            PlaceFieldItems(FieldItem.Battleship, field, shipPosition, shipSize);
        }

        private void UnplaceShip(FieldItem[,] field, Point shipPosition, Size shipSize)
        {
            PlaceFieldItems(FieldItem.Water, field, shipPosition, shipSize);
        }

        private void PlaceFieldItems(FieldItem item, FieldItem[,] field, Point position, Size size)
        {
            for (int y = position.Y; y < position.Y + size.Height; y++)
            {
                for (int x = position.X; x < position.X + size.Width; x++)
                {
                    field[y, x] = item;
                }
            }
        }
    }
}
