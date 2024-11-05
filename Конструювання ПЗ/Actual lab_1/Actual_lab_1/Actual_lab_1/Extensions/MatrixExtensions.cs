using System.Drawing;

namespace Actual_lab_1.Extensions
{
    public static class MatrixExtensions
    {
        public static Size GetSize<T>(this T[,] matrix)
        {
            return new Size(matrix.GetLength(0), matrix.GetLength(1));
        }
    }
}
