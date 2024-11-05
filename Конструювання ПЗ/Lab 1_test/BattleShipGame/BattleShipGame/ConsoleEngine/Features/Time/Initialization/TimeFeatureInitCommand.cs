using ConsoleEngine.Domain.Abstractions;

namespace ConsoleEngine.Features.Time
{
    internal class TimeFeatureInitCommand : BaseFeatureInitCommand
    {
        public override void BindDependencies()
        {
            ClassFactory.Bind<TimeManager>();

            ClassFactory.Bind<ITimeService, TimeService>();
        }

        public override void InitManagers()
        {
            ClassFactory.Resolve<TimeManager>().Init();
        }

        public override void InitServices()
        {
            ClassFactory.Resolve<ITimeService>().Init();
        }
    }
}
