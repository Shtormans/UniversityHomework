using ConsoleEngine.Features.Frame;

namespace ConsoleEngine.Features.Time
{
    internal class TimeService : ITimeService
    {
        private readonly IFrameService _frameService;
        private readonly TimeManager _timeManager;

        public TimeService(IFrameService frameService, TimeManager timeManager)
        {
            _frameService = frameService;
            _timeManager = timeManager;
        }

        public void Init()
        {
            _frameService.AddManagerToGameLoop(_timeManager);
        }

        public double DeltaTime => _timeManager.DeltaTime;
    }
}
