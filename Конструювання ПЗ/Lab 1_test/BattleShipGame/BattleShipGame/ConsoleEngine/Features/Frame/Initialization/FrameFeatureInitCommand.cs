using ConsoleEngine.Domain.Abstractions;

namespace ConsoleEngine.Features.Frame
{
    internal class FrameFeatureInitCommand : BaseFeatureInitCommand
    {
        public override void BindDependencies()
        {
            ClassFactory.Bind<FrameManager>();

            ClassFactory.Bind<IFrameService, FrameService>();
        }

        public override void InitManagers()
        {
            ClassFactory.Resolve<FrameManager>().Init();
        }
    }
}
