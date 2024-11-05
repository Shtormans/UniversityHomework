namespace ConsoleEngine.Features.Input
{
    public interface IInputService
    {
        public void Init();

        public bool GetKeDown(ConsoleKey key);
    }
}
