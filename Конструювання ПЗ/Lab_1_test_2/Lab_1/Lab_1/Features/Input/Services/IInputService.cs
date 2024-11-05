namespace Lab_1.Features.Input.Services
{
    internal interface IInputService
    {
        public ConsoleKey GetKeyDown();

        public T GetValue<T>();
        public string GetString();
        public int GetInt();
    }
}
