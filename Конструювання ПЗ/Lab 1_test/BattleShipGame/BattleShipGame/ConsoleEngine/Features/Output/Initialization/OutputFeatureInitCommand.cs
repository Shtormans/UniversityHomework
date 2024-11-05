using ConsoleEngine.Domain.Abstractions;

namespace ConsoleEngine.Features.Output
{
    internal class OutputFeatureInitCommand : BaseFeatureInitCommand
    {
        public override void BindDependencies()
        {
            ClassFactory.Bind<OutputManager>();

            ClassFactory.Bind<IOutputService, OutputService>();
        }

        public override void InitManagers()
        {
            ClassFactory.Resolve<OutputManager>().Init();
        }

        public override void InitServices()
        {
            ClassFactory.Resolve<IOutputService>().Init();
        }
    }
}
