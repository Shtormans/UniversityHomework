using Lab_1.Domain.Enums;
using Lab_1.Features.Output;
using System.Drawing;

namespace Lab_1.Features.GameLoop.Field;

internal class FieldContainer
{
    private FieldItem[,] _field;

    public FieldContainer(Size fieldSize)
    {
        _field = new FieldItem[fieldSize.Height, fieldSize.Width];
    }

    public void DisplaySelf(IOutputService outputService)
    {
        Size size = GetSize();

        OutputModel[,] outputMatrix = new OutputModel[size.Height, size.Width];

        for (int y = 0; y < size.Height; y++)
        {
            for (int x = 0; x < size.Width; x++)
            {
                outputMatrix[y, x] = _field[y, x].TranlateToOutput();
            }
        }

        outputService.Display(outputMatrix);
    }

    public Size GetSize()
    {
        int fieldHeight = _field.GetLength(0);
        int fieldWidth = _field.GetLength(1);

        return new Size(fieldHeight, fieldWidth);
    }

    public void Init(FieldItem defaultItem)
    {
        Size size = GetSize();

        for (int y = 0; y < size.Height; y++)
        {
            for (int x = 0; x < size.Width; x++)
            {
                _field[y, x] = defaultItem;
            }
        }
    }

    private void SetItem(FieldItem item, Point position)
    {
        SetItem(item, position, 1, 1);
    }

    public void SetItem(FieldItem item, Point position, int width, int height)
    {
        for (int y = position.Y; y < height; y++)
        {
            for (int x = position.X; x < width; x++)
            {
                _field[y, x] = item;
            }
        }
    }

    public FieldItem GetItem(Point position)
    {
        return _field[position.X, position.Y];
    }
}
