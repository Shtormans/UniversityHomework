using ConsoleEngine.Domain.Abstractions;

namespace ConsoleEngine.Features.Frame
{
    internal class FrameService : IFrameService
    {
        private readonly FrameManager _frameManager;

        public FrameService(FrameManager frameManager)
        {
            _frameManager = frameManager;
        }

        public void AddManagerToGameLoop(GameManager gameManager)
        {
            _frameManager.AddManager(gameManager);
        }
    }
}
