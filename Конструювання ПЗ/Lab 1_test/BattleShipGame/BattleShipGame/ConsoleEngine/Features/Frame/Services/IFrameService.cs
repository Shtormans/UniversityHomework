using ConsoleEngine.Domain.Abstractions;

namespace ConsoleEngine.Features.Frame
{
    internal interface IFrameService
    {
        public void AddManagerToGameLoop(GameManager gameManager);
    }
}
