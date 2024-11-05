using System.Drawing;

namespace Lab_1.Features.Input.Services
{
    internal class InputService : IInputService
    {
        public ConsoleKey GetKeyDown()
        {
            return Console.ReadKey(true).Key;
        }

        public T GetValue<T>()
        {
            T defaultInstance = default;

            object generalValue = defaultInstance switch
            {
                string => GetString(),
                int => GetInt(),
                _ => throw new NotImplementedException()
            };

            return (T)generalValue;
        }

        public string GetString()
        {
            return Console.ReadLine();
        }

        public int GetInt()
        {
            string text = GetString();

            return int.Parse(text);
        }
    }
}
