using ConsoleEngine.Features.Frame;

namespace ConsoleEngine.Features.Output
{
    internal class OutputService : IOutputService
    {
        private readonly IFrameService _frameService;
        private readonly OutputManager _outputManager;

        public OutputService(IFrameService frameService, OutputManager outputManager)
        {
            _frameService = frameService;
            _outputManager = outputManager;
        }

        public void Init()
        {
            _frameService.AddManagerToGameLoop(_outputManager);
        }
    }
}
