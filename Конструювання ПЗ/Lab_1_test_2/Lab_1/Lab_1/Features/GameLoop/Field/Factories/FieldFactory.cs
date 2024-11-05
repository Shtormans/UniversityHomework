using Lab_1.Domain.Enums;
using System.Drawing;

namespace Lab_1.Features.GameLoop.Field;

internal class FieldFactory
{
    private readonly Random _random = new Random();

    public bool TryCreateField(FieldCreationModel creationModel, out FieldContainer field)
    {
        if (creationModel.FieldSize.Height < 1 || creationModel.FieldSize.Width < 1)
        {
            field = null;
            return false;
        }

        field = new(creationModel.FieldSize);
        field.Init(FieldItem.Water);

        return TryCreateBattleShips(field, creationModel.BattleshipsAmount, creationModel.BattleshipVariations);
    }

    private bool TryCreateBattleShips(FieldContainer field, int amount, List<Size> variations)
    {
        for (int i = 0; i < amount; i++)
        {
            int index = _random.Next(variations.Count);
            Size variation = variations[index];

            bool success = TryCreateBattleShip(field, variation);

            if (!success)
            {
                return false;
            }
        }

        return true;
    }

    private bool TryCreateBattleShip(FieldContainer field, Size shipSize)
    {
        Size fieldSize = field.GetSize();

        int maxStartX = fieldSize.Width - shipSize.Width;
        int maxStartY = fieldSize.Height - shipSize.Height;

        Point randomShipPosition = new()
        {
            X = _random.Next(maxStartX),
            Y = _random.Next(maxStartY)
        };

        int repetitionsAmount = maxStartX * maxStartY;
        for (int i = 0; i < repetitionsAmount; i++)
        {
            int x = (randomShipPosition.X + i) % fieldSize.Width;
            int y = (randomShipPosition.Y + i) % fieldSize.Height;

            Point shipPosition = new(x, y);

            if (TryPlace(field, shipPosition, shipSize))
            {
                return true;
            }
        }

        return false;
    }

    private bool TryPlace(FieldContainer field, Point shipPosition, Size shipSize)
    {
        for (int y = shipPosition.Y; y < shipSize.Height; y++)
        {
            for (int x = shipPosition.X; x < shipSize.Width; x++)
            {
                Point position = new(x, y);

                if (field.GetItem(position) != FieldItem.Water)
                {
                    return false;
                }
            }
        }

        return true;
    }
}
