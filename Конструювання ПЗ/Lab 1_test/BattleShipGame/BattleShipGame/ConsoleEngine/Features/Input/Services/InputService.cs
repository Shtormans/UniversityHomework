using ConsoleEngine.Features.Frame;

namespace ConsoleEngine.Features.Input
{
    internal class InputService : IInputService
    {
        private readonly IFrameService _frameService;
        private readonly InputManager _inputManager;

        public InputService(IFrameService frameService, InputManager inputManager)
        {
            _frameService = frameService;
            _inputManager = inputManager;            
        }

        public void Init()
        {
            _frameService.AddManagerToGameLoop(_inputManager);
        }

        public bool GetKeDown(ConsoleKey key)
        {
            return _inputManager.EnteredKeys[(int)key];
        }
    }
}
