namespace ConsoleEngine.Features.Time
{
    public interface ITimeService
    {
        public double DeltaTime { get; }

        public void Init();
    }
}
