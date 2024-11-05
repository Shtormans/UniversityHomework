using ConsoleEngine.Domain.Abstractions;

namespace ConsoleEngine.Features.Time
{
    internal class TimeManager : GameManager
    {
        private DateTime _lastUpdateTime;

        public double DeltaTime { get; private set; }

        public override void Init()
        {
            _lastUpdateTime = DateTime.UtcNow;
        }

        public override void Update()
        {
            DateTime now = DateTime.UtcNow;
            TimeSpan timeSpan = now - _lastUpdateTime;

            DeltaTime = timeSpan.TotalSeconds;

            _lastUpdateTime = now;
        }
    }
}
